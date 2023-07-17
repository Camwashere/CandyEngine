#include <candy/math/direction/Direction2.hpp>
#include <candy/math/MathOps.hpp>
namespace Candy::Math{
  
  
  const Vector2 Direction2::directionVectors[] = {Vector2::left, Vector2::right,
                                                  Vector2::up,
                                                  Vector2::down, Vector2::negativeOne,
                                                  Vector2::downRight, Vector2::upLeft,
                                                  Vector2::one, Vector2::zero};
  
  
  const Direction Direction2::directionArray[3][3]={
  {DOWN_LEFT, LEFT, UP_LEFT},
  {DOWN, NONE, UP},
  {DOWN_RIGHT, RIGHT, UP_RIGHT},
  };
  
  
  const Direction Direction2::directionOpposites[9]={RIGHT, LEFT, DOWN, UP, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT, NONE};
  
  const Direction Direction2::imGuiDirections[9]={0, 1, 2, 3, -1, -1, -1, -1, -1};
  
  
  Direction2 Direction2::ClosestDirectionTo(const Vector2& vec)
  {
    Vector2 normalizedVector = vec.Normalized();
    int x = RoundToInt(normalizedVector.x)+1;
    int y = RoundToInt(normalizedVector.y)+1;
    
    return directionArray[x][y];
  }
  
  Direction2::Direction2() : value(Direction2::NONE){}
  
  Direction2::Direction2(Direction direction) : value(direction) {}
  
  Direction2::Direction2(const Direction2& other) = default;
  
  
  Direction2::operator std::int8_t() const { return value; }
  
  std::ostream &operator<<(Direction2 direction, std::ostream &ostream) {
    ostream << direction.ToString();
    return ostream;
  }
  
  std::string Direction2::ToString(bool classicFormat) const {
    if (classicFormat) {
      switch (value) {
        case LEFT:
          return "Left";
        case RIGHT:
          return "Right";
        case UP:
          return "Up";
        case DOWN:
          return "Down";
        case UP_LEFT:
          return "Up-Left";
        case UP_RIGHT:
          return "Up-Right";
        case DOWN_LEFT:
          return "Down-Left";
        case DOWN_RIGHT:
          return "Down_Right";
        default:
          return "None";
      }
      
    } else {
      switch (value) {
        case WEST:
          return "West";
        case EAST:
          return "East";
        case NORTH:
          return "NORTH";
        case SOUTH:
          return "SOUTH";
        case NORTH_WEST:
          return "Northwest";
        case NORTH_EAST:
          return "Northeast";
        case SOUTH_WEST:
          return "Southwest";
        case SOUTH_EAST:
          return "Southeast";
        default:
          return "None";
      }
    }
    
  }
  
  Direction2 Direction2::Opposite() const {
    return directionOpposites[value];
  }
  
  Direction2 Direction2::Compliment() const {
    switch (value) {
      case LEFT:
        return DOWN;
      case RIGHT:
        return UP;
      case UP:
        return RIGHT;
      case DOWN:
        return LEFT;
      default:
        return NONE;
    }
  }
  
  Vector2 Direction2::ToVector2() const {
    return directionVectors[value];
  }
  
  Vector3 Direction2::ToVector3() const {
    return directionVectors[value];
  }
  
  Vector4 Direction2::ToVector4() const {
    return directionVectors[value];
  }
  int Direction2::ToImGuiDir()const{
    return imGuiDirections[value];
    
  }
  
  bool Direction2::IsPositive() const {
    switch (value) {
      case RIGHT:
      case UP_RIGHT:
      case UP:
        return true;
      default:
        return false;
    }
  }
  
  bool Direction2::IsNegative() const {
    switch (value) {
      case LEFT:
      case DOWN_LEFT:
      case DOWN:
        return true;
      default:
        return false;
    }
  }
}
