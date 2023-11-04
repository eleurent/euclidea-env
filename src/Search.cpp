#include <queue>
#include <unordered_set>
#include "Search.h"


StatePath breadthFirstSearch(const Puzzle& puzzle, const int maxIterations, const int maxDepth, const int optimalDepth) {
    int iterations = 0;
    std::queue<StatePath> puzzleQueue;
    Path emptyPath = {};
    StatePath bestPath = std::make_pair(puzzle, emptyPath);
    float bestCost = puzzle.cost();
    puzzleQueue.push(bestPath);
    std::unordered_set<PuzzleState> discoveredStates;

    while (!puzzleQueue.empty() && ++iterations < maxIterations) {
        if (iterations % (maxIterations / 10) == 0) {
            std::cout << "Iteration " << iterations << " - best cost so far: " << bestCost << ", best path depth: " << bestPath.second.size() << std::endl;
        }
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
            if (bestCost > 0 && newPath.size() < maxDepth) {
                if (discoveredStates.count(childPuzzle.state)) {
                    continue;
                }
                else {
                    discoveredStates.insert(childPuzzle.state);
                }
                puzzleQueue.push(newPuzzlePath);
            }
        }
    }
    return bestPath;
}


StatePath aStarSearch(const Puzzle& puzzle, const int maxIterations, const int maxDepth, const int optimalDepth) {
    int iterations = 0;
    std::priority_queue<StatePath, std::vector<StatePath>, CostComparator> puzzleQueue;
    Path emptyPath = {};
    StatePath bestPath = std::make_pair(puzzle, emptyPath);
    float bestCost = puzzle.cost();
    puzzleQueue.push(bestPath);
    std::unordered_set<PuzzleState> discoveredStates;

    while (!puzzleQueue.empty() && ++iterations < maxIterations) {
        const auto puzzlePath = puzzleQueue.top();
        puzzleQueue.pop();
        const Puzzle currentPuzzle = puzzlePath.first;
        Path currentPath = puzzlePath.second;

        if (iterations % (maxIterations / 20 ) == 0) {
            std::cout << "[" << iterations << "/" << maxIterations << "] - best cost so far: " << bestCost << ", best path depth: " << bestPath.second.size() << ", current depth: " << currentPath.size() << ", queue size: " << puzzleQueue.size() << std::endl;
        }

        std::vector<Puzzle::Action> actions = currentPuzzle.availableActions();
        for (const Puzzle::Action& action : actions) {
            const Puzzle childPuzzle = currentPuzzle.applyAction(action);
            Path newPath;
            newPath.assign(currentPath.begin(), currentPath.end());
            newPath.push_back(action);
            const StatePath newPuzzlePath = std::make_pair(childPuzzle, newPath);

            const float newCost = childPuzzle.cost();
            if (newCost < bestCost) {
                bestCost = newCost;
                bestPath = newPuzzlePath;
            }
            if (newCost == 0 && newPath.size() == optimalDepth)
                return bestPath;
            if (newCost > 0 && newPath.size() < maxDepth) {
                if (discoveredStates.count(childPuzzle.state)) {
                    continue;
                }
                else {
                    discoveredStates.insert(childPuzzle.state);
                }
                puzzleQueue.push(newPuzzlePath);
            }
        }
    }
    return bestPath;
}
