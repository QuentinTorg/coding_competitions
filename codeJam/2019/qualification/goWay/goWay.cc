// example

#include <iostream>  // includes cin to read from stdin and cout to write to stdout
#include <string>  // includes cin to read from stdin and cout to write to stdout
using namespace std;  // since cin and cout are both in namespace std, this saves some text

void newPath(string& n) {

    for (int i = 0; i < n.length(); i++) {
        if (n[i] == 'E') {
            n[i] = 'S';
        }
        else {
            n[i] = 'E';
        }
    }
}

int main() {
  int t;
  string n, path;
  cin >> t;  // read t. cin knows that t is an int, so it reads it as such.

  for (int i = 1; i <= t; ++i) {
    cin >> n;  // read n and then m.
    cin >> path;  // read n and then m.

    newPath(path);

    cout<<"Case #"<<i<<": "<< path << endl;
  }

  return 0;
}
