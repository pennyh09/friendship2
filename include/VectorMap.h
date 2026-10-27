#ifndef VECTORMAP_H
#define VECTORMAP_H

#include "Map.h"
#include <vector>
#include <cstddef>

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
        std::size_t left = 0;
        std::size_t right = keys.size();

        while(left<right){
                std::size_t mid = left + (right - left) / 2;

            if (key < keys[mid]) {
                right = mid;
            }          
            else if (key > keys[mid]) {
                left = mid + 1;
            }
            else {
               return false;
            }
           
        }
    keys.insert(keys.begin() + left, key);
    values.insert(values.begin() + left, val);
    return true;

    }
    //alphabetical now 

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
        std::size_t left = 0;
        std::size_t right = keys.size();

        while(left<right){
                std::size_t mid = left + (right - left) / 2;

            if (key < keys[mid]) {
                right = mid;
            }          
            else if (key > keys[mid]) {
                left = mid + 1;
            }
            else {
                val = values[mid];
                return true;
            }
           
        }
        return false;

    }
    //swapped to binary search 

    void ForEach(typename CMap<K, V>::TEntityFunction fun) override {
        
         for(std::size_t i = 0 ; i < keys.size(); i++){
            fun(keys[i],values[i]);
         }
    }
    //asked gpt if there were any ways to print and save the line so fcode bign written
    //couldn't remeber for each did had to ask gpt 
};

#endif