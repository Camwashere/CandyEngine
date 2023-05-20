#pragma once
#include "BlockTypeManager.hpp"
namespace Candy::Voxel {

    class Block
    {
    private:
        ushort id;
        uint8 lightLevel;

    public:
        constexpr Block() : id(0), lightLevel(0){}
        constexpr Block(ushort blockID) : id(blockID), lightLevel(0){}
        constexpr Block(ushort blockID, uint8 blockLightLevel) : id(blockID), lightLevel(blockLightLevel){}

    public:
        constexpr operator bool()const{return id==0;}
        constexpr operator ushort()const{return id;}

    public:
        constexpr ushort GetID()const{return id;}
        constexpr uint8 GetLightLevel()const{return lightLevel;}
        std::string GetName()const;
        bool IsAir()const{return id==0;}
        uint GetFrontFace()const;
        uint GetBackFace()const;
        uint GetLeftFace()const;
        uint GetRightFace()const;
        uint GetTopFace()const;
        uint GetBottomFace()const;
        uint GetFace(uint index)const;
        BlockType GetType()const;





    };
}
