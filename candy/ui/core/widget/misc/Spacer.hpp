#pragma once
#include "../base/WidgetBase.hpp"
namespace Candy::UI{
    class Spacer : public WidgetBase
    {
    private:
        int amount;

    public:
        Spacer() : amount(1){}
        Spacer(int amountValue) : amount(amountValue){}

    public:
        void OnRender()override{

            for (int i=0; i<amount; i++)
            {
                ImGui::Spacing();
            }

        }

    public:
        void SetAmount(int value){amount=value;}
        int GetAmount()const{return amount;}

    };
}
