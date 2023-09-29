#include <editor/panels/SceneHierarchyPanel.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <candy/ecs/BaseComponents.hpp>
#include <candy/graphics/Renderer.hpp>
namespace Candy
{
  using namespace ECS;
  using namespace Math;
  using namespace Graphics;
  SceneHierarchyPanel::SceneHierarchyPanel(const SharedPtr<Scene>& scene)
  {
    CANDY_PROFILE_FUNCTION();
    SetContext(scene);
  }
  
  void SceneHierarchyPanel::SetContext(const SharedPtr<Scene> &scene)
  {
    context = scene;
    selectionContext={};
  }
  
  void SceneHierarchyPanel::OnRenderUI()
  {
    CANDY_PROFILE_FUNCTION();
    ImGui::Begin("Scene Hierarchy");
    if (context)
    {
      std::vector<Entity> roots{};
      for (auto [e] : context->registry.storage<entt::entity>().each())
      {
        Entity entity{e, context.get()};
        if (entity.IsRoot())
        {
          roots.push_back(entity);
        }
        //DrawEntityNode(entity);
      }
      
      for (auto& root : roots)
      {
        DrawEntityNode(root);
      }

      
      if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
      {
        selectionContext={};
      }
      if (ImGui::BeginPopupContextWindow())
      {
        if (selectionContext)
        {
          if (ImGui::MenuItem("Delete Entity"))
          {
            context->DestroyEntityTree(selectionContext);
            selectionContext={};
          }
          
        }
        if (ImGui::MenuItem("Create Empty Entity"))
        {
          context->CreateEntity("Empty Entity");
        }
        ImGui::EndPopup();
      }
      
    }
    
    ImGui::End();
    
    ImGui::Begin("Properties");
    
    if (selectionContext)
    {
      DrawComponents(selectionContext);
    }
    ImGui::End();
  }
  
  void SceneHierarchyPanel::SetSelectedEntity(ECS::Entity entity)
  {
    CANDY_PROFILE_FUNCTION();
    selectionContext = entity;
    isSelection2D = selectionContext.Is2D();
    if (entity)
    {
      Renderer::GetGizmo().SetTarget(&entity.GetTransform());
    }
    else
    {
      Renderer::GetGizmo().SetTarget(nullptr);
    }
    
    
  }
  
  void SceneHierarchyPanel::DrawEntityNode(Entity entity)
  {
    CANDY_PROFILE_FUNCTION();
    auto& tag = entity.GetComponent<TagComponent>().tag;
    ImGuiTreeNodeFlags flags;
    
    
    
    if (entity.HasChildren())
    {
      flags = ((selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    }
    else
    {
      flags = ((selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_Leaf; // Use ImGuiTreeNodeFlags_Leaf for nodes without children
    }
    flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    
    bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, "%s", tag.c_str());
    if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
    {
      SetSelectedEntity(entity);
    }
    
    bool entityDeleted = false;
    if (ImGui::BeginPopupContextItem())
    {
      if (ImGui::MenuItem("Delete Entity"))
        entityDeleted = true;
      
      ImGui::EndPopup();
    }
    
    if (opened)
    {
      // Recursively draw children nodes
      if (entity.HasChildren())
      {
        auto& children = entity.GetChildren().children;
        for(auto& child : children)
        {
          DrawEntityNode(child); // recursive call
        }
        
        ImGui::TreePop();
      }
      else
      {
        ImGui::TreePop();
      }
    
    }
    
    if (entityDeleted)
    {
      context->DestroyEntity(entity);
      if (selectionContext == entity)
        selectionContext = {};
    }
  }
  
  template<typename T, typename UIFunction>
  static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
  {
    CANDY_PROFILE_FUNCTION();
    const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
    if (entity.HasComponent<T>())
    {
      auto& component = entity.GetComponent<T>();
      ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
      
      ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
      float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
      ImGui::Separator();
      bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, "%s", name.c_str());
      ImGui::PopStyleVar(
      );
      ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
      if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
      {
        ImGui::OpenPopup("ComponentSettings");
      }
      
      bool removeComponent = false;
      if (ImGui::BeginPopup("ComponentSettings"))
      {
        if (ImGui::MenuItem("Remove component"))
          removeComponent = true;
        
        ImGui::EndPopup();
      }
      
      if (open)
      {
        uiFunction(component);
        ImGui::TreePop();
      }
      
      if (removeComponent)
        entity.RemoveComponent<T>();
    }
  }
  static void DrawFloatControl(const std::string& label, float& value, float min=0.0f, float max=0.0f, float columnWidth=100.0f)
  {
    CANDY_PROFILE_FUNCTION();
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];
    
    ImGui::PushID(label.c_str());
    
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();
    
    ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
    
    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::DragFloat("##X", &value, 0.01f, min, max, "%.2f");
    ImGui::PopItemWidth();
    
    ImGui::PopStyleVar();
    
    ImGui::Columns(1);
    
    ImGui::PopID();
  }
  static void DrawVector2Control(const std::string& label, Math::Vector2& values, float resetValue = 0.0f, float columnWidth = 100.0f)
  {
    CANDY_PROFILE_FUNCTION();
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];
    
    ImGui::PushID(label.c_str());
    
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();
    
    ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
    
    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize))
      values.x = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize))
      values.y = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    
    
    ImGui::PopStyleVar();
    
    ImGui::Columns(1);
    
    ImGui::PopID();
  }
  static void DrawVector3Control(const std::string& label, Math::Vector3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
  {
    CANDY_PROFILE_FUNCTION();
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];
    
    ImGui::PushID(label.c_str());
    
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();
    
    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
    
    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize))
      values.x = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize))
      values.y = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize))
      values.z = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    
    ImGui::PopStyleVar();
    
    ImGui::Columns(1);
    
    ImGui::PopID();
  }
  static void DrawVector4Control(const std::string& label, Math::Quaternion& values, float resetValue = 0.0f, float columnWidth = 100.0f)
  {
    CANDY_PROFILE_FUNCTION();
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];
    
    ImGui::PushID(label.c_str());
    
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();
    
    ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
    
    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize))
      values.x = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize))
      values.y = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize))
      values.z = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("W", buttonSize))
      values.z = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::DragFloat("##W", &values.w, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    
    ImGui::PopStyleVar();
    
    ImGui::Columns(1);
    
    ImGui::PopID();
  }
  static void DrawTextControl(const std::string& label, std::string& value, float columnWidth = 100.0f)
  {
    CANDY_PROFILE_FUNCTION();
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];
    
    ImGui::PushID(label.c_str());
    
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();
    
    ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
    
    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::InputText("##X", &value[0], value.size()+1);
    ImGui::PopItemWidth();
    
    ImGui::PopStyleVar();
    
    ImGui::Columns(1);
    
    ImGui::PopID();
  }
  
  static void DrawColorPickerControl(const std::string& label, Color& value, float columnWidth=100.0f)
  {
    CANDY_PROFILE_FUNCTION();
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];
    
    ImGui::PushID(label.c_str());
    
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();
    
    ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
    
    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::ColorEdit4("RGB", &value.r);
    ImGui::PopItemWidth();
    
    ImGui::PopStyleVar();
    
    ImGui::Columns(1);
    
    ImGui::PopID();
    
  }
  
  
  void SceneHierarchyPanel::DrawComponents(Entity entity)
  {
    CANDY_PROFILE_FUNCTION();
    if (entity.HasComponent<TagComponent>())
    {
      auto& tag = entity.GetComponent<TagComponent>().tag;
      
      char buffer[256];
      memset(buffer, 0, sizeof(buffer));
      strncpy_s(buffer, sizeof(buffer), tag.c_str(), sizeof(buffer));
      if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
      {
        tag = std::string(buffer);
      }
    }
    
    ImGui::SameLine();
    ImGui::PushItemWidth(-1);
    
    if (ImGui::Button("Add Component"))
      ImGui::OpenPopup("AddComponent");
    
    if (ImGui::BeginPopup("AddComponent"))
    {
      DisplayAddComponentEntry<MeshFilterComponent>("Mesh Filter");
      DisplayAddComponentEntry<SpriteRendererComponent>("Sprite Renderer");
      
      ImGui::EndPopup();
    }
    
    ImGui::PopItemWidth();
    
    
    
    DrawComponent<TransformComponent>("Transform", entity, [](auto& component)
    {
    Math::Vector3 position = component.GetLocalPosition();
    Math::Vector3 scale = component.GetLocalScale();
    Math::Quaternion rotation = component.GetLocalRotation();
    
    DrawVector3Control("Position", position);
    //DrawVector3Control("Rotation", rotationEuler);
    DrawVector4Control("Rotation", rotation);
    DrawVector3Control("Scale", scale, 1.0f);
    
    component.SetLocal(position, rotation, scale);
    });
    
    if (entity.HasComponent<CircleRendererComponent>())
    {
      DrawComponent<CircleRendererComponent>("Circle Renderer", entity, [](auto& component)
      {
      DrawColorPickerControl("Color", component.color);
      DrawFloatControl("Thickness", component.thickness, 0.0f, 1.0f);
      DrawFloatControl("Fade", component.fade, 0.0f, 1.0f);
      });
    }
    
    if (entity.HasComponent<LineRendererComponent>())
    {
      DrawComponent<LineRendererComponent>("Line Renderer", entity, [](auto& component)
      {
      DrawColorPickerControl("Color", component.color);
      DrawVector3Control("Start", component.start, 0.0f);
      DrawVector3Control("End", component.end, 0.0f);
      DrawFloatControl("Thickness", component.thickness);
      });
    }
    if (entity.HasComponent<TextRendererComponent>())
    {
      
      DrawComponent<TextRendererComponent>("Text Renderer", entity, [](auto& component)
      {
        char* str = component.text.data();
        ImGui::InputText("Text", str, 100);
        
        std::string comboItems;
        const auto& fontNames = FontManager::GetFontNames();
        size_t counter=0;
        int currentIndex=-1;
        for (const auto& name : fontNames)
        {
          comboItems += name;
          comboItems.push_back('\0');
          if (component.font->GetName() == name)
          {
            currentIndex = (int)counter;
          }
          counter++;
        }
        CANDY_CORE_ASSERT(currentIndex >= 0);
        if (ImGui::Combo("Fonts", &currentIndex, comboItems.c_str()))
        {
          // Font Selection has changed. Update the font
          if (currentIndex >= 0)
          {
            std::string fontName = fontNames[currentIndex];
            SharedPtr<Font> font = FontManager::GetFont(fontName);
            CANDY_CORE_ASSERT(font);
            if (! font->IsLoaded())
            {
              bool loaded = font->Load();
              CANDY_CORE_ASSERT(loaded);
              
            }
            component.font = font;
          }
          
        }
        DrawColorPickerControl("Color", component.color);
        DrawFloatControl("Kerning", component.kerning);
        DrawFloatControl("Line Spacing", component.lineSpacing);
        component.text = str;
      
      
      });
    }
    
    
    
    
  }
  
  template<typename T>
  void SceneHierarchyPanel::DisplayAddComponentEntry(const std::string& entryName) {
    CANDY_PROFILE_FUNCTION();
    if (!selectionContext.HasComponent<T>())
    {
      if (ImGui::MenuItem(entryName.c_str()))
      {
        selectionContext.AddComponent<T>();
        ImGui::CloseCurrentPopup();
      }
    }
  }
}