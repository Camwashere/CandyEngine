#pragma once

#include "VectorBase.hpp"

namespace Candy::Math
{
    template<typename T, size_t DIMENSIONS, typename Enable = void>
    struct VectorBaseStaticData;
    
    
    // VECTOR 2
    
    // Signed
    template<typename T>
    struct VectorBaseStaticData<T, 2, typename std::enable_if<std::is_signed<T>::value>::type>
    {
        static inline const VectorBase<T, 2> up = {0, 1};
        static inline const VectorBase<T, 2> down = {0, -1};
        static inline const VectorBase<T, 2> left = {-1, 0};
        static inline const VectorBase<T, 2> right = {1, 0};
        static inline const VectorBase<T, 2> zero = {0, 0};
        static inline const VectorBase<T, 2> one = {1, 1};
        static inline const VectorBase<T, 2> upLeft = {-1, 1};
        static inline const VectorBase<T, 2> upRight = {1, 1};
        static inline const VectorBase<T, 2> downLeft = {-1, -1};
        static inline const VectorBase<T, 2> downRight = {1, 1};
        static inline const VectorBase<T, 2> negativeOne = {-1, -1};
        static inline const VectorBase<T, 2> positiveInfinity = {Limit<T>::Max(), Limit<T>::Max()};
        static inline const VectorBase<T, 2> negativeInfinity = {Limit<T>::Min(), Limit<T>::Min()};
    };
    
    // Unsigned
    template<typename T>
    struct VectorBaseStaticData<T, 2, typename std::enable_if<std::is_unsigned<T>::value>::type>
    {
        static inline const VectorBase<T, 2> up = {0, 1};
        static inline const VectorBase<T, 2> right = {1, 0};
        static inline const VectorBase<T, 2> zero = {0, 0};
        static inline const VectorBase<T, 2> one = {1, 1};
    };
    
    
    // VECTOR 3
    template<typename T>
    struct VectorBaseStaticData<T, 3, typename std::enable_if<std::is_signed<T>::value>::type>
    {
        static inline const VectorBase<T, 3> up = {0, 1, 0};
        static inline const VectorBase<T, 3> down = {0, -1, 0};
        static inline const VectorBase<T, 3> left = {-1, 0, 0};
        static inline const VectorBase<T, 3> right = {1, 0, 0};
        static inline const VectorBase<T, 3> forward = {0, 0, 1};
        static inline const VectorBase<T, 3> back = {0, 0, -1};
        static inline const VectorBase<T, 3> upLeft = {-1, 1, 0};
        static inline const VectorBase<T, 3> upRight = {1, 1, 0};
        static inline const VectorBase<T, 3> upForward = {0, 1, 1};
        static inline const VectorBase<T, 3> upBack = {0, 1, -1};
        static inline const VectorBase<T, 3> leftBack = {-1, 0, -1};
        static inline const VectorBase<T, 3> rightBack = {1, 0, -1};
        static inline const VectorBase<T, 3> leftForward = {-1, 0, 1};
        static inline const VectorBase<T, 3> rightForward = {1, 0, 1};
        static inline const VectorBase<T, 3> upLeftForward = {-1, 1, 1};
        static inline const VectorBase<T, 3> upLeftBack = {-1, 1, -1};
        static inline const VectorBase<T, 3> upRightForward = {1, 1, 1};
        static inline const VectorBase<T, 3> upRightBack = {1, 1, -1};
        static inline const VectorBase<T, 3> downLeft = {-1, -1, 0};
        static inline const VectorBase<T, 3> downRight = {1, -1, 0};
        static inline const VectorBase<T, 3> downForward = {0, -1, 1};
        static inline const VectorBase<T, 3> downBack = {0, -1, -1};
        static inline const VectorBase<T, 3> downLeftForward = {-1, -1, 1};
        static inline const VectorBase<T, 3> downLeftBack = {-1, -1, -1};
        static inline const VectorBase<T, 3> downRightForward = {1, -1, 1};
        static inline const VectorBase<T, 3> downRightBack = {1, -1, -1};
        static inline const VectorBase<T, 3> zero = {0, 0, 0};
        static inline const VectorBase<T, 3> one = {1, 1, 1};
        static inline const VectorBase<T, 3> negativeOne = {-1, -1, -1};
        static inline const VectorBase<T, 3> positiveInfinity = {Limit<T>::Max(), Limit<T>::Max(), Limit<T>::Max()};
        static inline const VectorBase<T, 3> negativeInfinity = {Limit<T>::Min(), Limit<T>::Min(), Limit<T>::Min()};
    };
    
    // Unsigned
    template<typename T>
    struct VectorBaseStaticData<T, 3, typename std::enable_if<std::is_unsigned<T>::value>::type>
    {
        static inline const VectorBase<T, 3> up = {0, 1, 0};
        static inline const VectorBase<T, 3> right = {1, 0, 0};
        static inline const VectorBase<T, 3> forward = {0, 0, 1};
        
        static inline const VectorBase<T, 3> upRight = {1, 1, 0};
        static inline const VectorBase<T, 3> upForward = {0, 1, 1};
        
        static inline const VectorBase<T, 3> rightForward = {1, 0, 1};
        static inline const VectorBase<T, 3> upRightForward = {1, 1, 1};
        static inline const VectorBase<T, 3> zero = {0, 0, 0};
        static inline const VectorBase<T, 3> one = {1, 1, 1};
        static inline const VectorBase<T, 3> positiveInfinity = {Limit<T>::Max(), Limit<T>::Max(), Limit<T>::Max()};
    };
    
    
    // VECTOR 4
    template<typename T>
    struct VectorBaseStaticData<T, 4, typename std::enable_if<std::is_signed<T>::value>::type>
    {
        static inline const VectorBase<T, 4> up = {0, 1, 0};
        static inline const VectorBase<T, 4> down = {0, -1, 0};
        static inline const VectorBase<T, 4> left = {-1, 0, 0};
        static inline const VectorBase<T, 4> right = {1, 0, 0};
        static inline const VectorBase<T, 4> forward = {0, 0, 1};
        static inline const VectorBase<T, 4> back = {0, 0, -1};
        static inline const VectorBase<T, 4> upLeft = {-1, 1, 0};
        static inline const VectorBase<T, 4> upRight = {1, 1, 0};
        static inline const VectorBase<T, 4> upForward = {0, 1, 1};
        static inline const VectorBase<T, 4> upBack = {0, 1, -1};
        static inline const VectorBase<T, 4> leftBack = {-1, 0, -1};
        static inline const VectorBase<T, 4> rightBack = {1, 0, -1};
        static inline const VectorBase<T, 4> leftForward = {-1, 0, 1};
        static inline const VectorBase<T, 4> rightForward = {1, 0, 1};
        static inline const VectorBase<T, 4> upLeftForward = {-1, 1, 1};
        static inline const VectorBase<T, 4> upLeftBack = {-1, 1, -1};
        static inline const VectorBase<T, 4> upRightForward = {1, 1, 1};
        static inline const VectorBase<T, 4> upRightBack = {1, 1, -1};
        static inline const VectorBase<T, 4> downLeft = {-1, -1, 0};
        static inline const VectorBase<T, 4> downRight = {1, -1, 0};
        static inline const VectorBase<T, 4> downForward = {0, -1, 1};
        static inline const VectorBase<T, 4> downBack = {0, -1, -1};
        static inline const VectorBase<T, 4> downLeftForward = {-1, -1, 1};
        static inline const VectorBase<T, 4> downLeftBack = {-1, -1, -1};
        static inline const VectorBase<T, 4> downRightForward = {1, -1, 1};
        static inline const VectorBase<T, 4> downRightBack = {1, -1, -1};
        static inline const VectorBase<T, 4> zero = {0, 0, 0};
        static inline const VectorBase<T, 4> one = {1, 1, 1};
        static inline const VectorBase<T, 4> negativeOne = {-1, -1, -1};
        static inline const VectorBase<T, 4> positiveInfinity = {Limit<T>::Max(), Limit<T>::Max(), Limit<T>::Max()};
        static inline const VectorBase<T, 4> negativeInfinity = {Limit<T>::Min(), Limit<T>::Min(), Limit<T>::Min()};
    };
    
    // Unsigned
    template<typename T>
    struct VectorBaseStaticData<T, 4, typename std::enable_if<std::is_unsigned<T>::value>::type>
    {
        static inline const VectorBase<T, 4> up = {0, 1, 0};
        static inline const VectorBase<T, 4> right = {1, 0, 0};
        static inline const VectorBase<T, 4> forward = {0, 0, 1};
        static inline const VectorBase<T, 4> upRight = {1, 1, 0};
        static inline const VectorBase<T, 4> upForward = {0, 1, 1};
        
        static inline const VectorBase<T, 4> rightForward = {1, 0, 1};
        static inline const VectorBase<T, 4> upRightForward = {1, 1, 1};
        static inline const VectorBase<T, 4> zero = {0, 0, 0};
        static inline const VectorBase<T, 4> one = {1, 1, 1};
        static inline const VectorBase<T, 4> positiveInfinity = {Limit<T>::Max(), Limit<T>::Max(), Limit<T>::Max()};
    };
}