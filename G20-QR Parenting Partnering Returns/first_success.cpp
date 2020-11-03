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

bool tryAssign(vector<bool>& occupied, int from, int to) {
  bool free_ = true;
  for(int i=from;i<=to && free_;i++)
    free_ = free_ && !occupied[i];

  if (free_) {
    for(int i=from;i<=to;i++) { occupied[i] = true; }
  }
  return free_;
}

void problem(int testCase) {
  int n; // age of oldest species, and it's index.
  cin >> n;

  vector<int> s(n,-1);
  vector<int> idx(n,-1);
  for(int i=0;i<n;i++){
    idx[i] = i;
  }
  map<int,int> end;
  vector<bool> assignedC(n,false);

  // read input
  int maxT = 0;
  for(int i=0;i<n;i++){
    cin >> s[i] >> end[i];
    end[i]--;
    if (debug) cout << "["<<i<<"] Read s,e: " << s[i] << " " << end[i] << endl;
    maxT = max(maxT,max(s[i],end[i]+1));
  }

  vector<bool> tA(maxT,false); // tA[i] = person A is occupied at minute i
  vector<bool> tB(maxT,false);

  /* sort indices: first order by earliest start time. then sort b by earliest end time. */
  sort(idx.begin(), idx.end(), [&](int i, int j) {return s[i] == s[j]? end[i] < end[j] : s[i] <= s[j];});

  if (debug) cout << mkString(idx,"Sorted indices: ["," ") << endl;

  int i0 = 0;
  bool success = true;
  for(int t=0; t<maxT && success && i0<n; t++) {
    // greedy assignment.

    //cout << "t = " << t << endl;
    for(int i=idx[i0]; i0<n && t == s[i] && success; i0++,i=idx[i0]) { // process all tasks ending here
      if (debug) cout << "Task beg:" << s[i] << "," << end[i] << endl;
      assignedC[i] = tryAssign(tA,s[i],end[i]);
      if (debug) cout << i0 << " " << i << " ["<< success<<"] Tried assigning " << s[i] << ", "<< end[i] << " to C: " << assignedC[i] << endl;
      if (!assignedC[i]) {
        bool second = tryAssign(tB,s[i],end[i]);
        success = success && second;
        if (debug) cout << i0 << " " << i << " ["<< success<<"] Then tried assigning " << s[i] << ", "<< end[i] << " to J: " << second << endl;
      }
      if (debug) cout << mkString(tA,0,maxT,"A[","","]") << " and " << mkString(tB,0,maxT,"B[","","]") << endl;
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
