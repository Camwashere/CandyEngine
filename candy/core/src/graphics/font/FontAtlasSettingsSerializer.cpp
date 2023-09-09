#include <candy/graphics/font/FontAtlasSettingsSerializer.hpp>
#include <utility>
#include <ryml_std.hpp>
#include <ryml.hpp>

#include <c4/format.hpp>



namespace Candy::Graphics
{
  std::string AtlasTypeToString(Font::AtlasGeneratorSettings::AtlasType atlasType)
  {
    switch (atlasType)
    {
      case Font::AtlasGeneratorSettings::AtlasType::MSDF:
        return "MSDF";
      case Font::AtlasGeneratorSettings::AtlasType::SDF:
        return "SDF";
      case Font::AtlasGeneratorSettings::AtlasType::PSDF:
        return "PSDF";
      case Font::AtlasGeneratorSettings::AtlasType::MTSDF:
        return "MTSDF";
      default:
        return "NONE";
    }
  }
  Font::AtlasGeneratorSettings::AtlasType StringToAtlasType(const std::string& str)
  {
    if (str == "MSDF")
    {
      return Font::AtlasGeneratorSettings::AtlasType::MSDF;
    }
    else if (str == "SDF")
    {
      return Font::AtlasGeneratorSettings::AtlasType::SDF;
    }
    else if (str == "PSDF")
    {
      return Font::AtlasGeneratorSettings::AtlasType::PSDF;
    }
    else if (str == "MTSDF")
    {
      return Font::AtlasGeneratorSettings::AtlasType::MTSDF;
    }
    else
    {
      return Font::AtlasGeneratorSettings::AtlasType::NONE;
    }
  }
  
  std::string DimensionConstraintToString(Font::AtlasGeneratorSettings::DimensionConstraint value)
  {
    switch(value)
    {
      case Font::AtlasGeneratorSettings::DimensionConstraint::SQUARE:
        return "SQUARE";
      case Font::AtlasGeneratorSettings::DimensionConstraint::EVEN_SQUARE:
        return "EVEN_SQUARE";
      case Font::AtlasGeneratorSettings::DimensionConstraint::MULTIPLE_OF_4_SQUARE:
        return "MULTIPLE_OF_4_SQUARE";
      case Font::AtlasGeneratorSettings::DimensionConstraint::POWER_OF_2_SQUARE:
        return "POWER_OF_2_SQUARE";
      case Font::AtlasGeneratorSettings::DimensionConstraint::POWER_OF_2_RECTANGLE:
        return "POWER_OF_2_RECTANGLE";
      default:
        return "NONE";
        
    }
  }
  
  Font::AtlasGeneratorSettings::DimensionConstraint StringToDimensionConstraint(const std::string& str)
  {
    if (str == "SQUARE")
    {
      return Font::AtlasGeneratorSettings::DimensionConstraint::SQUARE;
    }
    else if (str == "EVEN_SQUARE")
    {
      return Font::AtlasGeneratorSettings::DimensionConstraint::EVEN_SQUARE;
    }
    else if (str == "MULTIPLE_OF_4_SQUARE")
    {
      return Font::AtlasGeneratorSettings::DimensionConstraint::MULTIPLE_OF_4_SQUARE;
    }
    else if (str == "POWER_OF_2_SQUARE")
    {
      return Font::AtlasGeneratorSettings::DimensionConstraint::POWER_OF_2_SQUARE;
    }
    else if (str == "POWER_OF_2_RECTANGLE")
    {
      return Font::AtlasGeneratorSettings::DimensionConstraint::POWER_OF_2_RECTANGLE;
    }
    else
    {
      return Font::AtlasGeneratorSettings::DimensionConstraint::NONE;
    }
  }
  
  size_t to_chars(c4::substr buf, const Font::AtlasGeneratorSettings::AtlasType& v)
  {
    // convert the enum Color to a string
    const std::string strColor = AtlasTypeToString(v);
    // use c4::format() to put the string into the buffer
    return c4::format(buf, "{}", strColor);
  }
  
  bool from_chars(c4::csubstr buf, Font::AtlasGeneratorSettings::AtlasType* v)
  {
    // equivalent to converting string color to enum Color
    *v = StringToAtlasType(std::string(buf.str, buf.len));
    return *v != Font::AtlasGeneratorSettings::AtlasType::NONE; // or return true; depending on your use case
  }
  
  size_t to_chars(c4::substr buf, const Font::AtlasGeneratorSettings::DimensionConstraint& v)
  {
    // convert the enum Color to a string
    const std::string strColor = DimensionConstraintToString(v);
    // use c4::format() to put the string into the buffer
    return c4::format(buf, "{}", strColor);
  }
  
  bool from_chars(c4::csubstr buf, Font::AtlasGeneratorSettings::DimensionConstraint* v)
  {
    // equivalent to converting string color to enum Color
    *v = StringToDimensionConstraint(std::string(buf.str, buf.len));
    return true;
  }
  
}


namespace Candy::Graphics
{
  FontAtlasSettingsSerializer::FontAtlasSettingsSerializer(Font::AtlasGeneratorSettings* value) : settings(value)
  {
    CANDY_CORE_ASSERT(settings != nullptr);
  
  }
  
  
  bool FontAtlasSettingsSerializer::Serialize(const std::filesystem::path& filepath)
  {
    c4::yml::Tree tree;
    c4::yml::NodeRef root = tree.rootref();
    root |= c4::yml::MAP;
    root["GeneratorSettings"] |= c4::yml::MAP;
    auto settingsNode = root["GeneratorSettings"];
    settingsNode["PixelRange"] << settings->pixelRange;
    settingsNode["MinimumScale"] << settings->minimumScale;
    settingsNode["Scale"] << settings->scale;
    settingsNode["MiterLimit"] << settings->miterLimit;
    settingsNode["Padding"] << settings->padding;
    settingsNode["DimensionWidth"] << settings->dimensionWidth;
    settingsNode["DimensionHeight"] << settings->dimensionHeight;
    settingsNode["ExpensiveColoring"] << settings->expensiveColoring;
    settingsNode["DimensionConstraint"] << settings->dimensionConstraint;
    settingsNode["DefaultAngleThreshold"] << settings->defaultAngleThreshold;
    settingsNode["AttributeSettings"] |= c4::yml::MAP;
    auto attributesNode = settingsNode["AttributeSettings"];
    attributesNode["OverlapSupport"] << settings->attributeSettings.overlapSupport;
    attributesNode["ScanlinePass"] << settings->attributeSettings.scanlinePass;
    attributesNode["AtlasType"] << settings->attributeSettings.atlasType;
    attributesNode["ThreadCount"] << settings->attributeSettings.threadCount;
    
    
    
    
    FILE* out = fopen(filepath.string().c_str(), "w");
    if (!out)
    {
      CANDY_CORE_ERROR("Failed to open file {0} for font serialization", filepath.string());
      return false;
    }
    c4::yml::emit_yaml(tree, out);
    fclose(out);
    return true;
  }
  bool FontAtlasSettingsSerializer::Deserialize(const std::filesystem::path& filepath)
  {
    
    // read the file into a string
    std::ifstream fin(filepath);
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string yaml_str = buffer.str();
    if (yaml_str.empty())
    {
      CANDY_CORE_ERROR("EMPTY YAML STRING WITH PATH: {}", filepath.string());
      return false;
    }
    
    // parse the YAML string
    ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(yaml_str));
    ryml::NodeRef root = tree.rootref();
    
    auto settingsNode = root["GeneratorSettings"];
    if (settingsNode.empty())
    {
      CANDY_CORE_ERROR("Failed to deserialize font file {0}. Empty Settings Node", filepath.string());
      return false;
    }
    
    
    settingsNode["PixelRange"] >> settings->pixelRange;
    settingsNode["MinimumScale"] >> settings->minimumScale;
    settingsNode["Scale"] >> settings->scale;
    settingsNode["MiterLimit"] >> settings->miterLimit;
    settingsNode["Padding"] >> settings->padding;
    settingsNode["DimensionWidth"] >> settings->dimensionWidth;
    settingsNode["DimensionHeight"] >> settings->dimensionHeight;
    settingsNode["ExpensiveColoring"] >> settings->expensiveColoring;
    
    settingsNode["DimensionConstraint"] >> settings->dimensionConstraint;
   
    settingsNode["DefaultAngleThreshold"] >> settings->defaultAngleThreshold;
    settingsNode["AttributeSettings"] |= c4::yml::MAP;
    auto attributesNode = settingsNode["AttributeSettings"];
    attributesNode["OverlapSupport"] >> settings->attributeSettings.overlapSupport;
    attributesNode["ScanlinePass"] >> settings->attributeSettings.scanlinePass;
    
    attributesNode["AtlasType"] >> settings->attributeSettings.atlasType;
    
    attributesNode["ThreadCount"] >> settings->attributeSettings.threadCount;
    
    
    
    return true;
  }
}