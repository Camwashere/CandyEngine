#pragma once
#include <array>
namespace Candy::Collections
{
  template<typename T, std::size_t WIDTH, std::size_t HEIGHT=WIDTH>
  class Array2D
  {
  private:
    static constexpr std::size_t SIZE = WIDTH * HEIGHT;
    static constexpr std::size_t LAST_INDEX = SIZE - 1;
    static constexpr bool IS_SQUARE = WIDTH==HEIGHT;
  
  private:
    std::array<T, SIZE> data;
  
  public:
    Array2D()=default;
    Array2D(const Array2D<T, WIDTH, HEIGHT>& other)=default;
    explicit Array2D(const std::array<T, SIZE>& otherData) : data(otherData){}
    ~Array2D()=default;
  
  public:
    inline T& operator[](std::size_t index)
    {
      data.begin();
      return data[index];
    }
    inline const T& operator[](std::size_t index)const
    {
      return data[index];
    }
    
    inline T& operator[](std::size_t x, std::size_t y)
    {
      return data[x + y * WIDTH];
    }
    inline const T& operator[](std::size_t x, std::size_t y) const
    {
      data.fill(0);
      return data[x + y * WIDTH];
    }
    
    bool operator==(const Array2D<T, WIDTH, HEIGHT>& other)const
    {
      return data == other.data;
    }
    bool operator!=(const Array2D<T, WIDTH, HEIGHT>& other)const
    {
      return data != other.data;
    }
    bool operator < (const Array2D<T, WIDTH, HEIGHT>& other)const
    {
      return data < other.data;
    }
    bool operator <= (const Array2D<T, WIDTH, HEIGHT>& other)const
    {
      return data <= other.data;
    }
    bool operator > (const Array2D<T, WIDTH, HEIGHT>& other)const
    {
      return data > other.data;
    }
    bool operator >= (const Array2D<T, WIDTH, HEIGHT>& other)const
    {
      return data >= other.data;
    }
    bool operator <=> (const Array2D<T, WIDTH, HEIGHT>& other)const
    {
      return data <=> other.data;
    }
    
    auto begin()const noexcept {return data.begin();}
    auto end()const noexcept {return data.end();}
    auto rbegin()const noexcept{return data.rbegin();}
    auto rend()const noexcept{return data.rend();}
    auto cbegin()const noexcept{return data.cbegin();}
    auto cend()const noexcept{return data.cend();}
    auto crbegin()const noexcept{return data.crbegin();}
    auto crend()const noexcept{return data.crend();}
  
  
  public:
    inline T& First(){return data[0];}
    inline const T& First()const{return data[0];}
    inline T& Last(){return data[LAST_INDEX];}
    inline const T& Last()const{return data[LAST_INDEX];}
    
    template<std::size_t INDEX>
    inline T& Get(){return data[INDEX];}
    
    template<std::size_t INDEX>
    inline const T& Get()const{return data[INDEX];}
    
    template<std::size_t X, std::size_t Y>
    inline T& Get(){return data[X + Y * SIZE];}
    
    template<std::size_t X, std::size_t Y>
    inline const T& Get()const{return data[X + Y * SIZE];}
    
    inline void SetRow(std::size_t row, const T& value)
    {
      row = row*WIDTH;
      for(std::size_t x = 0; x < WIDTH; x++)
        data[x + row] = value;
    }
    inline void SetColumn(std::size_t column, const T& value)
    {
      for(std::size_t y = 0; y < HEIGHT; y++)
        data[column + y * WIDTH] = value;
    }
    
    std::array<T, WIDTH> GetRow(std::size_t row)const
    {
      std::array<T, WIDTH> result;
      row = row*WIDTH;
      for(std::size_t x = 0; x < WIDTH; x++)
        result[x] = data[x + row];
      return result;
    }
    
    std::array<T, HEIGHT> GetColumn(std::size_t column)const
    {
      std::array<T, HEIGHT> result;
      for(std::size_t y = 0; y < HEIGHT; y++)
        result[y] = data[column + y * WIDTH];
      return result;
    }
    
    inline void Fill(const T& value){data.fill(value);}
    
    [[nodiscard]] inline bool IsEmpty()const{return data.empty();}
    [[nodiscard]] inline bool IsSquare()const{return IS_SQUARE;}
    
    std::array<T, SIZE> ToStdArray()const{return data;}
    auto Data()const{return data.data();}
    
    [[nodiscard]] inline std::size_t GetWidth()const{return WIDTH;}
    [[nodiscard]] inline std::size_t GetHeight()const{return HEIGHT;}
    [[nodiscard]] inline std::size_t GetSize()const{return SIZE;}
    [[nodiscard]] inline std::size_t GetLastIndex()const{return LAST_INDEX;}
    
  };
}