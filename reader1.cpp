// example for thread::join
#include <bits/stdc++.h>       // std::cout
using namespace std;

int main() 
{ 
  string reg_id_ex="doggie";
  int id_ex;
  stringstream ss;
  ss << reg_id_ex;
  ss >> id_ex;
  cout << id_ex << endl;
  return 0;
}