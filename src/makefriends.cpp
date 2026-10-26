#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <exception>
#include "CLI11.hpp"
#include "FriendGroups.h"
#include <unordered_map>
#include <deque>
#include <unordered_set>
#include <iomanip>
#include <locale>

struct CommaSeparator : std::numpunct<char> {
    char do_thousands_sep() const override { return ','; }
    std::string do_grouping() const override { return "\3"; }
};

std::vector<CFriendGroups::TConnection> LoadFriendsFile(std::string_view filename);
bool ValidateSolution(const std::vector<CFriendGroups::TConnection> &connections, const std::vector<CFriendGroups::TConnection> &solution);

int main(int argc, char *argv[]){
    CLI::App CLIApp{"Make All Friends"};
    std::string InFilename;
    bool Validate = false;
    argv = CLIApp.ensure_utf8(argv);
    CLIApp.add_option("-f,--file", InFilename, "Friend filename.")->required();
    CLIApp.add_flag("-v,--validate", Validate, "Friend filename.");
    CLI11_PARSE(CLIApp, argc, argv);
    auto FriendConnections = LoadFriendsFile(InFilename);

    auto Start = std::chrono::steady_clock::now();
    CFriendGroups Groups;
    for(auto &Connection : FriendConnections){
        Groups.AddFriendship(Connection);
    }
    auto ProposedSolution = Groups.FriendshipsForSingleGroup();
    auto Duration =  std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now()-Start);

    for(auto Connection : ProposedSolution){
        Groups.AddFriendship(Connection);   
    }
    auto ResultConnections = Groups.FriendshipsForSingleGroup();
    if(!ResultConnections.empty()){
        std::cerr<<"Invalid Solution: Proposed solution still left "<<ResultConnections.size() + 1<<" groups."<<std::endl;
        return EXIT_FAILURE;        
    }
    if(Validate){
        if(!ValidateSolution(FriendConnections,ProposedSolution)){
            return EXIT_FAILURE;
        }
    }

    for(auto Connection : ProposedSolution){
        auto First = std::min(std::get<0>(Connection),std::get<1>(Connection));
        auto Second = std::max(std::get<0>(Connection),std::get<1>(Connection));
        std::cout<<First<<" <-> "<<Second<<std::endl;
    }
    std::unordered_set<std::string> People;
    for(auto Connection : FriendConnections){
        People.insert(std::get<0>(Connection));
        People.insert(std::get<1>(Connection));
    }
    std::cerr<<"Processed ";
    std::cerr.imbue(std::locale(std::cout.getloc(), new CommaSeparator));
    std::cerr<<People.size()<<" people with ";
    std::cerr.imbue(std::locale(std::cout.getloc(), new CommaSeparator));
    std::cerr<<FriendConnections.size()<<" connections in ";
    std::cerr.imbue(std::locale(std::cout.getloc(), new CommaSeparator));
    std::cerr<<Duration.count()<<"ns."<<std::endl;
    return EXIT_SUCCESS;
}


std::vector<CFriendGroups::TConnection> LoadFriendsFile(std::string_view filename){
    std::vector<CFriendGroups::TConnection> Connections;
    std::ifstream InFile{std::string(filename)};
    while(!InFile.eof()){
        std::string NewLine;
        std::getline(InFile, NewLine);
        auto CommaLocation = NewLine.find(",");

        if(std::string::npos != CommaLocation){
            Connections.push_back(CFriendGroups::TConnection{NewLine.substr(0,CommaLocation), NewLine.substr(CommaLocation+1)});
        }
    }
    return Connections;
}

bool ValidateSolution(const std::vector<CFriendGroups::TConnection> &connections, const std::vector<CFriendGroups::TConnection> &solution){
    std::unordered_map<std::string, std::vector<std::string>> UnprocessedConnections;
    std::string NameToStartWith;
    for(auto &Connection : connections){
        auto First = std::min(std::get<0>(Connection),std::get<1>(Connection));
        auto Second = std::max(std::get<0>(Connection),std::get<1>(Connection));
        auto Search = UnprocessedConnections.find(First);
        if(Search == UnprocessedConnections.end()){
            UnprocessedConnections[First] = {Second};
        }
        else{
            Search->second.push_back(Second);
        }
        if(NameToStartWith.empty() || First < NameToStartWith){
            NameToStartWith = First;
        }
    }
    std::unordered_map<std::string, std::size_t> PeopleToGroup;
    std::size_t GroupNumber = 0;
    while(!UnprocessedConnections.empty()){
        std::deque<std::string> PeopleToProcess;
        auto NextStartingPerson = UnprocessedConnections.begin();
        PeopleToProcess.push_back(NextStartingPerson->first);
        while(!PeopleToProcess.empty()){
            auto CurrentPerson = PeopleToProcess.front();
            PeopleToProcess.pop_front();
            PeopleToGroup[CurrentPerson] = GroupNumber;
            auto Search = UnprocessedConnections.find(CurrentPerson);
            if(Search != UnprocessedConnections.end()){
                for(auto OtherPerson : UnprocessedConnections[CurrentPerson]){
                    PeopleToGroup[OtherPerson] = GroupNumber;
                    PeopleToProcess.push_back(OtherPerson); 
                }
                UnprocessedConnections.erase(CurrentPerson);
            }
        }

        GroupNumber++;
    }

    if(GroupNumber < solution.size()){
        std::cerr<<"Invalid Solution: Proposed solution is suboptimal, could be completed with only ";
        if(2 <= GroupNumber){
            std::cerr<<GroupNumber<<" friendships."<<std::endl;
        }
        else if(1 == GroupNumber){
            std::cerr<<GroupNumber<<" friendship."<<std::endl;
        }
        else{
            std::cerr<<" no friendships."<<std::endl;   
        }
        return false;
    }
  
    std::unordered_map<std::string, int> NameUsage;
    for(auto Connection : solution){
        for(auto Name : {std::get<0>(Connection), std::get<1>(Connection)}){
            auto NameData = NameUsage.find(Name);
            if(NameData != NameUsage.end()){
                NameData->second++;
                if(2 < NameData->second){
                    std::cerr<<"Invalid Solution: Name "<<NameData->first<<" listed more than twice."<<std::endl;
                    return false;
                }
            }
            else{
                NameUsage[Name] = 1;   
            }
        }
    }
    return true;
}