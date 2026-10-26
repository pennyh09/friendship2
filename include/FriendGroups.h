#ifndef FRIENDGROUPS_H
#define FRIENDGROUPS_H

#include <string>
#include <tuple>
#include <vector>
#include <memory>

class CFriendGroups{
    protected:
        struct SImplementation;
        std::unique_ptr< SImplementation > DImplementation;
        
    public:
        CFriendGroups();
        ~CFriendGroups();
        
        using TName = std::string;
        using TConnection = std::tuple<TName, TName>;
        
        bool SameFriendGroup(const TConnection &) noexcept;
        void AddFriendship(const TConnection &) noexcept;
        std::vector<TConnection> FriendshipsForSingleGroup() noexcept;
        
};

#endif
