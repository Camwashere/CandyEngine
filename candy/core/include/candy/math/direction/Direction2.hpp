#pragma once
#include "Direction3.hpp"
namespace Candy::Math{
  
  class Direction2 {
  private:
    static const Vector2 directionVectors[9];
    static const Direction directionArray[3][3];
    static const Direction directionOpposites[9];
    static const Direction imGuiDirections[9];
  
  public:
    static constexpr Direction LEFT = 0, WEST = 0;
    static constexpr Direction RIGHT = 1, EAST = 1;
    static constexpr Direction UP = 2, NORTH = 2;
    static constexpr Direction DOWN = 3, SOUTH = 3;
    static constexpr Direction DOWN_LEFT = 4, SOUTH_WEST = 4;
    static constexpr Direction DOWN_RIGHT = 5, SOUTH_EAST = 5;
    static constexpr Direction UP_LEFT = 6, NORTH_WEST = 6;
    static constexpr Direction UP_RIGHT = 7, NORTH_EAST = 7;
    static constexpr Direction NONE = 8;
  
  public:
    static Direction2 ClosestDirectionTo(const Vector2& vec);
  
  private:
    Direction value;
  
  public:
    Direction2();
    Direction2(Direction direction);
    Direction2(const Direction2& other);
  
  public:
    operator Direction() const;
    
    friend std::ostream &operator<<(Direction2 direction, std::ostream &ostream);
  
  public:
    std::string ToString(bool classicFormat = true) const;
    
    Direction2 Opposite() const;
    
    Direction2 Compliment() const;
    
    Vector2 ToVector2() const;
    
    Vector3 ToVector3() const;
    
    Vector4 ToVector4() const;
    
    int ToImGuiDir()const;
    
    bool IsPositive() const;
    
    bool IsNegative() const;
    
    
  };
}