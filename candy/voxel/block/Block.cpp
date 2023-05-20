#include "Block.hpp"
namespace Candy::Voxel {


        std::string Block::GetName()const
        {
            return BlockTypeManager::Instance()->GetBlockName(id);
        }
        uint Block::GetFrontFace()const
        {
            return BlockTypeManager::Instance()->GetFrontFace(id);

        }
        uint Block::GetBackFace()const
        {
            return BlockTypeManager::Instance()->GetBackFace(id);
        }
        uint Block::GetLeftFace()const
        {
            return BlockTypeManager::Instance()->GetLeftFace(id);

        }
        uint Block::GetRightFace()const
        {
            return BlockTypeManager::Instance()->GetRightFace(id);

        }
        uint Block::GetTopFace()const
        {
            return BlockTypeManager::Instance()->GetTopFace(id);
        }
        uint Block::GetBottomFace()const
        {
            return BlockTypeManager::Instance()->GetBottomFace(id);
        }
        uint Block::GetFace(uint index)const
        {
            return BlockTypeManager::Instance()->GetFace(id, index);
        }
        BlockType Block::GetType()const
        {
            return BlockTypeManager::Instance()->GetBlockType(id);
        }

}