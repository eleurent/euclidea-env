#include "Puzzle.h"
typedef std::vector<Puzzle::Action> Path;
typedef std::pair<Puzzle, Path> StatePath;

StatePath breadthFirstSearch(const Puzzle& puzzle, const int maxIterations, const int maxDepth, const int optimalDepth);

StatePath aStarSearch(const Puzzle& puzzle, const int maxIterations, const int maxDepth, const int optimalDepth);

struct CostComparator {
    bool operator()(const StatePath& lhs, const StatePath& rhs) const {
        return lhs.second.size() + 0.6*lhs.first.cost() > rhs.second.size() + 0.6*rhs.first.cost();
    }
};