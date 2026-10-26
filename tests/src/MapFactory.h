#include "Map.h"
#include "VectorMap.h"
#include <memory>


template <typename T>
struct SMapFactory;

template<typename K, typename V>
struct SMapFactory<CVectorMap<K,V> > {
    static std::unique_ptr<CMap<K,V>> Create(){
        return std::make_unique<CVectorMap<K,V>>();
    }
};
