#include <candy/graphics/font/MSDFSerializer.hpp>
#include <candy/graphics/font/MSDFData.hpp>
#include <ryml_std.hpp>
#include <ryml.hpp>
#include <c4/format.hpp>
#include <CandyPch.hpp>

struct KerningPair
{
  int first;
  int second;
  float amount;
};
size_t to_chars(c4::substr buf, const KerningPair& v)
{
  // convert the enum Color to a string
  return c4::format(buf, "[{},{},{}]", v.first, v.second, v.amount);
}

bool from_chars(c4::csubstr buf, KerningPair* v)
{
  // equivalent to converting string color to enum Color
  size_t ret = c4::unformat(buf, "[{},{},{}]", v->first, v->second, v->amount);
  return ret != c4::csubstr::npos;
}
namespace Candy::Graphics
{
  
  
  
  
  bool MSDFSerializer::Serialize(MSDFData* data, const std::filesystem::path& filepath)
  {
    CANDY_CORE_ASSERT(data != nullptr);
    c4::yml::Tree tree;
    c4::yml::NodeRef root = tree.rootref();
    root |= c4::yml::MAP;
    root["FontGeometry"] |= c4::yml::MAP;
    auto fontNode = root["FontGeometry"];
    const char* fontGeomName = data->fontGeometry.getName();
    if (fontGeomName)
    {
      fontNode["Name"] << fontGeomName;
    }
    else
    {
      fontNode["Name"] << "None";
    }
    fontNode["GeometryScale"] << data->fontGeometry.getGeometryScale();
    const auto& metrics = data->fontGeometry.getMetrics();
    
    auto metricsNode = fontNode["Metrics"];
    metricsNode |= c4::yml::MAP;
    metricsNode["AscenderY"] << metrics.ascenderY;
    metricsNode["DescenderY"] << metrics.descenderY;
    metricsNode["LineHeight"] << metrics.lineHeight;
    metricsNode["UnderlineY"] << metrics.underlineY;
    metricsNode["UnderlineThickness"] << metrics.underlineThickness;
    metricsNode["EmSize"] << metrics.emSize;
    
    
    auto kerningNode = fontNode["Kerning"];
    kerningNode |= c4::yml::SEQ;
    const auto& kerning = data->fontGeometry.getKerning();
    for (const auto& [key, value] : kerning)
    {
      auto node = kerningNode.append_child();
      KerningPair k = {key.first, key.second, value};
      node << k;
    }
    
    auto glyphsNode = root["GlyphStorage"];
    glyphsNode |= c4::yml::SEQ;
    for (const auto& glyph : data->glyphStorage) {
      auto node = glyphsNode.append_child();
      node |= c4::yml::MAP;
      
      node["Index"] << glyph.getGlyphIndex().GetIndex();
      node["Codepoint"] << glyph.getCodepoint();
      node["Advance"] << glyph.getAdvance();
      node["GeometryScale"] << glyph.getGeometryScale();
      
      
      auto boxNode = node["Box"];
      boxNode |= c4::yml::MAP;
      boxNode["Range"] << glyph.getBoxRange();
      boxNode["Scale"] << glyph.getBoxScale();
      boxNode["TranslateX"] << glyph.getBoxTranslate().x;
      boxNode["TranslateY"] << glyph.getBoxTranslate().y;
      
      
      msdf_atlas::Rectangle boxRect = glyph.getBoxRect();
      boxNode["RectX"] << boxRect.x;
      boxNode["RectY"] << boxRect.y;
      boxNode["RectW"] << boxRect.w;
      boxNode["RectH"] << boxRect.h;
      
    }
    
   
    
    
    
    
    
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
  bool MSDFSerializer::Deserialize(MSDFData* data, const std::filesystem::path& filepath)
  {
    CANDY_CORE_ASSERT(data != nullptr);
    
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
    
    auto fontNode = root["FontGeometry"];
    if (fontNode.empty())
    {
      CANDY_CORE_ERROR("Failed to deserialize font file {0}. Empty Settings Node", filepath.string());
      return false;
    }
    
    data->fontGeometry = msdf_atlas::FontGeometry(&data->glyphStorage);
    auto& fontGeometry = data->fontGeometry;
    fontNode["Name"] >> fontGeometry.name;
    fontNode["GeometryScale"] >> fontGeometry.geometryScale;
    
    msdf_atlas::FontMetrics metrics{};
    auto metricsNode = fontNode["Metrics"];
    metricsNode["AscenderY"] << metrics.ascenderY;
    metricsNode["DescenderY"] << metrics.descenderY;
    metricsNode["LineHeight"] << metrics.lineHeight;
    metricsNode["UnderlineY"] << metrics.underlineY;
    metricsNode["UnderlineThickness"] << metrics.underlineThickness;
    metricsNode["EmSize"] << metrics.emSize;
    
    fontGeometry.metrics = metrics;
    
    auto kerningNode = fontNode["Kerning"];
    for (auto node : kerningNode)
    {
      KerningPair k{};
      node >> k;
      fontGeometry.kerning[std::make_pair(k.first, k.second)] = k.amount;
    }
    
    auto glyphsNode = root["GlyphStorage"];
    for (auto node : glyphsNode)
    {
      msdf_atlas::GlyphGeometry glyph{};
      
      node["Index"] >> glyph.index;
      node["Codepoint"] >> glyph.codepoint;
      node["Advance"] >> glyph.advance;
      node["GeometryScale"] >> glyph.geometryScale;
      
      
      auto boxNode = node["Box"];
      boxNode["Range"] >> glyph.box.range;
      boxNode["Scale"] >> glyph.box.scale;
      boxNode["TranslateX"] >> glyph.box.translate.x;
      boxNode["TranslateY"] >> glyph.box.translate.y;
      
      
      boxNode["RectX"] >> glyph.box.rect.x;
      boxNode["RectY"] >> glyph.box.rect.y;
      boxNode["RectW"] >> glyph.box.rect.w;
      boxNode["RectH"] >> glyph.box.rect.h;
      
      data->glyphStorage.push_back(glyph);
      //data->AddGlyph(glyph);
    }
    
    
    
    
    
    return true;
  }
}