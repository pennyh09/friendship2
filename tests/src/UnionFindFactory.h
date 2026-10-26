#include "UnionFind.h"
#include "WeightedQuickUnion.h"
#include <memory>


template <typename T>
struct SUnionFindFactory;

template<>
struct SUnionFindFactory<CWeightedQuickUnion>{
    static std::unique_ptr<CUnionFind> Create(){
        return std::make_unique<CWeightedQuickUnion>();
    }
};
