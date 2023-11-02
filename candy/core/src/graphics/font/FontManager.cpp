#include <candy/graphics/font/FontManager.hpp>
#include <candy/graphics/font/Font.hpp>
#include <CandyPch.hpp>
#include <utility>
#include "FontAtlas/msdf-atlas-gen.hpp"
#include <candy/graphics/font/FontAtlasSettingsSerializer.hpp>
namespace Candy::Graphics
{
  FontFamily::FontFamily(std::string  familyName) : name(std::move(familyName))
  {
  
  }
  SharedPtr<Font> FontFamily::GetFont(const std::string& style)
  {
    const auto& found = styleToFontMap.find(style);
    if (found == styleToFontMap.end())
    {
      CANDY_CORE_WARN("Font with style {0} does not exist in family {1}", style, name);
      return nullptr;
    }
    else
    {
      return found->second;
    }
  }
  
  bool FontFamily::HasFont(const std::string& style) const
  {
    const auto& found = styleToFontMap.find(style);
    return found != styleToFontMap.end();
  }
  
  bool FontFamily::AddFont(const SharedPtr<Font>& font)
  {
    CANDY_CORE_ASSERT(font->GetFamily() == name);
    const auto& found = styleToFontMap.find(font->GetStyle());
    if (found == styleToFontMap.end())
    {
      styleToFontMap[font->GetStyle()] = font;
      return true;
    }
    else
    {
      CANDY_CORE_WARN("Font with style {0} already exists in family {1}", font->GetStyle(), name);
      return false;
    }
   
  }
  
  struct FontManagerData
  {
    std::vector<std::filesystem::path> fontDirectories{};
    std::vector<std::string> validFontFileExtensions{};
    std::unordered_map<std::string, SharedPtr<FontFamily>> nameToFamilyMap{};
    std::unordered_map<std::string, SharedPtr<Font>> nameToFontMap{};
    std::vector<std::string> fontNameList{};
    size_t maxRecursiveFontDirectorySearchDepth;
    bool recursiveFontDirectorySearch;
    FontAtlasGeneratorSettings atlasGeneratorSettings{};
    std::filesystem::path atlasGeneratorSettingsPath;
    bool useCachedAtlasImages=false;
    std::filesystem::path cachedAtlasImagesPath;
  };
  
  static FontManagerData data{};
  
  
  bool FontManager::SaveAtlasGeneratorSettings(const std::filesystem::path& filepath)
  {
    FontAtlasSettingsSerializer serializer(&data.atlasGeneratorSettings);
    return serializer.Serialize(filepath);
  }
  bool FontManager::LoadAtlasGeneratorSettings(const std::filesystem::path& filepath)
  {
    
    FontAtlasSettingsSerializer serializer(&data.atlasGeneratorSettings);
    return serializer.Deserialize(filepath);
    
  }
  
  void FontManager::Init(const FontManagerSettings& settings)
  {
    data.fontDirectories = settings.fontDirectories;
    data.validFontFileExtensions = settings.validFontFileExtensions;
    data.maxRecursiveFontDirectorySearchDepth = settings.maxRecursiveFontDirectorySearchDepth;
    data.recursiveFontDirectorySearch = settings.recursiveFontDirectorySearch;
    data.atlasGeneratorSettingsPath = settings.atlasGeneratorSettingsPath;
    data.cachedAtlasImagesPath = "assets/cache/font";
    if (!std::filesystem::exists(data.cachedAtlasImagesPath))
    {
      if (std::filesystem::create_directories(data.cachedAtlasImagesPath))
      {
        CANDY_CORE_INFO("Created font atlas cache directory");
      }
      else
      {
        CANDY_CORE_ERROR("Failed to create font atlas cache directory");
        CANDY_CORE_ASSERT(false);
      }
    }
    
    if (std::filesystem::exists(data.atlasGeneratorSettingsPath))
    {
      if (LoadAtlasGeneratorSettings(data.atlasGeneratorSettingsPath))
      {
        CANDY_CORE_INFO("Successfully loaded atlas generator settings from path: {0}", data.atlasGeneratorSettingsPath.string());
      }
      else
      {
        CANDY_CORE_WARN("Failed to load atlas generator settings from path: {0}. Using default atlas generator settings", data.atlasGeneratorSettingsPath.string());
        data.atlasGeneratorSettings = FontAtlasGeneratorSettings();
      }
    }
    
    if (msdf_atlas::FontAtlasLoader::Init())
    {
      CANDY_CORE_INFO("Successfully initialized font atlas loader and freetype");
    }
    else
    {
      CANDY_CORE_ERROR("Failed to initialize font atlas loader and freetype");
      CANDY_CORE_ASSERT(false);
    }
    for (const auto& directory : data.fontDirectories)
    {
      LoadDirectory(directory);
    }
    
  }
  
  
  
  
  void FontManager::LoadDirectory(const std::filesystem::path& directory, size_t currentDepth)
  {
    CANDY_CORE_ASSERT(std::filesystem::is_directory(directory));
    if (currentDepth >= data.maxRecursiveFontDirectorySearchDepth)
    {
      CANDY_CORE_ERROR("Current depth exceeds max recursive font directory search depth");
      return;
    }
    std::vector<std::filesystem::path> invalidPaths{};
    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
      
      if (!entry.is_directory())
      {
        if (! LoadFile(entry.path()))
        {
          invalidPaths.push_back(entry.path());
        }
      }
      else
      {
        if (data.recursiveFontDirectorySearch)
        {
          LoadDirectory(entry.path(), currentDepth + 1);
        }
        
      }
    }
    
  }
  bool FontManager::LoadFile(const std::filesystem::path& path)
  {
    if (IsValidFontFile(path))
    {
      SharedPtr<Font> font = CreateSharedPtr<Font>(path);
      std::string familyName = font->GetFamily();
      const auto& found = data.nameToFamilyMap.find(familyName);
      if (found == data.nameToFamilyMap.end())
      {
        SharedPtr<FontFamily> family = CreateSharedPtr<FontFamily>(familyName);
        if (AddFamily(family))
        {
          return AddFont(font, family);
        }
        else
        {
          CANDY_CORE_WARN("Failed to add font family: {0}", familyName);
          return false;
        }
      }
      else
      {
        return AddFont(font, found->second);
      }
      
      
    }
    return false;
  }
  bool FontManager::AddFont(const SharedPtr<Font>& font, const SharedPtr<FontFamily>& family)
  {
    const auto& found = data.nameToFontMap.find(font->GetName());
    if (found == data.nameToFontMap.end())
    {
      data.nameToFontMap[font->GetName()] = font;
      data.fontNameList.push_back(font->GetName());
      CANDY_CORE_INFO("Added font: {0}", font->GetName());
      return family->AddFont(font);
    }
    else
    {
      CANDY_CORE_WARN("Font with name {0} already exists", font->GetName());
      return false;
    }
  }
  /*bool FontManager::AddFont(const SharedPtr<Font>& font)
  {
    const auto& found = data.nameToFontMap.find(font->GetName());
    if (found == data.nameToFontMap.end())
    {
      data.nameToFontMap[font->GetName()] = font;
      return true;
    }
    else
    {
      CANDY_CORE_WARN("Font with name {0} already exists", font->GetName());
      return false;
    }
  }*/
  bool FontManager::AddFamily(const SharedPtr<FontFamily>& family)
  {
    const auto& found = data.nameToFamilyMap.find(family->name);
    if (found == data.nameToFamilyMap.end())
    {
      data.nameToFamilyMap[family->name] = family;
      return true;
    }
    else
    {
      CANDY_CORE_WARN("Font family with name {0} already exists", family->name);
      return false;
    }
  }
  bool FontManager::IsValidFontFile(const std::filesystem::path& path)
  {
    std::string extension = path.extension().string();
    for (const auto& validExtension : data.validFontFileExtensions)
    {
      if (extension == validExtension)
      {
        return true;
      }
    }
    return false;
  
  }
  bool FontManager::LoadFont(const std::string& fontName)
  {
    SharedPtr<Font> font = GetFont(fontName);
    if (font)
    {
      return font->Load();
    }
    else
    {
      return false;
    }
  }
  bool FontManager::LoadFont(const std::string& familyName, const std::string& styleName)
  {
    SharedPtr<Font> font = GetFont(familyName, styleName);
    if (font)
    {
      return font->Load();
    }
    else
    {
      return false;
    }
  }
  SharedPtr<Font> FontManager::GetFont(const std::string& fontName)
  {
    const auto& found = data.nameToFontMap.find(fontName);
    if (found == data.nameToFontMap.end())
    {
      CANDY_CORE_WARN("Font with name {0} does not exist. Total font count: {1}", fontName, GetFontCount());
      return nullptr;
    }
    else
    {
      return found->second;
    }
  }
  SharedPtr<Font> FontManager::GetFont(const std::string& fontFamilyName, const std::string& fontStyleName)
  {
    if (GetFamily(fontFamilyName))
    {
      return GetFamily(fontFamilyName)->GetFont(fontStyleName);
    }
    else
    {
      return nullptr;
    }
  }
  SharedPtr<FontFamily> FontManager::GetFamily(const std::string& fontFamilyName)
  {
    const auto& found = data.nameToFamilyMap.find(fontFamilyName);
    if (found == data.nameToFamilyMap.end())
    {
      CANDY_CORE_WARN("Font family with name {0} does not exist", fontFamilyName);
      return nullptr;
    }
    else
    {
      return found->second;
    }
  }
  const FontAtlasGeneratorSettings& FontManager::GetAtlasGeneratorSettings()
  {
    return data.atlasGeneratorSettings;
  }
  size_t FontManager::GetFamilyCount()
  {
    return data.nameToFamilyMap.size();
  }
  size_t FontManager::GetFontCount()
  {
    
    return data.nameToFontMap.size();
  }
  const std::vector<std::string>& FontManager::GetFontNames()
  {
    return data.fontNameList;
  }
  bool FontManager::UseCachedAtlasImages()
  {
    return data.useCachedAtlasImages;
  }
  std::filesystem::path FontManager::GetCachedAtlasPath()
  {
    return data.cachedAtlasImagesPath;
  }
  SharedPtr<Font> FontManager::DefaultFont()
  {
    static SharedPtr<Font> defaultFont;
    if (!defaultFont)
    {
      defaultFont = GetFont("Open Sans", "Regular");
      if (!defaultFont)
      {
        CANDY_CORE_ERROR("Could not find default font");
        CANDY_CORE_ASSERT(false);
      }
      
    }
    if (! defaultFont->IsLoaded())
    {
      CANDY_CORE_INFO("Default font not loaded, attempting to load");
      if (defaultFont->Load())
      {
        CANDY_CORE_INFO("Successfully loaded default font");
      }
      else
      {
        CANDY_CORE_ERROR("Failed to load default font");
        CANDY_CORE_ASSERT(false);
      }
    }
    return defaultFont;
  }
}