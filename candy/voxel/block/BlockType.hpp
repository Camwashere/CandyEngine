#pragma once
#include <Candy/CandyEngineCore.hpp>
namespace Candy::Voxel {
        class BlockTypeManager;
        class BlockType {
        private:
            ushort id;
            std::string name;
            union {
                uint frontFace, backFace, leftFace, rightFace, topFace, bottomFace;
                std::array<uint, 6> faces;
            };

        public:
            BlockType();

            BlockType(std::string blockName, uint facesID);

        public:
            constexpr bool operator==(const BlockType &other) const { return id == other.id; }

            constexpr bool operator!=(const BlockType &other) const { return id != other.id; }

            constexpr operator ushort() const { return id; }

        public:
            inline void SetName(const std::string &blockName) { name = blockName; }

            inline void SetID(ushort blockID) { id = blockID; }

            inline void SetFrontFace(uint value) { frontFace = value; }

            inline void SetBackFace(uint value) { backFace = value; }

            inline void SetLeftFace(uint value) { leftFace = value; }

            inline void SetRightFace(uint value) { rightFace = value; }

            inline void SetTopFace(uint value) { topFace = value; }

            inline void SetBottomFace(uint value) { bottomFace = value; }

            inline void SetFace(uint index, uint value) { faces[index] = value; }

            inline std::string GetName() const { return name; }

            inline uint GetFrontFace() const { return frontFace; }

            inline uint GetBackFace() const { return backFace; }

            inline uint GetLeftFace() const { return leftFace; }

            inline uint GetRightFace() const { return rightFace; }

            inline uint GetTopFace() const { return topFace; }

            inline uint GetBottomFace() const { return bottomFace; }

            inline uint GetFace(uint index) const { return faces[index]; }

            inline bool IsEmpty()const{return id==0;}


        public:
            friend BlockTypeManager;


        };
}
