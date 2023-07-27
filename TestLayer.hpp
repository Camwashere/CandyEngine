#pragma once
#include "candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp"
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/vulkan/Image.hpp>
#include <candy/app/Application.hpp>
#include <candy/app/Layer.hpp>
#include <candy/event/Events.hpp>
#include <CandyPch.hpp>

class TestLayer : public Candy::Layer
{
private:
  Candy::SharedPtr<Candy::Graphics::Shader> shader;
  Candy::SharedPtr<Candy::Graphics::VertexArray> vertexArray;
  //Candy::SharedPtr<Candy::Graphics::UniformBuffer> uniformBuffer;
  Candy::Color color;
  Candy::Graphics::Texture texture;
  Candy::Graphics::ImageView textureImageView;
  Candy::Graphics::UniformBufferObject ubo{};
  //Candy::Graphics::DescriptorBuilder descriptorBuilder;
  
private:
  void CreateDescriptorSets();

public:
  TestLayer();
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnEvent(Candy::Events::Event& event)override;
  virtual void OnUpdate()override;
  virtual void OnRenderUI()override;

};
