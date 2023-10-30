#include "Puzzle.h"
typedef std::vector<Puzzle::Action> Path;
typedef std::pair<Puzzle, Path> StatePath;

StatePath breadthFirstSearch(const Puzzle& puzzle, int maxIterations);

StatePath aStarSearch(const Puzzle& puzzle, int maxIterations);

struct CostComparator {
    bool operator()(const StatePath& lhs, const StatePath& rhs) const {
        return lhs.first.cost() > rhs.first.cost();
    }
};