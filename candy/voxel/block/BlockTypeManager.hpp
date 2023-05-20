#pragma once
#include "BlockType.hpp"
namespace Candy::Voxel
{
    class Block;
    class BlockTypeManager{
    private:
        static BlockTypeManager* instance;
    public:
        static BlockTypeManager* Instance(){return instance;}

    private:
        std::vector<BlockType> blockTypes;

    public:
        BlockTypeManager();
        ~BlockTypeManager();

    public:
        void RegisterBlockType(BlockType& blockType);

    public:
        inline BlockType GetBlockType(ushort id){return blockTypes[id];}
        inline std::string GetBlockName(ushort id)const{return blockTypes[id].GetName();}
        inline uint GetFrontFace(ushort id)const{return blockTypes[id].GetFrontFace();}
        inline uint GetBackFace(ushort id)const{return blockTypes[id].GetBackFace();}
        inline uint GetLeftFace(ushort id)const{return blockTypes[id].GetLeftFace();}
        inline uint GetRightFace(ushort id)const{return blockTypes[id].GetRightFace();}
        inline uint GetTopFace(ushort id)const{return blockTypes[id].GetTopFace();}
        inline uint GetBottomFace(ushort id)const{return blockTypes[id].GetBottomFace();}
        inline uint GetFace(ushort id, uint faceIndex)const{return blockTypes[id].GetFace(faceIndex);}
        inline std::array<uint, 6> GetFaces(ushort id)const{return blockTypes[id].faces;}

    public:
        void SetBlockName(ushort blockID, const std::string& name);
        void SetBlockType(ushort blockID, const BlockType& blockType);


    public:
        friend BlockType;
        



    };
}


