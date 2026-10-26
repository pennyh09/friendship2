#ifndef WEIGHTEDQUICKUNION_H
#define WEIGHTEDQUICKUNION_H

#include "UnionFind.h"
#include <vector>
#include <cstddef>

class CWeightedQuickUnion : public CUnionFind {
private:
    std::vector<std::size_t> parent;
    std::vector<std::size_t> treeSize;
    std::size_t groupCount = 0;

public:
    std::size_t Size() const override;
    std::size_t GroupCount() const override;
    TElementID AddElement() override;
    bool Union(TElementID a, TElementID b) override;
    TGroupID Find(TElementID a) const override;
    bool Connected(TElementID a, TElementID b) override;
};

#endif
