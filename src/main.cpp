#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"euclidea-env main"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}