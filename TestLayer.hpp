#pragma once
#include "candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp"
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/vulkan/Image.hpp>
#include <candy/app/Application.hpp>
#include <candy/app/Layer.hpp>
#include <candy/event/Events.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Material.hpp>
class TestLayer : public Candy::Layer
{
private:
  Candy::SharedPtr<Candy::Graphics::Shader> shader;
  Candy::SharedPtr<Candy::Graphics::VertexArray> vertexArray;
  Candy::Graphics::Material material;
  Candy::Color color;

  
public:
  TestLayer();
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnEvent(Candy::Events::Event& event)override;
  virtual void OnUpdate()override;
  virtual void OnRenderUI()override;

};
