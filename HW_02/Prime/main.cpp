#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int i, j, cnt;
    int start_num;
    int end_num;
    cout << "Find prime number within a range:\n";
    cout << "--------------------------------------\n";
    cout << "-> The start of the range: ";
    cin >> start_num;
    cout << "-> The end of the range: ";
    cin >> end_num;
    cout << "The prime numbers between " << start_num
          << " and " << end_num << " are:\n";
          
    for (int i= start_num ; i < end_num+1; i++)
    {
        cnt = 0;
        for (int j = 2; j <= i; j++)
        {
            if (i % j == 0) {cnt++;}
        }
        if (cnt == 1) {cout << i << " ";}
    }
    cout << endl;
    return 0;
}
