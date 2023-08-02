#pragma once
#include <candy/app/Layer.hpp>
#include <vulkan/vulkan.h>
namespace Candy
{
    class UILayer : public Layer
    {
    private:
      VkDescriptorPool uiPool;
      bool blockEvents=false;
    
    public:
      UILayer();
      ~UILayer()=default;
      
      virtual void OnAttach() override;
      virtual void OnDetach() override;
      virtual void OnEvent(Events::Event& e)override;
      
      void BlockEvents(bool block);
      //void Begin();
      //void End();
      
      
        
        
    };
}