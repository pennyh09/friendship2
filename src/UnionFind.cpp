#include "WeightedQuickUnion.h"

std::size_t CWeightedQuickUnion::Size() const {
    return parent.size();
}

std::size_t CWeightedQuickUnion::GroupCount() const{
    return groupCount;
}

CUnionFind::TElementID CWeightedQuickUnion::AddElement() {
TElementID newID = parent.size();

    parent.push_back(newID);
    treeSize.push_back(1);
    groupCount++;

    return newID;
}

CUnionFind::TGroupID CWeightedQuickUnion::Find(TElementID a) const {
      if (a >= parent.size()) {
        return InvalidGroupID;
    }

    TElementID temp = a;
    while (temp != parent[temp]){
        temp = parent[temp];

    }
    return temp;
}

bool CWeightedQuickUnion::Connected(TElementID a, TElementID b) {
    TElementID a1;
    TElementID b1;
    a1 = Find(a);
    b1 = Find(b);

    if (a1 == InvalidGroupID || b1 == InvalidGroupID) {
        return false;
    }
    if(a1 == b1){
        return true;
    }else{
    return false;
    }
}

bool CWeightedQuickUnion::Union(TElementID a, TElementID b){
     if (a >= parent.size() || b >= parent.size()) {
        return false;
    }
    TElementID rootA = Find(a);
    TElementID rootB = Find(b);
    TElementID TSa = treeSize[rootA];
    TElementID TSb = treeSize[rootB];

    if(rootA == rootB){
        return false;
    }

    if(TSa < TSb){
        parent[rootA] = rootB;
        treeSize[rootB]= TSb + TSa;
        groupCount--;
        return true;
    }else{
         parent[rootB] = rootA;
        treeSize[rootA]= TSb + TSa;
        groupCount--;
        return true;

    }
}

