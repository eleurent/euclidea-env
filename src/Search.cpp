#include <queue>
#include "Search.h"


StatePath breadthFirstSearch(const Puzzle& puzzle, int maxIterations) {
    int iterations = 0;
    std::queue<StatePath> puzzleQueue;
    Path emptyPath = {};
    StatePath bestPath = std::make_pair(puzzle, emptyPath);
    float bestCost = puzzle.cost();
    puzzleQueue.push(bestPath);

    while (!puzzleQueue.empty() && ++iterations < maxIterations) {
        const auto puzzlePath = puzzleQueue.front();
        const Puzzle currentPuzzle = puzzlePath.first;
        Path currentPath = puzzlePath.second;
        puzzleQueue.pop();

        std::vector<Puzzle::Action> actions = currentPuzzle.availableActions();
        for (const Puzzle::Action& action : actions) {
            const Puzzle childPuzzle = currentPuzzle.applyAction(action);
            Path newPath;
            newPath.assign(currentPath.begin(), currentPath.end());
            newPath.push_back(action);
            const StatePath newPuzzlePath = std::make_pair(childPuzzle, newPath);

            if (childPuzzle.cost() < bestCost) {
                bestCost = childPuzzle.cost();
                bestPath = newPuzzlePath;
            }
            if (bestCost == 0)
                return bestPath;

            puzzleQueue.push(newPuzzlePath);
        }
    }
    return bestPath;
}