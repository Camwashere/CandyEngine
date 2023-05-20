#include "BlockTypeManager.hpp"
#include "BlockAll.hpp"
namespace Candy::Voxel {

        BlockTypeManager* BlockTypeManager::instance = new BlockTypeManager();
        BlockTypeManager::BlockTypeManager()
        {


        }

        BlockTypeManager::~BlockTypeManager()
        {

        }

        void BlockTypeManager::RegisterBlockType(BlockType& blockType)
        {
            if (blockType.id != 0)
            {
                if (blockType.id == blockTypes.size())
                {
                    blockTypes.push_back(blockType);
                }
                else if (blockType.id > blockTypes.size())
                {
                    blockTypes.resize(blockType.id+1);
                    blockTypes[blockType.id] = blockType;
                }
                else
                {
                    blockTypes[blockType.id] = blockType;
                }
            }
            else
            {
                ushort id = blockTypes.size();
                blockType.id = id;
                blockTypes.push_back(blockType);
            }
        }

        void BlockTypeManager::SetBlockName(ushort blockID, const std::string& name){
            blockTypes[blockID].name=name;
        }
        void BlockTypeManager::SetBlockType(ushort blockID, const BlockType& blockType){
            blockTypes[blockID] = blockType;
        }

}