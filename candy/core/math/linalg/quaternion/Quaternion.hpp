#pragma once

#include "../LinalgForwardDef.hpp"

namespace Candy::Math{
        struct Quaternion : public VectorBase<float, 4>{
        
        public:
            static const Quaternion identity;
        public:
            static Quaternion FromEulerAngles(const Vector3 &angles);
            
            static Vector3 Rotate(const Quaternion &quat, const Vector3 &vec);
            
            static Quaternion Rotation(const Vector3 &unitVec0, const Vector3 &unitVec1);
            
            static Quaternion Rotation(float radians, const Vector3 &unitVec);
            
            static Quaternion RotationX(float radians);
            
            static Quaternion RotationY(float radians);
            
            static Quaternion RotationZ(float radians);
        
        public:
            Quaternion();
            
            Quaternion(const Quaternion &quaternion);
            
            Quaternion(float x, float y, float z, float w);
            
            Quaternion(const Vector3 &xyz, float w);
            
            Quaternion(const Vector4 &vec);
            
            Quaternion(float scalar);
            
            template <typename E>
            constexpr Quaternion(const VectorExpression<float, E>& expr) : VectorBase<float, 4>(expr){}
            
            
            Vector3 GetVector3() const;
            
            Matrix4 ToMatrix() const;
            
            
            Vector3 GetAxis() const;
            
            Vector3 ToEulerAngles() const;
            
            float Norm() const;
            
            Quaternion Normalized() const;
            
            Quaternion NormalizedEst() const;
            
            void Normalize();
            
            
            
            float &operator[](int index);
            
            float operator[](int index) const;
            
            void operator+=(const Quaternion &other);
            
            void operator-=(const Quaternion &Quaternion);
            
            void operator*=(const Quaternion &Quaternion);
            
            void operator*=(float scalar);
            
            void operator/=(float scalar);
            
            const Quaternion operator-() const;
            
            bool operator==(const Quaternion &quaternion) const;
            
            bool operator!=(const Quaternion &quaternion) const;
            
            float Dot(const Quaternion &other) const;
            
            Quaternion Conjugate() const;
            
        };
}

