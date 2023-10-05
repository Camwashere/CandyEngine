#pragma once
#include <candy/base/Base.hpp>
#include <candy/base/CandyConcepts.hpp>
namespace Candy::Utils
{
  template<Numeric INDEX>
  class ObjectIdentifiable;
  
  
  template<Numeric INDEX>
  class ObjectIDAccess {
  protected:
    void SetID(ObjectIdentifiable<INDEX>& obj, INDEX id) {
      obj.id = id;
    }
  };
  
  
  template<Numeric INDEX>
  class ObjectIdentifiable
  {
  public:
    static constexpr INDEX NULL_ID = std::numeric_limits<INDEX>::max();
  private:
    INDEX id=NULL_ID;
  
  public:
    [[nodiscard]] bool ValidID()const{return id!=NULL_ID;}
    [[nodiscard]] INDEX GetID()const{return id;}
  
  private:
    friend class ObjectIDAccess<INDEX>;
    
    
  };
}