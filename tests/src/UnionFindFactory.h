#include "UnionFind.h"
#include "YOUR_IMPLEMENTATION_HEADER.h"
#include <memory>


template <typename T>
struct SUnionFindFactory;

template<>
struct SUnionFindFactory<YOUR_IMPLEMENTATION>{
    static std::unique_ptr<CUnionFind> Create(){
        return std::make_unique<YOUR_IMPLEMENTATION>();
    }
};
