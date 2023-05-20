#include "BlockType.hpp"
#include "BlockTypeManager.hpp"
namespace Candy::Voxel {
        BlockType::BlockType() : name("Air")
        {


        }
        BlockType::BlockType(std::string blockName, uint facesID) : name(blockName)
        {
            faces.fill(facesID);
        }
}