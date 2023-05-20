#pragma once

#include <cstddef>
#include <array>
#include <cassert>
#include <iostream>
#include <iomanip>


namespace Candy::Math{
        template<typename T, std::size_t ROW_SIZE, std::size_t COLUMN_SIZE, std::size_t ARRAY_SIZE = ROW_SIZE * COLUMN_SIZE>
        struct Matrix {
        protected:
            std::array<T, ARRAY_SIZE> data;
        
        
        protected:
            static constexpr std::size_t AccessIndex(std::size_t row, std::size_t col){return row+col*ROW_SIZE;}
        
        public:
            Matrix() {
                data.fill(0);
            }
            
            Matrix(T diagonal) {
                data.fill(0);
                int diagonalSize = std::max(ROW_SIZE, COLUMN_SIZE);
                data[0] = diagonal;
                for (int i = 1; i < diagonalSize; i++) {
                    data[i + i * diagonalSize] = diagonal;
                }
            }
            
            
            Matrix(const Matrix<T, ROW_SIZE, COLUMN_SIZE>& other)
            {
            
            }
        
        
        public:
            inline bool operator==(const Matrix<T, ROW_SIZE, COLUMN_SIZE> &other) const {
                for (int i = 0; i < ARRAY_SIZE; i++) {
                    if (data[i] != other[i]) {
                        return false;
                    }
                }
                return true;
                
            }
            
            inline bool operator!=(const Matrix &other) const { return !*this == other; }
            
            inline T& operator[](std::size_t accessIndex) {
                return data[accessIndex];
            }
            inline T operator[](std::size_t accessIndex) const {
                return data[accessIndex];
            }
            inline T& operator[](std::size_t rowIndex, std::size_t columnIndex) {
                return data[AccessIndex(rowIndex, columnIndex)];
            }
            inline T operator[](std::size_t rowIndex, std::size_t columnIndex) const {
                return data[AccessIndex(rowIndex, columnIndex)];
            }
            
            
            friend std::ostream &operator<<(std::ostream &ostream, const Matrix &vec) {
                
                ostream << std::fixed << std::setprecision(1);
                int count = 0;
                for (int i=0; i < ARRAY_SIZE - COLUMN_SIZE; i++)
                {
                    ostream << vec.data[i*ROW_SIZE] << ", ";
                    count++;
                    if (count==COLUMN_SIZE)
                    {
                        count=0;
                        ostream << "\n";
                    }
                }
                
                return ostream;
            }
            void PrintFlat()
            {
                for (int i=0; i < ARRAY_SIZE; i++)
                {
                    std::cout << std::fixed << std::setprecision(1) << data[i] << ", ";
                }
            }
            
            inline const T *ValuePtr() const { return &data[0]; }
        
        public:
            std::size_t RowSize() const { return ROW_SIZE; }
            
            std::size_t ColumnSize() const { return COLUMN_SIZE; }
            
            std::size_t MaxSize() const { return ARRAY_SIZE; }
            
            bool IsSquare() const { return ROW_SIZE == COLUMN_SIZE; }
            
            Matrix<T, ROW_SIZE, COLUMN_SIZE> Identity() const { return Matrix<T, ROW_SIZE, COLUMN_SIZE>(1); }
            
            
        };
}




