
#include <gtest/gtest.h>
#include "FriendGroups.h"
#include <iostream>


class FriendGroupsTest : public ::testing::Test {
    protected:
        std::unique_ptr<CFriendGroups> DFriendGroups = std::make_unique<CFriendGroups>();
};


TEST_F(FriendGroupsTest, SimpleFriendship){
    this->DFriendGroups->AddFriendship({"A","B"});
    EXPECT_TRUE(this->DFriendGroups->SameFriendGroup({"A","B"}));
}

TEST_F(FriendGroupsTest, SingleGroupTest){
    CFriendGroups Groups;
    
    EXPECT_FALSE(Groups.SameFriendGroup(CFriendGroups::TConnection{"A", "B"}));
    Groups.AddFriendship(CFriendGroups::TConnection{"A", "B"});
    EXPECT_TRUE(Groups.SameFriendGroup(CFriendGroups::TConnection{"A", "B"}));
    Groups.AddFriendship(CFriendGroups::TConnection{"C", "D"});
    EXPECT_FALSE(Groups.SameFriendGroup(CFriendGroups::TConnection{"A", "C"}));
    auto FriendshipsNeeded = Groups.FriendshipsForSingleGroup();
    
    EXPECT_EQ(FriendshipsNeeded.size(), 1);
    if(FriendshipsNeeded.size()){
        auto MinFriend = std::min(std::get<0>(FriendshipsNeeded[0]), std::get<1>(FriendshipsNeeded[0]));
        auto MaxFriend = std::max(std::get<0>(FriendshipsNeeded[0]), std::get<1>(FriendshipsNeeded[0]));
        EXPECT_TRUE(MinFriend == "A" || MinFriend == "B");
        EXPECT_TRUE(MaxFriend == "C" || MaxFriend == "D");
    }
}
