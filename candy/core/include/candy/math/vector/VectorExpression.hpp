#pragma once
#include <condition_variable>
namespace Candy::Math{
    
    
    template <typename COMPONENT_TYPE, typename VEC>
    class VectorExpression
    {
    public:
        static constexpr bool isLeaf=false;
        COMPONENT_TYPE operator[](std::size_t index)const{return static_cast<const VEC&>(*this)[index];}
        [[nodiscard]] std::size_t Size() const{return static_cast<const VEC&>(*this).Size();}
        
        
    };
    
    template<typename COMPONENT_TYPE, typename VEC1_SIZE, typename VEC2_SIZE>
    class VectorSum : public VectorExpression<COMPONENT_TYPE, VectorSum<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE>>
    {
        std::conditional_t<VEC1_SIZE::isLeaf, const VEC1_SIZE&, const VEC1_SIZE> _u;
        std::conditional_t<VEC2_SIZE::isLeaf, const VEC2_SIZE&, const VEC2_SIZE> _v;
    
    public:
        static constexpr bool isLeaf=false;
        VectorSum(const VEC1_SIZE& u, const VEC2_SIZE& v) : _u(u), _v(v){
            //assert(u.Size() == v.Size());
        }
        COMPONENT_TYPE operator[](std::size_t index) const {return _u[index] + _v[index];}
        std::size_t Size()const{return _v.Size();}
    };
    
    template<typename COMPONENT_TYPE, typename VEC1_SIZE, typename VEC2_SIZE>
    class VectorDif : public VectorExpression<COMPONENT_TYPE, VectorDif<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE>>{
        std::conditional_t<VEC1_SIZE::isLeaf, const VEC1_SIZE&, const VEC1_SIZE> _u;
        std::conditional_t<VEC2_SIZE::isLeaf, const VEC2_SIZE&, const VEC2_SIZE> _v;
    public:
        static constexpr bool isLeaf=false;
        VectorDif(const VEC1_SIZE& u, const VEC2_SIZE& v) : _u(u), _v(v){
            //assert(u.Size() == v.Size());
        }
        
        COMPONENT_TYPE operator[](std::size_t index) const {return _u[index] - _v[index];}
        std::size_t Size()const{return _v.Size();}
    };
    
    template<typename COMPONENT_TYPE, typename VEC1_SIZE, typename VEC2_SIZE>
    class VectorMultiply : public VectorExpression<COMPONENT_TYPE, VectorMultiply<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE>>
    {
        std::conditional_t<VEC1_SIZE::isLeaf, const VEC1_SIZE&, const VEC1_SIZE> _u;
        std::conditional_t<VEC2_SIZE::isLeaf, const VEC2_SIZE&, const VEC2_SIZE> _v;
    
    public:
        static constexpr bool isLeaf=false;
        VectorMultiply(const VEC1_SIZE& u, const VEC2_SIZE& v) : _u(u), _v(v){
            //assert(u.Size() == v.Size());
        }
        COMPONENT_TYPE operator[](std::size_t index) const {return _u[index] * _v[index];}
        std::size_t Size()const{return _v.Size();}
        
    };
    
    template<typename COMPONENT_TYPE, typename VEC1_SIZE, typename VEC2_SIZE>
    class VectorDivide : public VectorExpression<COMPONENT_TYPE, VectorDivide<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE>>{
        std::conditional_t<VEC1_SIZE::isLeaf, const VEC1_SIZE&, const VEC1_SIZE> _u;
        std::conditional_t<VEC2_SIZE::isLeaf, const VEC2_SIZE&, const VEC2_SIZE> _v;
    public:
        static constexpr bool isLeaf=false;
        VectorDivide(const VEC1_SIZE& u, const VEC2_SIZE& v) : _u(u), _v(v){
            //assert(u.Size() == v.Size());
        }
        COMPONENT_TYPE operator[](std::size_t index) const {return _u[index] / _v[index];}
        std::size_t Size()const{return _v.Size();}
    };
    
    template<typename COMPONENT_TYPE, typename VEC>
    class ScalarDivide : public VectorExpression<COMPONENT_TYPE, ScalarDivide<COMPONENT_TYPE, VEC>>{
        std::conditional_t<VEC::isLeaf, const VEC&, const VEC> _u;
        const COMPONENT_TYPE _v;
    public:
        static constexpr bool isLeaf=false;
        ScalarDivide(const VEC& u, const COMPONENT_TYPE& v) : _u(u), _v(v){}
        ScalarDivide(const COMPONENT_TYPE& v, const VEC& u) : _u(u), _v(v){}
        COMPONENT_TYPE operator[](std::size_t index) const {return _u[index] / _v;}
        std::size_t Size()const{return _u.Size();}
    };
    
    template<typename COMPONENT_TYPE, typename VEC>
    class ScalarVectorMultiply : public VectorExpression<COMPONENT_TYPE, ScalarVectorMultiply<COMPONENT_TYPE, VEC>>{
        std::conditional_t<VEC::isLeaf, const VEC&, const VEC> _u;
        const COMPONENT_TYPE _v;
    public:
        static constexpr bool isLeaf=false;
        ScalarVectorMultiply(const VEC& u, const COMPONENT_TYPE& v) : _u(u), _v(v){}
        ScalarVectorMultiply(const COMPONENT_TYPE& v, const VEC& u) : _u(u), _v(v){}
        COMPONENT_TYPE operator[](std::size_t index) const {return _u[index] * _v;}
        std::size_t Size()const{return _u.Size();}
    };
    
}

// Global Operator Implementations
template <typename COMPONENT_TYPE, typename VEC1_SIZE, typename VEC2_SIZE>
Candy::Math::VectorSum<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE> operator+(Candy::Math::VectorExpression<COMPONENT_TYPE, VEC1_SIZE> const& u, Candy::Math::VectorExpression<COMPONENT_TYPE, VEC2_SIZE> const& v) {
    return Candy::Math::VectorSum<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE>(*static_cast<const VEC1_SIZE *>(&u), *static_cast<const VEC2_SIZE *>(&v));
}

template <typename COMPONENT_TYPE, typename VEC1_SIZE, typename VEC2_SIZE>
Candy::Math::VectorDif<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE> operator-(Candy::Math::VectorExpression<COMPONENT_TYPE, VEC1_SIZE> const& u, Candy::Math::VectorExpression<COMPONENT_TYPE, VEC2_SIZE> const& v) {
    return Candy::Math::VectorDif<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE>(*static_cast<const VEC1_SIZE *>(&u), *static_cast<const VEC2_SIZE *>(&v));
}

template <typename COMPONENT_TYPE, typename VEC1_SIZE, typename VEC2_SIZE>
Candy::Math::VectorMultiply<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE> operator*(Candy::Math::VectorExpression<COMPONENT_TYPE, VEC1_SIZE> const& u, Candy::Math::VectorExpression<COMPONENT_TYPE, VEC2_SIZE> const& v) {
    return Candy::Math::VectorMultiply<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE>(*static_cast<const VEC1_SIZE *>(&u), *static_cast<const VEC2_SIZE *>(&v));
}

template <typename COMPONENT_TYPE, typename VEC1_SIZE, typename VEC2_SIZE>
Candy::Math::VectorDivide<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE> operator/(Candy::Math::VectorExpression<COMPONENT_TYPE, VEC1_SIZE> const& u, Candy::Math::VectorExpression<COMPONENT_TYPE, VEC2_SIZE> const& v) {
    return Candy::Math::VectorDivide<COMPONENT_TYPE, VEC1_SIZE, VEC2_SIZE>(*static_cast<const VEC1_SIZE *>(&u), *static_cast<const VEC2_SIZE *>(&v));
}

template <typename COMPONENT_TYPE, typename VEC_SIZE, typename SCALAR_TYPE>
requires (std::convertible_to<SCALAR_TYPE, COMPONENT_TYPE>)
Candy::Math::ScalarDivide<COMPONENT_TYPE, VEC_SIZE> operator/(Candy::Math::VectorExpression<COMPONENT_TYPE, VEC_SIZE> const& vec, const SCALAR_TYPE& scalar) {
    return Candy::Math::ScalarDivide<COMPONENT_TYPE, VEC_SIZE>(*static_cast<const VEC_SIZE *>(&vec), scalar);
}

template <typename COMPONENT_TYPE, typename VEC_SIZE, typename SCALAR_TYPE>
requires (std::convertible_to<SCALAR_TYPE, COMPONENT_TYPE>)
Candy::Math::ScalarDivide<COMPONENT_TYPE, VEC_SIZE> operator/(const SCALAR_TYPE& scalar, const Candy::Math::VectorExpression<COMPONENT_TYPE, VEC_SIZE>& vec) {
    return Candy::Math::ScalarDivide<COMPONENT_TYPE, VEC_SIZE>(scalar, *static_cast<const VEC_SIZE *>(&vec));
}

template <typename COMPONENT_TYPE, typename VEC_SIZE, typename SCALAR_TYPE>
requires (std::convertible_to<SCALAR_TYPE, COMPONENT_TYPE>)
Candy::Math::ScalarVectorMultiply<COMPONENT_TYPE, VEC_SIZE> operator*(const Candy::Math::VectorExpression<COMPONENT_TYPE, VEC_SIZE>& vec, const SCALAR_TYPE& scalar) {
    return Candy::Math::ScalarVectorMultiply<COMPONENT_TYPE, VEC_SIZE>(*static_cast<const VEC_SIZE *>(&vec), scalar);
}
template <typename COMPONENT_TYPE, typename VEC_SIZE, typename SCALAR_TYPE>
requires (std::convertible_to<SCALAR_TYPE, COMPONENT_TYPE>)
Candy::Math::ScalarVectorMultiply<COMPONENT_TYPE, VEC_SIZE> operator*(const SCALAR_TYPE& scalar, const Candy::Math::VectorExpression<COMPONENT_TYPE, VEC_SIZE>& vec) {
    return Candy::Math::ScalarVectorMultiply<COMPONENT_TYPE, VEC_SIZE>(scalar, *static_cast<const VEC_SIZE *>(&vec));
}