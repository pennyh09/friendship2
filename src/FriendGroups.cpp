#include "FriendGroups.h"
#include "VectorMap.h"
#include "WeightedQuickUnion.h"
#include <iostream>

struct CFriendGroups::SImplementation{
    CVectorMap<TName, std::size_t> map;
    CWeightedQuickUnion unionFind;

};

CFriendGroups::CFriendGroups(){
    DImplementation = std::make_unique<SImplementation>();
}

CFriendGroups::~CFriendGroups(){
    
}

bool CFriendGroups::SameFriendGroup(const TConnection &connection) noexcept{
    TName name1 = std::get<0>(connection);
    TName name2 = std::get<1>(connection);// couldnt rememeber the get for tuples had to ask gpt 

    std::size_t id1;
    std::size_t id2;
    //id is updated to the element id 

    if(DImplementation->map.Find(name1,id1) == false || DImplementation->map.Find(name2,id2) == false){
        return false;
    }

    return DImplementation->unionFind.Connected(id1,id2);


}

void CFriendGroups::AddFriendship(const TConnection &friendship) noexcept{
    TName name1 = std::get<0>(friendship);
    TName name2 = std::get<1>(friendship);

    std::size_t id1;
    std::size_t id2;
    //id is updated to the element id 

        if(DImplementation->map.Find(name1,id1) == false){
            id1 = DImplementation->unionFind.AddElement();//add element to union
            DImplementation->map.Add(name1,id1);//then add id and element to map
        } 
         if(DImplementation->map.Find(name2,id2) == false){
        id2 = DImplementation->unionFind.AddElement();
        DImplementation->map.Add(name2,id2);
    }

     DImplementation->unionFind.Union(id1, id2);
     

    
}

std::vector<CFriendGroups::TConnection> CFriendGroups::FriendshipsForSingleGroup() noexcept{
    std::vector<TConnection> connections;
    std::vector<std::size_t> roots; 

    std::vector<TName> names;
  

    if (DImplementation->unionFind.GroupCount() <= 1 ){
        return connections; //no other friends no friendship
    }
    
    DImplementation->map.ForEach(
        [&](const TName& name, const std::size_t& id){
        std::size_t root = DImplementation->unionFind.Find(id);
    for(std::size_t i = 0 ;i < roots.size(); i++){
        if(roots[i]== root){
            return;
        }
    }
            roots.push_back(root);
            names.push_back(name);
}
);


       
    for(std::size_t i = 0 ; i + 1<names.size(); i++){
        connections.push_back({names[i], names[i+1]});
    }
  
    return connections;

}