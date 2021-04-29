#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "digraphMatrix.h"
using namespace std;

int main()
{

  DigraphMatrix g("input.txt");
  vector<int> component = g.stronglyConnectedComponents();

  cout << "SCC IDs: ";
  for (int cid : component)
    cout << ' ' << cid;
  cout << '\n';

  return 0;
}
