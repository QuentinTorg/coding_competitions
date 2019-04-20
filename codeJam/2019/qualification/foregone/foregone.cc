// example

#include <iostream>  // includes cin to read from stdin and cout to write to stdout
#include <string>  // includes cin to read from stdin and cout to write to stdout
using namespace std;  // since cin and cout are both in namespace std, this saves some text

struct Solution {
    string a, b;
};

Solution remFour(string& n) {
    string m(n.length(), '0');

    size_t found = n.find_first_of("4");
    while (found != string::npos) {
        n[found] = '2';
        m[found] = '2';
        found = n.find_first_of("4", found+1);
    }

    found = m.find_first_of("123456789");
    if (found != string::npos) {
        m.erase(0,found);
    }
    else {
        m = "0";
    }

    Solution solution;
    solution.a = n;
    solution.b = m;
    return solution;
}

int main() {
  int t;
  string n;
  cin >> t;  // read t. cin knows that t is an int, so it reads it as such.

  for (int i = 1; i <= t; ++i) {
    cin >> n;  // read n and then m.
    Solution solution;
    solution = remFour(n);

    cout<<"Case #"<<i<<": "<< solution.a << " " << solution.b << endl;
  }

  return 0;
}
