#pragma once
#include "../vector/VectorAll.hpp"
#include <Candy/CandyEngineBase.hpp>
#include <xmmintrin.h>

namespace Candy::Math{
    
        struct Matrix4{
        private:
            static constexpr std::size_t ROW_SIZE=4;
            static constexpr std::size_t COLUMN_SIZE=4;
            static constexpr std::size_t TOTAL_SIZE=16;
        
        public:
            static const Matrix4 Identity;
        private:
            union
            {
                alignas(16) std::array<float, 16> data;
                alignas(16) std::array<Vector4, 4> columns;
                alignas(16) __m128 matrix[4];
            };
        
        
        
        private:
            static constexpr std::size_t AccessIndex(std::size_t row, std::size_t column){return row+column*ROW_SIZE;}
        
        public:
        public:
            Matrix4();
            Matrix4(float diagonal);
            Matrix4(const Vector4& diagonal);
            
            template<Numeric... T>
            Matrix4(T... elements)
            {
                //CANDY_CORE_ASSERT(sizeof...(elements)==16);
                std::size_t size = sizeof...(elements);
                //data.fill({elements...});
                int count=0;
                if (size<TOTAL_SIZE)
                {
                    data.fill(0.0f);
                }
                for(auto element : {elements...})
                {
                    data[count]=element;
                    count++;
                }
            }
            Matrix4(std::initializer_list<float> elements);
            Matrix4(const Matrix4& other);
            Matrix4(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3);
        
        
        
        public:
            static Matrix4 Eye();
            
            static Matrix4 Diagonal(float value);
            
            static Matrix4 Diagonal(const Vector4& value);
            
            static Matrix4 Diagonal(float v0, float v1, float v2, float v3);
            
            static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
            
            static Matrix4 Perspective(float fov, float aspectRatio, float near, float far);
            
            static Matrix4 LookAt(const Vector3 &camera, const Vector3 &object, const Vector3 &up);
            
            static Matrix4 Translation(const Vector3 &translation);
            
            static Matrix4 Rotated(const Matrix4 &matrix, float angle, const Vector3 &axis);
            
            static Matrix4 Rotated(float angle, const Vector3 &axis);
            
            static Matrix4 Rotated(const Quaternion &quat);
            
            static Matrix4 Scaled(const Vector3 &scale);
            
            static Matrix4 Scaled(const Matrix4 &mat, const Vector3 &scale);
            
            static Matrix4 Invert(const Matrix4 &matrix);
            
            static Matrix4 CreateFromRows(const Vector4& r0, const Vector4& r1, const Vector4& r2, const Vector4& r3);
            
            static Matrix4 CreateFromColumns(const Vector4& c0, const Vector4& c1, const Vector4& c2, const Vector4& c3);
            
            static Matrix4 Transpose(const Matrix4 &matrix);
            
            static bool DecomposeTransform(const Matrix4& transform, Vector3& translation, Vector3& rotation, Vector3& scale);
        
            static bool EpsilonEqual(float x, float y, float epsilon);
            static bool EpsilonNotEqual(float x, float y, float epsilon);
        
        
        
        public:
            float GetEntry(std::size_t row, std::size_t col) const { return data[AccessIndex(row, col)]; }
            void SetEntry(std::size_t row, std::size_t col, const float &value) { data[AccessIndex(row, col)] = value; }
            float &Entry(std::size_t row, std::size_t col) { return data[AccessIndex(row, col)]; }
            float GetEntry(std::size_t access) const { return data[access]; }
            void SetEntry(std::size_t access, const float &value) { data[access] = value; }
            float &Entry(std::size_t access) { return data[access]; }
            
            float& operator[](std::size_t index){return data[index];}
            float operator[](std::size_t index)const{return data[index];}
            float& operator[](std::size_t row, std::size_t column){return data[AccessIndex(row, column)];}
            float operator[](std::size_t row, std::size_t column)const{return data[AccessIndex(row, column)];}
            
            bool operator==(const Matrix4& other)const{return data == other.data;}
            bool operator!=(const Matrix4& other)const{return data != other.data;}
            Matrix4 operator+(const Matrix4& other)const;
            Matrix4 operator-(const Matrix4& other)const;
            Matrix4 operator*(const Matrix4& other) const;
            
            Vector3 operator*(const Vector3& other)const;
            Vector4 operator*(const Vector4& other)const;
            friend std::ostream &operator<<(std::ostream &ostream, const Matrix4 &mat);
            inline const float *ValuePtr() const { return &data[0]; }
        
        
        
        
        public:
            void SetRow(unsigned int index, const Vector4 &row);
            
            void SetColumn(unsigned int index, const Vector4 &column);
            
            void SetPosition(const Vector3 &position);
            
            Vector4 GetRow(int index) const;
            
            Vector4 GetColumn(int index) const;
            
            Vector3 GetPosition() const;
            
            void Translate(const Vector3 &offset);
            
            void Scale(const Vector3 &scale);
            
            
            void RotateX(float angle);
            
            void RotateY(float angle);
            
            void RotateZ(float angle);
            
            Matrix4 &Invert();
            
            constexpr inline std::size_t ColumnSize()const{return COLUMN_SIZE;}
            constexpr inline std::size_t RowSize()const{return ROW_SIZE;}
            constexpr inline std::size_t TotalSize()const{return TOTAL_SIZE;}
            void PrintFlat()const;
            
            
        };
}

