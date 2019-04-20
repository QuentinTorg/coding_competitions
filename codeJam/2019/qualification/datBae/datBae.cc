// example

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

//pairs are always (total, numBroken)
//always start messages with 0

void printDataVec(vector<tuple<int, int, char>> v) {
    for(auto it = v.begin(); it != v.end(); ++it) {
        int total  = get<0>(*it);
        int broken = get<1>(*it);
        char start = get<2>(*it);

        cout << "total=" << total << " broken=" << broken << " start=" << start << endl;
    }
}


string genTestString(const vector<tuple<int, int, char>> & v) {
    string test = "";
    bool solved = true;

    // for each tuple in vector
    for(auto it = v.begin(); it != v.end(); ++it) {
        int total = get<0>(*it);
        int broken = get<1>(*it);

        if (total != broken && broken != 0) solved = false;

        int first = (total / 2.0) + 0.51;
        int second = total - first;

        test += string(first,  '0');
        test += string(second, '1');
    }
    // return empty string if solved
    if (solved) return "";
    else return test;
}

void sendSolution(const vector<tuple<int, int, char>> & v) {
    // solved when every pair is either equal or .second is 0
    string solution = "";
    int index = 0;
    for(auto it = v.begin(); it != v.end(); ++it) {
        int total  = get<0>(*it);
        int broken = get<1>(*it);

        if (broken == 0) index += total;
        for (; broken > 0; broken--, index++) {
            solution += to_string(index) + " ";
        }
    }

    cout << solution << endl;
}

string genFirstTest(int total, int broken) {
    string test = "";
    int n = broken+1;
    char num = '1';

    while (total > test.size()) {
        // decide value and length to append to test
        num == '1' ? num = '0' : num = '1';
        if (total - test.size() < n) n = total - test.size();

        // append to test string
        test += string(n, num);
    }
    return test;
}

vector<tuple<int, int, char>> parseFirstResponse(const string & resp, const string & test) {
    vector<tuple<int, int, char>> data;
    size_t prevTestInd = 0;
    size_t prevRespInd = 0;
    char val = '0';

    while (true) {
        // vector will alternate every 16 until there are fewer than 16 left
        int testInd = test.find_first_not_of(val, prevTestInd);
        int respInd = resp.find_first_not_of(val, prevRespInd);

        if (testInd == string::npos) testInd = test.size();
        if (respInd == string::npos) respInd = resp.size();
        int testNum = testInd - prevTestInd;
        int respNum = respInd - prevRespInd;

        data.push_back(make_tuple(testNum, testNum - respNum, val));

        if (respInd == resp.size()) {
            if (testInd != test.size()) {
                // if resp ended one increment sooner than test, account for rest of test
                testNum = test.size() - testInd;
                // all broken in this last section
                val == '1' ? val = '0' : val = '1';
                data.push_back(make_tuple(testNum, testNum, val == '1' ? '0' : '1'));
            }
            break;
        }
        val == '1' ? val = '0' : val = '1';
        prevTestInd = testInd;
        prevRespInd = respInd;
    }
    return data;
}

vector<tuple<int, int, char>> parseResponse(const string & resp, const string & test,
        const vector<tuple<int, int, char>> & oldData) {
    vector<tuple<int, int, char>> data;
    size_t respStartInd = 0;
    size_t testStartInd = 0;

    for(auto it = oldData.begin(); it != oldData.end(); ++it) {
        int total  = get<0>(*it);
        int broken = get<1>(*it);

        size_t respLen = total - broken;

        string subResp = resp.substr(respStartInd, respLen);
        string subTest = test.substr(testStartInd, total);

        // get index where transition happens
        // num of "start" char in first half = firstNot
        size_t firstNotResp = subResp.find_first_not_of(subTest[0]);
        if (firstNotResp == string::npos) firstNotResp = subResp.size();
        size_t secondNotResp = subResp.size() - firstNotResp;

        size_t firstNotTest = subTest.find_first_not_of(subTest[0]);
        if (firstNotTest == string::npos) firstNotTest = subTest.size();
        size_t secondNotTest = subTest.size() - firstNotTest;

        // check what happens if all of first half gone
        //     all of second half gone
        //     all gone, so empty response string,
        //     and both still exist

        // for now I think this is general case
        size_t total1 = firstNotTest;
        size_t broken1 = firstNotTest - firstNotResp;
        size_t total2 = secondNotTest;
        size_t broken2 = secondNotTest - secondNotResp;

        data.push_back(make_tuple(total1, broken1, subTest[0]));
        if (total2 != 0) {
            // only add second tuple if there is second half of total,
            data.push_back(make_tuple(total2, broken2, subTest[0]=='0' ? '1':'0'));
        }

        respStartInd += respLen;
        testStartInd += total;
    }

    return data;
}


int main() {
  uint32_t num, broken, lim, t;
  cin >> t;  // read t. cin knows that t is an int, so it reads it as such.

  for (int i = 1; i <= t; ++i) {
    cin >> num >> broken >> lim;

    string test = genFirstTest(num, broken);
    cout << test << endl;

    string response;
    cin >> response;

    auto data = parseFirstResponse(response, test);

    while (true) {

        test = genTestString(data);

        if (test == "") {
            break;
        }
        // send test and get response
        cout << test << endl;
        cin >> response;

        data = parseResponse(response, test, data);
        //printDataVec(testVec);
    }
    sendSolution(data);
    int verdict;
    cin >> verdict;
    if (verdict != 1) {
        throw runtime_error("got answer incorrect");
    }
  }

  return 0;
}
