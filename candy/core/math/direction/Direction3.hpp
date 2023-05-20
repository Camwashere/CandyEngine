#pragma once
#include "Direction2.hpp"

namespace Candy::Math{
        
        class Direction3 {
        private:
            static const Vector3 directionVectors[27];
            static const Direction directionArray[3][3][3];
            static const Direction oppositeDirections[27];
        private:
            Direction value;
        public:
            constexpr static Direction LEFT = 0, WEST = 0;
            constexpr static Direction RIGHT = 1, EAST = 1;
            constexpr static Direction UP = 2, NORTH = 2;
            constexpr static Direction DOWN = 3, SOUTH = 3;
            constexpr static Direction DOWN_LEFT = 4, SOUTH_WEST = 4;
            constexpr static Direction DOWN_RIGHT = 5, SOUTH_EAST = 5;
            constexpr static Direction UP_LEFT = 6, NORTH_WEST = 6;
            constexpr static Direction UP_RIGHT = 7, NORTH_EAST = 7;
            constexpr static Direction FORWARD = 8;
            constexpr static Direction BACK = 9;
            constexpr static Direction UP_FORWARD = 10;
            constexpr static Direction UP_BACK = 11;
            constexpr static Direction UP_LEFT_FORWARD = 12;
            constexpr static Direction UP_LEFT_BACK = 13;
            constexpr static Direction UP_RIGHT_FORWARD = 14;
            constexpr static Direction UP_RIGHT_BACK = 15;
            constexpr static Direction DOWN_FORWARD = 16;
            constexpr static Direction DOWN_BACK = 17;
            constexpr static Direction DOWN_LEFT_FORWARD = 18;
            constexpr static Direction DOWN_LEFT_BACK = 19;
            constexpr static Direction DOWN_RIGHT_FORWARD = 20;
            constexpr static Direction DOWN_RIGHT_BACK = 21;
            constexpr static Direction LEFT_BACK=22;
            constexpr static Direction RIGHT_BACK=23;
            constexpr static Direction LEFT_FORWARD=24;
            constexpr static Direction RIGHT_FORWARD=25;
            constexpr static Direction NONE = 26;
        
        public:
            static Direction3 ClosestDirectionTo(const Vector3& vec);
            static Direction3 ClosestDirectionTo(const  Vector2& vec);
        
        
        public:
            Direction3(Direction direction);
            Direction3(const Direction3& other);
        
        
        public:
            
            operator int8() const;
            
            friend std::ostream &operator<<(Direction3 direction, std::ostream &ostream);
        
        public:
            std::string ToString(bool classicFormat = true) const;
            
            Direction3 Opposite() const;
            
            Direction3 Compliment() const;
            
            Vector2 ToVector2() const;
            
            Vector3 ToVector3() const;
            
            Vector4 ToVector4() const;
            
            bool IsPositive() const;
            
            bool IsNegative() const;
        };
}
