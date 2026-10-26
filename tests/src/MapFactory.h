#include "Map.h"
#include "YOUR_IMPLEMENTATION_HEADER.H"
#include <memory>


template <typename T>
struct SMapFactory;

template<typename K, typename V>
struct SMapFactory<YOUR_IMPLEMENTATION<K,V> > {
    static std::unique_ptr<CMap<K,V>> Create(){
        return std::make_unique<YOUR_IMPLEMENTATION<K,V>>();
    }
};
