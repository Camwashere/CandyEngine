#pragma once
#include <Candy/CandyEngineBase.hpp>
struct ImGuiViewport;
namespace Candy::UI{
    class EditorPane;
    class EditorLayout
    {
    private:
        String name;
        int windowFlags;
        int dockspaceFlags;
        ImGuiViewport* viewport;
        uint dockspaceID;

        EditorPane* leftPane;
        EditorPane* rightPane;
        EditorPane* topPane;
        EditorPane* bottomPane;

        bool needsInit;

    private:
        void Init();



    public:
        EditorLayout(const String& layoutName);

    public:
        void OnRender();

    public:
        void SetLeftPane(const String& name, float size=0.25f);
        void SetRightPane(const String& name, float size=0.25f);
        void SetTopPane(const String& name, float size=0.25f);
        void SetBottomPane(const String& name, float size=0.25f);
        EditorPane& GetLeftPane(){return *leftPane;}
        EditorPane& GetRightPane(){return *rightPane;}
        EditorPane& GetTopPane(){return *topPane;}
        EditorPane& GetBottomPane(){return *bottomPane;}
        inline const String& GetName()const{return name;}
        inline uint GetID()const{return dockspaceID;}
        inline uint& GetRefID(){return dockspaceID;}

    };

}
