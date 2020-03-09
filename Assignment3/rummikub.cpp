//
// Created by roland on 2/13/20.
//

#include "rummikub.h"
#include <algorithm>
#include <unordered_map>

std::ostream& operator<<(std::ostream& os, Tile const& t) {
    os << "{ "<< t.denomination << ",";
    switch ( t.color ) {
        case Red:      os << "R"; break;
        case Green:    os << "G"; break;
        case Blue:     os << "B"; break;
        case Yellow:   os << "Y"; break;
    }
    os << " }";
    return os;
}

static bool operator==(const Tile& lhs, const Tile& rhs)
{
    return lhs.denomination == rhs.denomination && lhs.color == rhs.color;
}

static bool compareDenomination(Tile a, Tile b)
{
    return a.denomination < b.denomination;
}

RummiKub::RummiKub()
{

}

void RummiKub::Add(Tile const &t)
{
    hand.push_back(t);
}

void RummiKub::Solve()
{
    if(!solve_recursive(hand))
    {
        Groups.clear();
        Runs.clear();
    }
}

std::vector<std::vector<Tile> > RummiKub::GetGroups() const
{
    return Groups;
}

std::vector<std::vector<Tile> > RummiKub::GetRuns() const
{
    return Runs;
}

// Expect input to be sorted
bool RummiKub::isGroupLegal(std::vector<Tile> const &tiles)
{
    // A group can only be 3 or 4 tiles.
    if(tiles.size() < 3 || tiles.size() > 4)
        return false;

    int denomination = tiles[0].denomination;
    Color color = tiles[0].color;
    // same denomination, no tiles of the same color
    for (unsigned i = 1; i < tiles.size(); ++i)
    {
        // If different demonimation, return false
        if(denomination != tiles[i].denomination)
            return false;
        // If tiles are same color, return false
        if(color == tiles[i].color)
            return false;
    }
    return true;
}

bool RummiKub::isRunLegal(std::vector<Tile> const &tiles)
{
    // A run is 3 or more tiles
    if(tiles.size() < 3)
        return false;
    // All tiles same color, consecutive denominations
    Color color = tiles[0].color;
    int denomination = tiles[0].denomination;
    for(unsigned i = 1; i < tiles.size(); ++i)
    {
        // If tiles are different color, return false
        if(tiles[i].color != color)
            return false;
        // If tiles aren't consecutive
        if(denomination + 1 != tiles[i].denomination)
            return false;
        denomination = tiles[i].denomination;
    }
    return true;
}

void RummiKub::AddNewRun(Tile tile)
{
    Runs.push_back({tile});
}

void RummiKub::AddNewGroup(Tile tile)
{
    Groups.push_back({tile});
}

bool RummiKub::solve_recursive(std::vector<Tile> localhand)
{
    if(localhand.size() == 0)
    {
        return areRunsLegal(Runs) && areGroupsLegal(Groups);
    }

    Tile currentTile = localhand.back();
    localhand.pop_back();

    std::vector<ActionStruct> actions = GetOptions(currentTile);

    for(ActionStruct actionStruct : actions)
    {
        actionStruct.action(currentTile);
        solve_recursive(localhand);
        if (areRunsLegal(Runs) && areGroupsLegal(Groups))
            return true;
        // undo the action
        actionStruct.undo(currentTile);
    }
    return false;
}

bool RummiKub::areRunsLegal(const std::vector<Run> &runs)
{
    if(Runs.size() == 0)
        return true;
    // std::remove_if(runs.cbegin(), runs.cend(), [](Run run){ return !isRunLegal(run);});
    for(const Run& run: runs)
    {
        if (!isRunLegal(run))
            return false;
    }
    return true;
}

bool RummiKub::areGroupsLegal(const std::vector<RummiKub::Group> &groups)
{
    if(Groups.size() == 0)
        return true;
    for(const Group& group: groups)
    {
        if(!isGroupLegal(group))
            return false;
    }
    return true;
}

std::vector<RummiKub::ActionStruct> RummiKub::GetOptions(Tile tile)
{
    //1) add it to an existing run with the same color as tile and tile's denomination is not yet in the run
    //2) add it to an existing group with the same denomiation as tile and tile's color is not yet in the group
    //3) create a new run
    //4) create a new group
    std::vector<RummiKub::ActionStruct> result;

    for(unsigned i = 0; i < Groups.size(); ++i)
    {
        Group& group = Groups[i];
        Group groupCopy = group;
        groupCopy.push_back(tile);
        if(isGroupAddable(groupCopy))
        {
            result.emplace_back(ActionStruct{});
            result.back().action = ([this, i](Tile tile) {
                Group& group = Groups[i];
                group.push_back(tile);
            });
            result.back().undo = ([this, i](Tile tile)
            {
                Group& group = Groups[i];
                auto iter = std::find(group.begin(), group.end(), tile);
                if(iter == group.end())
                    throw 1;
                group.erase(iter);
            });
        }
    }

    for(unsigned i = 0; i < Runs.size(); ++i)
    {
        Run& run = Runs[i];
        Run runCopy = run;
        runCopy.push_back(tile);
        std::sort(runCopy.begin(), runCopy.end(), compareDenomination);
        if(isRunAddable(runCopy))
        {
            result.emplace_back(ActionStruct{});
            result.back().action = ([this, i](Tile tile) {
                Run& run = Runs[i];
                run.push_back(tile);
                std::sort(run.begin(), run.end(), compareDenomination);
            });
            result.back().undo = ([this, i](Tile tile)
            {
                Run& run = Runs[i];
                auto iter = std::find(run.begin(), run.end(), tile);
                if(iter == run.end())
                    throw 1;
                run.erase(iter);
            });
        }
    }

    result.emplace_back(ActionStruct{});
    result.back().action = [this](Tile tile)
    {
        Runs.push_back({tile});
    };
    result.back().undo = [this](Tile tile)
    {
        (void)tile;
        Runs.pop_back();
    };

    result.emplace_back(ActionStruct{});
    result.back().action = [this](Tile tile)
    {
        Groups.push_back({tile});
    };
    result.back().undo = [this](Tile tile)
    {
        (void)tile;
        Groups.pop_back();
    };
    return result;
}

bool RummiKub::isGroupAddable(std::vector<Tile> const &tiles)
{
    // add it to an existing group with the same denomiation as tile
    // and tile's color is not yet in the group
    int groupDenomination = tiles[0].denomination;
    std::unordered_map<Color, int> colors;

    for(unsigned i = 0; i < tiles.size(); ++i)
    {
        // If tiles are different denominations, return false
        if(tiles[i].denomination != groupDenomination)
            return false;
        if(++(colors[tiles[i].color]) != 1)
            return false;
    }
    return true;
}

bool RummiKub::isRunAddable(std::vector<Tile> const &tiles)
{
    //  add it to an existing group with the same denomiation as
    //  tile and tile's color is not yet in the gro
    Color color = tiles[0].color;
    std::unordered_map<int, int> denominations;
    for(unsigned i = 0; i < tiles.size(); ++i)
    {
        // If tiles are different color, return false
        if(tiles[i].color != color)
            return false;
        if(++(denominations[tiles[i].denomination]) != 1)
            return false;
    }
    return true;
}

void RummiKub::TrimGroupsAndRuns()
{
    Trim(this->Groups, isGroupLegal);
    Trim(this->Runs, isRunLegal);
}

void RummiKub::Trim(std::vector<std::vector<Tile>>& set, bool (*pred)(std::vector<Tile> const &))
{
    using MyVector = std::vector<std::vector<Tile>>;

    for (MyVector::iterator b = set.begin(); b != set.end();)
    {
        if (!pred(*b))
        {
            b = set.erase(b); // reseat iterator to a valid value post-erase
        }
        else
        {
            ++b;
        }
    }
}



