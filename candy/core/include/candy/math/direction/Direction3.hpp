#pragma once
#include "../Vector.hpp"
namespace Candy::Math
{
  
  typedef int8_t Direction;
  class Direction3
  {
  private:
    static const Vector3 directionVectors[27];
    static const Direction directionArray[3][3][3];
    static const Direction oppositeDirections[27];
  public:
    static constexpr Direction LEFT = 0, WEST = 0;
    static constexpr Direction RIGHT = 1, EAST = 1;
    static constexpr Direction UP = 2, NORTH = 2;
    static constexpr Direction DOWN = 3, SOUTH = 3;
    static constexpr Direction DOWN_LEFT = 4, SOUTH_WEST = 4;
    static constexpr Direction DOWN_RIGHT = 5, SOUTH_EAST = 5;
    static constexpr Direction UP_LEFT = 6, NORTH_WEST = 6;
    static constexpr Direction UP_RIGHT = 7, NORTH_EAST = 7;
    static constexpr Direction FORWARD = 8;
    static constexpr Direction BACK = 9;
    static constexpr Direction UP_FORWARD = 10;
    static constexpr Direction UP_BACK = 11;
    static constexpr Direction UP_LEFT_FORWARD = 12;
    static constexpr Direction UP_LEFT_BACK = 13;
    static constexpr Direction UP_RIGHT_FORWARD = 14;
    static constexpr Direction UP_RIGHT_BACK = 15;
    static constexpr Direction DOWN_FORWARD = 16;
    static constexpr Direction DOWN_BACK = 17;
    static constexpr Direction DOWN_LEFT_FORWARD = 18;
    static constexpr Direction DOWN_LEFT_BACK = 19;
    static constexpr Direction DOWN_RIGHT_FORWARD = 20;
    static constexpr Direction DOWN_RIGHT_BACK = 21;
    static constexpr Direction LEFT_BACK=22;
    static constexpr Direction RIGHT_BACK=23;
    static constexpr Direction LEFT_FORWARD=24;
    static constexpr Direction RIGHT_FORWARD=25;
    static constexpr Direction NONE = 26;
  
  public:
    static Direction3 ClosestDirectionTo(const Vector3& vec);
    static Direction3 ClosestDirectionTo(const  Vector2& vec);
    static Vector3i NeighborUp(const Vector3i& vec);
    static Vector3i NeighborDown(const Vector3i& vec);
    static Vector3i NeighborLeft(const Vector3i& vec);
    static Vector3i NeighborRight(const Vector3i& vec);
    static Vector3i NeighborForward(const Vector3i& vec);
    static Vector3i NeighborBack(const Vector3i& vec);
  
  private:
    Direction value;
  
  
  public:
    Direction3(Direction direction);
    Direction3(const Direction3& other);
  
  
  public:
    
    operator int8_t() const;
    
    friend std::ostream &operator<<(Direction3 direction, std::ostream &ostream);
  
  public:
    [[nodiscard]] std::string ToString(bool classicFormat = true) const;
    
    [[nodiscard]] Direction3 Opposite() const;
    
    [[nodiscard]] Direction3 Compliment() const;
    
    [[nodiscard]] Vector2 ToVector2() const;
    
    [[nodiscard]] Vector3 ToVector3() const;
    
    [[nodiscard]] Vector4 ToVector4() const;
    
    [[nodiscard]] bool IsPositive() const;
    
    [[nodiscard]] bool IsNegative() const;
    
  };
}