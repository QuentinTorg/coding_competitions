// example

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <set>
using namespace std;

unsigned long int findPrimeFactors(unsigned long int i) {
    if (i % 2 == 0) return 2;
    if (i % 3 == 0) return 3;

    unsigned long int plus, minus, j;
    j = 1;
    do {
        minus = 6 * j - 1;
        plus = 6 * j + 1;

        if (i % minus == 0) return minus;
        if (i % plus == 0) return plus;

        j++;
    } while (plus * plus < i);

    return 1;
}

#include <iostream>
#include <unordered_map>

    template<typename K, typename V>
void printMap(map<K,V> const &m)
{
    for (auto const& pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

template<typename K>
void printVec(const vector<K> &vec) {
    for (int j=0; j < vec.size(); j++) {
        cout << vec[j] << " ";
    }
    cout << endl;
}


int main() {
  int t, n, l;
  cin >> t;  // read t. cin knows that t is an int, so it reads it as such.

  for (int i = 1; i <= t; ++i) {
    cin >> n >> l;  // read n and then l.
    //cout << "length =" << l << endl;

    // fill crypt array
    vector<unsigned long int> crypt(l);
    for (int j= 0; j < l; j++) cin >> crypt[j];

    //printVec(crypt);

    //cout << "minIt" << endl;
    auto minIt = min_element(crypt.begin(), crypt.end());

    //cout << "making factors" << endl;
    unsigned long int fact1, fact2;
    fact1 = findPrimeFactors(*minIt);
    fact2 = *minIt / fact1;
    //cout << "fact1" << fact1 << endl;
    //cout << "fact2" << fact2 << endl;

    vector<unsigned long int> message(l+1);
    unsigned long int i1 = distance(crypt.begin(), minIt);

    //cout << "choosing fact order" << endl;
    // decide order of fact1 and fact2
    if (i1 != 0) {
        if (crypt[i1 - 1] % fact1 == 0) {
            message[i1] = fact1;
            message[i1+1] = fact2;
        }
        else {
            message[i1] = fact2;
            message[i1+1] = fact1;
        }
    }
    else {
        if (crypt[i1 + 1] % fact2 == 0) {
            message[i1] = fact1;
            message[i1+1] = fact2;
        }
        else {
            message[i1] = fact2;
            message[i1+1] = fact1;
        }
    }

    //cout << "filling message" << endl;
    // fill message primes
    //cout << "message len =" << message.size() << endl;
    for (int j=i1+2; j < l+1; j++) {
        //cout << "j=" << j << endl;
        message[j] = crypt[j-1] / message[j-1];
    }
    for (int j=i1-1; j >= 0; j--) {
        //cout << "j=" << j << endl;
        message[j] = crypt[j] / message[j+1];
    }

    //cout << "sorting primes" << endl;
    // fill vector with sorted list of primes
    vector<unsigned long int> alphaPrimes(message);
    set<unsigned long int> s( alphaPrimes.begin(), alphaPrimes.end() );
    alphaPrimes.assign( s.begin(), s.end() );
    sort( alphaPrimes.begin(), alphaPrimes.end() );

    // make alphabet map lookup
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    map<unsigned long int, char> alphaMap;
    for (int j=0; j < alphaPrimes.size(); j++) {
        // implicitly cast int to char
        // ascii captial A is 65
        alphaMap[alphaPrimes[j]] = alphabet[j];
    }

    // create output message
    string messageString = "Case #" + to_string(i) + ": ";
    for (int j=0; j < message.size(); j++) {
        messageString += alphaMap[message[j]];
    }

    cout<< messageString << endl;
  }

  return 0;
}
