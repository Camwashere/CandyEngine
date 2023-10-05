#pragma once
#include <unordered_map>
#include <cstdint>
namespace Candy::Collections
{
  template<typename KEY, typename VALUE>
  class DualMap
  {
  private:
    std::unordered_map<KEY, VALUE> keyToVal{};
    std::unordered_map<VALUE, KEY> valToKey{};
    
  public:
    VALUE& operator[](const KEY& key)
    {
      return keyToVal[key];
    }
    
  public:
    bool ContainsKey(const KEY& key)const
    {
      return keyToVal.find(key) != keyToVal.end();
    }
    bool ContainsValue(const VALUE& value)const
    {
      return valToKey.find(value) != valToKey.end();
    }
    
    // Add a pair
    void Insert(const KEY &key, const VALUE &value) {
      keyToVal.insert({key, value});
      valToKey.insert({value, key});
    }
    
    auto FindValue(const KEY &key) {
      return keyToVal.find(key);
    }
    
    auto FindKey(const VALUE &value) {
      return valToKey.find(value);
    }
    
    auto FindValue(const KEY& key)const
    {
      return keyToVal.find(key);
    }
    
    auto FindKey(const VALUE& value)const
    {
      return valToKey.find(value);
    }
    
    // Get by key
    VALUE AtKey(const KEY &key) {
      return keyToVal.at(key);
    }
    
    // Get by value
    KEY AtValue(const VALUE &value) {
      return valToKey.at(value);
    }
    
    // Erase by key
    void EraseByKey(const KEY &key) {
      VALUE value = keyToVal.at(key);
      keyToVal.erase(key);
      valToKey.erase(value);
    }
    
    // Erase by value
    void EraseByValue(const VALUE &value) {
      KEY key = valToKey.at(value);
      valToKey.erase(value);
      keyToVal.erase(key);
    }
    
    // Forwarding functions for begin and end iterators for the key -> value map.
    auto begin()
    {
      return keyToVal.begin();
    }
    
    auto end()
    {
      return keyToVal.end();
    }
    
    auto begin()const
    {
      return keyToVal.begin();
    }
    
    auto end()const
    {
      return keyToVal.end();
    }
    
    // Forwarding functions for const begin and end iterators for key -> value map.
    auto cbegin()
    {
      return keyToVal.cbegin();
    }
    
    auto cend()
    {
      return keyToVal.cend();
    }
    auto cbegin() const
    {
      return keyToVal.cbegin();
    }
    
    auto cend() const
    {
      return keyToVal.cend();
    }
    
    
    // begin and end for the value -> key map
    auto beginValueToKey() {
      return valToKey.begin();
    }
    
    auto endValueToKey() {
      return valToKey.end();
    }
    
    // const begin and end for the value -> key map
    auto cbeginValueToKey() const {
      return valToKey.cbegin();
    }
    
    auto cendValueToKey() const {
      return valToKey.cend();
    }
    size_t CountKey(const KEY& key) const {
      return keyToVal.count(key);
    }
    
    size_t CountValue(const VALUE& value)const
    {
      return valToKey.count(value);
    }
    // Size of DualMap (both maps should have same size)
    [[nodiscard]] size_t Size() const {
      return keyToVal.size(); // or return reverseMap.size()
    }
    
    // Check if map is empty
    [[nodiscard]] bool Empty() const {
      return keyToVal.empty(); // or return reverseMap.empty()
    }
    
    // Clear all elements
    void Clear() {
      keyToVal.clear();
      valToKey.clear();
    }
    
  };
}