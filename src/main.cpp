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
        alpha4_circle_in_square(),
        // beta8_tangent_to_line_at_point(),
        }) {
        const int maxIterations = 2000;
        // const auto& bestPath = breadthFirstSearch(puzzle, maxIterations);
        const auto& bestPath = aStarSearch(puzzle, maxIterations);
        std::cout << "Found cost " << bestPath.first.cost() << " in " << bestPath.second.size() << " actions." << std::endl;
        for (const auto& action: bestPath.second) {
            std::cout << (action.type ? "Circle" : "Line") << 
            " (" << CGAL::to_double(action.p1.x()) << ", " << CGAL::to_double(action.p1.y()) << ") - (" 
                << CGAL::to_double(action.p2.x()) << ", " << CGAL::to_double(action.p2.y()) << ")" << std::endl;
        }
    }
}