#include<cstdlib>
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<cmath>
#include<cassert>
#include<ios>
#include<algorithm>
using namespace std;

const bool debug = false;

void problem(int testCase) {
  string s;
  getline(cin >> ws,s); // std::ws discards whitespace from cin stream before giving it to getline

  if (debug) cout << "Read string: " << s << endl;

  cout << "Case #" << testCase << ": ";

  int d = 0; // current depth
  for (int i=0; i < s.length(); i++) {
    int reqd = s.at(i) - '0'; // required depth
    // add nesting or remove nesting until we get to this depth
    int sign = reqd > d ? 1 : -1;
    while (d != reqd) {
      cout << (sign == 1 ? "(" : ")");
      d += sign;
    }
    cout << reqd;
  }
  while(d > 0) { cout << ")"; d--; } // finish nesting

  cout << endl;
}

int main(int k,char ** args){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; for(int i=1;i<=t;i++) problem(i); return 0;
}
