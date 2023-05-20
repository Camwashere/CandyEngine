#pragma once

#include <Candy/CandyEngineBase.hpp>
#include <queue>
#include <limits>
#include <string>
namespace Candy{
    
    
    template<typename T>
    requires Incrementable<T>
    class IDManager
    {
    private:
        T currentID;
        std::queue<T> availableIDs;
        std::size_t poolSize;
    
    public:
        IDManager(T startIDValue, std::size_t poolSizeValue) : currentID(startIDValue), poolSize(poolSizeValue){}
    
    public:
        T AssignID()
        {
            if (!availableIDs.empty())
            {
                T id = availableIDs.front();
                availableIDs.pop();
                return id;
                
            }
            else
            {
                T id = currentID;
                ++currentID;
                return id;
            }
        }
        
        void FreeID(T id)
        {
            availableIDs.push(id);
        }
        
        void Reset(T startIDValue)
        {
            currentID = startIDValue;
            availableIDs = std::queue<T>();
        }
    
    public:
        void SetPoolSize(std::size_t value){poolSize=value;}
        T PeekCurrentID()const{return currentID;}
        const std::queue<T>& GetAvailableIDs()const{return availableIDs;}
    };
    
    class IDManagerInt : public IDManager<int>
    {
    public:
        IDManagerInt(int poolSize=300) : IDManager<int>(std::numeric_limits<int>::min(), poolSize){}
    };
}

