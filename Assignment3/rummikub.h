#ifndef RUMMIKUB_H
#define RUMMIKUB_H
#include <fstream>
#include <vector>
#include <iostream>
#include <functional>

enum Color { Red, Green, Blue, Yellow };


struct Tile {
    int     denomination;
    Color   color;
};

std::ostream& operator<<(std::ostream& os, Tile const& t);

class RummiKub {
    private:
        using Group = std::vector<Tile>;
        using Run = std::vector<Tile>;
    public:
        RummiKub(); // empty hand
        void Add( Tile const& ); // add a tile to hand

        void Solve(); // solve

        // get solution - groups
        std::vector<Group> GetGroups() const;
        // get solution - runs
        std::vector<Run> GetRuns() const;
        // if both vectors are empty - no solution possible
    private:

    bool solve_recursive(std::vector<Tile> hand);

        std::vector<Group> Groups;
        std::vector<Run> Runs;
        std::vector<Tile> hand;

        static bool isGroupLegal(std::vector<Tile> const &tiles);
        static bool isRunLegal(std::vector<Tile> const &tiles);
        static bool isGroupAddable(std::vector<Tile> const &tiles);
        static bool isRunAddable(std::vector<Tile>const & tiles);


        void Trim(std::vector<std::vector<Tile>>& set, bool (*pred)(std::vector<Tile> const&));
        void TrimGroupsAndRuns();

        bool areGroupsLegal(std::vector<Group> const & groups);
        bool areRunsLegal(std::vector<Run> const & runs);


        void AddNewRun(Tile tile);
        void AddNewGroup(Tile tile);

        using Action = std::function<void(Tile)>;

        struct ActionStruct
        {
            Action action;
            Action undo;
        };


        std::vector<ActionStruct> GetOptions(Tile tile);
};
#include "rummikub.cpp"

#endif
