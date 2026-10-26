#ifndef VECTORMAP_H
#define VECTORMAP_H

#include "Map.h"
#include <vector>
#include <cstddef>

template <typename K, typename V>
class CMap {
public:
    using TEntityFunction = std::function<void(const K&, const V&)>;

    virtual ~CMap() = default;

    virtual std::size_t Size() const = 0;
    virtual bool Add(const K& key, V val) = 0;
    virtual bool Remove(const K& key) = 0;
    virtual bool Find(const K& key, V& val) const = 0;
    virtual void ForEach(TEntityFunction fun) = 0;
};


template <typename K, typename V>
class CVectorMap : public CMap<K, V> {
private:
    std::vector<K> keys;
    std::vector<V> values;

public:
    std::size_t Size() const override {
        return keys.size();
    }

    bool Add(const K& key, V val) override {
        for(std::size_t i = 0 ; i < keys.size(); i++){
        if(keys[i]==key){
            return false; 
        }
    }
    keys.push_back(key);
    values.push_back(val);
    return true;

    }

    bool Remove(const K& key) override {
        for(std::size_t i = 0 ; i < keys.size(); i++){
            if(keys[i]==key){
                keys.erase(keys.begin() + i);
                values.erase(values.begin() + i);
                return true;
            }
        }
        return false;
    }
        
    

    bool Find(const K& key, V& val) const override {
         for(std::size_t i = 0 ; i < keys.size(); i++){
            if(keys[i]==key){
                val = values[i];
                return true;
            }
        }
        return false;
    }

    void ForEach(typename CMap<K, V>::TEntityFunction fun) override {
        
         for(std::size_t i = 0 ; i < keys.size(); i++){
            fun(keys[i],values[i]);
         }
    }
    //asked gpt if there were any ways to print and save the line so fcode bign written
    //couldn't remeber for each did had to ask gpt 
};

#endif