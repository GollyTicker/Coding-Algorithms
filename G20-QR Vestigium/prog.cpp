#include<cstdlib>
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<cmath>
#include<cassert>
#include<ios>
#include<algorithm>
#include <unordered_set>
using namespace std;

const bool debug = false;

typedef vector< vector<int> > matrix;

bool hasDuplicates(const matrix& M, int k, bool isRow) {
  unordered_set<int> s;

  for(int l=1;l<M.size();l++) {
    int x = isRow? M[k][l] : M[l][k];
    if (s.find(x) != s.end()) {
      //cout << "Found duplicate " << x << " in " << (isRow?"row":"col") << " " << k << endl;
      return true;
    }
    s.insert(x);
  }
  return false;
}

void problem(int testCase) {
  int n;
  cin >> n;

  matrix M(n+1,vector<int>(n+1,-1));

  for (int i=1; i<=n; i++) {
    for (int j=1; j<=n; j++) {
      cin >> M[i][j];
    }
  }

  int trace = 0;
  for(int i=1;i<=n;i++) trace+= M[i][i];

  int dupRows = 0;
  for (int i=1;i<=n;i++)
    if (hasDuplicates(M,i,true))
      dupRows++;

  int dupCols = 0;
  for (int j=1;j<=n;j++)
    if (hasDuplicates(M,j,false))
      dupCols++;

  cout << "Case #" << testCase << ": ";
  cout << trace << " " << dupRows << " " << dupCols;
  cout << endl;
}

int main(int k,char ** args){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; for(int i=1;i<=t;i++) problem(i); return 0;
}
