#include <iostream>
#include "Puzzle.h"
#include "Search.h"


using namespace std;

int main()
{
    for (auto& puzzle: {
        // alpha0_equilateral_triangle(),
        // alpha2_mediator(),
        // alpha3_midpoint(),
        // alpha4_circle_in_square(),
        // alpha5_diamond_in_rectangle(),
        // alpha7_inscribed_square(),
        // beta1_bisector(),
        beta8_tangent_to_line_at_point(),
        }) {
        const int maxIterations = 3000;
        // const auto& bestPath = breadthFirstSearch(puzzle, maxIterations);
        const auto& bestPath = aStarSearch(puzzle, maxIterations, puzzle.optimalDepth+2, puzzle.optimalDepth);
        std::cout << "Found cost " << bestPath.first.cost() << " in " << bestPath.second.size() << " actions." << std::endl;
        for (const auto& action: bestPath.second) {
            std::cout << (action.type ? "Circle" : "Line") << ": " << action.p1 << " - " << action.p2 << std::endl;
        }
    }
}