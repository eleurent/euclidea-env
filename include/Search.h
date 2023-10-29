#include "Puzzle.h"
typedef std::vector<Puzzle::Action> Path;
typedef std::pair<Puzzle, Path> StatePath;

StatePath breadthFirstSearch(const Puzzle& puzzle, int maxIterations);

