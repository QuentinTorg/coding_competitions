// template from faq for reading in file

// run as $./template.o < input.txt > output.txt
// output.txt will be written to by std::cout
//
// input.txt is test set, formatted as below
// T is number of tests, N and M are two ints
//
// T
// N M
// N M

#include <iostream>

int main() {
  int t, n, m;
  std::cin >> t;  // read t. cin knows that t is an int, so it reads it as such.

  for (int i = 1; i <= t; ++i) {
      std::cin >> n >> m;  // read n and then m.

      std::cout << "Case #" << i << ": " << n*m << std::endl;
  }

  return 0;
}
