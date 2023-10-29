#include <iostream>
#include "Puzzle.h"
#include "Search.h"


using namespace std;

int main()
{
    const Puzzle& puzzle = alpha1();
    const int maxIterations = 20;
    const auto& bestPath = breadthFirstSearch(puzzle, maxIterations);
    std::cout << "Found cost " << bestPath.first.cost() << " in " << bestPath.second.size() << " actions." << std::endl;
    for (const auto& action: bestPath.second) {
        std::cout << (action.type ? "Circle" : "Line") << 
        " (" << CGAL::to_double(action.p1.x()) << ", " << CGAL::to_double(action.p1.y()) << ") - (" 
             << CGAL::to_double(action.p2.x()) << ", " << CGAL::to_double(action.p2.y()) << ")" << std::endl;
    }
}