#include <candy/math/direction/Direction3.hpp>
#include <candy/math/MathOps.hpp>


namespace Candy::Math
{
  
  const Vector3 Direction3::directionVectors[27] = {Vector3::left, Vector3::right, Vector3::up, Vector3::down, Vector3::downLeft, Vector3::downRight, Vector3::upLeft, Vector3::upRight, Vector3::forward, Vector3::back, Vector3::upForward, Vector3::upBack, Vector3::upLeftForward, Vector3::upLeftBack, Vector3::upRightForward, Vector3::upRightBack, Vector3::downForward, Vector3::downBack, Vector3::downLeftForward, Vector3::downLeftBack, Vector3::downRightForward, Vector3::downRightBack,
                                                    Vector3::leftBack, Vector3::rightBack, Vector3::leftForward, Vector3::rightForward, Vector3::zero};
  
  const Direction Direction3::directionArray[3][3][3] = {{ // leftX
                                                         {DOWN_LEFT_BACK,  DOWN_LEFT,  DOWN_LEFT_FORWARD}, // down
                                                                                                            {LEFT_BACK,  LEFT,  LEFT_FORWARD}, // middleY
                                                                                                                                                {UP_LEFT_BACK,  UP_LEFT,  UP_LEFT_FORWARD}, // up
                                                         },
                                                         { // middleX
                                                         {DOWN_BACK,       DOWN,       DOWN_FORWARD}, //down
                                                                                                            {BACK,       NONE,  FORWARD}, // middleY
                                                                                                                                                {UP_BACK,       UP,       UP_FORWARD}, // up
                                                         },
                                                         { // rightX
                                                         {DOWN_RIGHT_BACK, DOWN_RIGHT, DOWN_RIGHT_FORWARD}, {RIGHT_BACK, RIGHT, RIGHT_FORWARD}, {UP_RIGHT_BACK, UP_RIGHT, UP_RIGHT_FORWARD},}};
  
  const Direction Direction3::oppositeDirections[27] = {RIGHT, LEFT, DOWN, UP, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT, BACK, FORWARD, DOWN_BACK, DOWN_FORWARD, DOWN_RIGHT_BACK, DOWN_RIGHT_FORWARD, DOWN_LEFT_BACK, DOWN_LEFT_FORWARD, UP_BACK, UP_FORWARD, UP_RIGHT_BACK, UP_RIGHT_FORWARD, UP_LEFT_BACK, UP_LEFT_FORWARD, RIGHT_FORWARD, LEFT_FORWARD, RIGHT_BACK, LEFT_BACK, NONE};
  
  Direction3::Direction3(Direction direction) : value(direction) {}
  
  Direction3::Direction3(const Direction3 &other) = default;
  
  Direction3 Direction3::ClosestDirectionTo(const Vector2 &vec)
  {
    Vector2 normalizedVector = vec.Normalized();
    int x = RoundToInt(normalizedVector.x)+1;
    int y = RoundToInt(normalizedVector.y)+1;
    int z = 1;
    return directionArray[x][y][z];
  }
  
  Direction3 Direction3::ClosestDirectionTo(const Vector3 &vec)
  {
    Vector3 normalizedVector = vec.Normalized();
    int x = RoundToInt(normalizedVector.x)+1;
    int y = RoundToInt(normalizedVector.y)+1;
    int z = RoundToInt(normalizedVector.z)+1;
    return directionArray[x][y][z];
  }
  
  Vector3i Direction3::NeighborUp(const Vector3i &vec)
  {
    return {vec.x, vec.y+1, vec.z};
  }
  
  Vector3i Direction3::NeighborDown(const Vector3i &vec)
  {
    return {vec.x, vec.y-1, vec.z};
  }
  
  Vector3i Direction3::NeighborLeft(const Vector3i &vec)
  {
    return {vec.x-1, vec.y, vec.z};
  }
  
  Vector3i Direction3::NeighborRight(const Vector3i &vec)
  {
    return {vec.x + 1, vec.y, vec.z};
  }
  Vector3i Direction3::NeighborForward(const Vector3i& vec)
  {
    return {vec.x, vec.y, vec.z + 1};
  }
  Vector3i Direction3::NeighborBack(const Vector3i& vec)
  {
    return {vec.x, vec.y, vec.z - 1};
  }
  
  
  
  
  Direction3::operator std::int8_t() const { return value; }
  
  std::ostream &operator<<(Direction3 direction, std::ostream &ostream) {
    ostream << direction.ToString();
    return ostream;
  }
  
  std::string Direction3::ToString(bool classicFormat) const {
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
          return "Down-Right";
        case FORWARD:
          return "Forward";
        case BACK:
          return "Back";
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
        case FORWARD:
          return "Forward";
        case BACK:
          return "Back";
        default:
          return "None";
      }
    }
    
  }
  
  Direction3 Direction3::Opposite() const {
    return oppositeDirections[value];
  }
  
  Direction3 Direction3::Compliment() const {
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
  
  Vector2 Direction3::ToVector2() const {
    return (Vector2) directionVectors[value];
  }
  
  Vector3 Direction3::ToVector3() const {
    return directionVectors[value];
  }
  
  Vector4 Direction3::ToVector4() const {
    return directionVectors[value];
  }
  
  bool Direction3::IsPositive() const {
    switch (value) {
      case RIGHT:
      case UP_RIGHT:
      case UP:
      case UP_RIGHT_FORWARD:
      case FORWARD:
      case UP_FORWARD:
        return true;
      default:
        return false;
    }
  }
  
  bool Direction3::IsNegative() const {
    switch (value) {
      case LEFT:
      case DOWN_LEFT:
      case DOWN:
      case DOWN_LEFT_BACK:
      case DOWN_BACK:
      case BACK:
        return true;
      default:
        return false;
    }
  }
  
}