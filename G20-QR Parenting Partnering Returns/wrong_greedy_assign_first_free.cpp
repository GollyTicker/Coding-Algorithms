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

const bool debug = true;

template <typename T>
string mkString(const vector<T>& v,int from, int until, const string& pre="[", const string& mid=",", const string& post="]") {
  string s = pre;
  for(int i=from;i<until;i++)
    s += (i>from?mid:"") + to_string(v[i]);
  return s + post;
}

template <typename T>
string mkString(const vector<T>& v, const string& pre="[", const string& mid=",", const string& post="]") {
  return mkString(v,0,v.size(),pre,mid,post);
}

bool tryAssign(vector<bool>& avail, int from, int to) {
  bool free_ = true;
  for(int i=from;i<=to && free_;i++)
    free_ = free_ && !avail[i];

  if (free_) {
    for(int i=from;i<=to && free_;i++) { avail[i] = true; }
  }
  return free_;
}

void problem(int testCase) {
  int n; // age of oldest species, and it's index.
  cin >> n;
  int maxT = 24*60+1;

  vector<bool> tA(maxT,false); // tA[i] = person A is occupied at minute i
  vector<bool> tB(maxT,false);

  map<int,int> end;
  vector<int> s(n,-1);
  vector<int> idx(n,-1);
  for(int i=0;i<n;i++){
    idx[i] = i;
  }
  vector<bool> assignedC(n,false);



  // read input
  for(int i=0;i<n;i++){
    cin >> s[i] >> end[i];
    end[i]--;
    if (debug) cout << "["<<i<<"] Read s,e: " << s[i] << " " << end[i] << endl;
  }

  /* sort indices */
  sort(idx.begin(), idx.end(), [&](int i, int j) {return s[i] <= s[j];});

  if (debug) cout << mkString(idx,"Sorted indices: ["," ") << endl;

  int i0 = 0;
  bool success = true;
  for(int t=0; t<maxT && success && i0<n; t++) {
    // greedy assignment.

    //cout << "t = " << t << endl;
    for(int i=idx[i0]; t == s[i]; i0++,i=idx[i0]) { // process all tasks starting here
      if (debug) cout << "Task beg:" << s[i] << "," << end[i] << endl;
      assignedC[i0] = tryAssign(tA,s[i],end[i]);
      if (debug) cout << i0 << " " << i << " Tried assigning " << s[i] << ", "<< end[i] << " to C: " << assignedC[i0] << endl;
      if (!assignedC[i0]) {
        bool second = tryAssign(tB,s[i],end[i]);
        if (debug) cout << i0 << " " << i << " Then tried assigning " << s[i] << ", "<< end[i] << " to J: " << second << endl;
        success = success && second;
      }
      if (debug) cout << mkString(tA,0,160,"A[","","]") << " and " << mkString(tB,0,160,"B[","","]") << endl;
    }
  }

  cout << "Case #" << testCase << ": ";
  if (success)
    for(int i=0;i<n;i++){
      cout << ( assignedC[i] ? "C" : "J");
    }
  else {
    cout << "IMPOSSIBLE";
  }
  cout << endl;
}

int main(int k,char ** args){
  ios_base::sync_with_stdio(false);
  int t; cin >> t; for(int i=1;i<=t;i++) problem(i); return 0;
}
