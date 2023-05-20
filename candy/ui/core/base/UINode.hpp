#pragma once
#include <Candy/CandyEngineBase.hpp>
#include <Candy/Events.hpp>
#include <Candy/Utils.hpp>
#include "imgui.h"
#include "imgui_internal.h"
namespace Candy::UI{
    class UINode : public Events::IEventListener
    {
    private:
        inline static IDManagerInt idManager{};
    
    protected:
        UINode* parent;
        int id;
    
    public:
        UINode() : parent(nullptr), id(idManager.AssignID()){}
        UINode(UINode* parentNode) : parent(parentNode), id(idManager.AssignID()){}
        virtual ~UINode() {idManager.FreeID(id);}
    
    public:
        virtual void OnRender()=0;
        virtual void OnEvent(Events::Event& event)=0;
    
    public:
        int GetID()const{return id;}
        
        bool IsRoot()const{return parent==nullptr;}
        bool HasParent()const{return parent!=nullptr;}
        UINode& GetParent(){return *parent;}
        
        
    };
}