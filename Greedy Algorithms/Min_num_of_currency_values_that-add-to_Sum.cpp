// Given an amount, find the minimum number of notes of different denominations that sum up to the given amount. Starting from the highest denomination note, try to accommodate as many notes as possible for a given amount. We may assume that we have infinite supply of notes of values {2000, 500, 200, 100, 50, 20, 10, 5, 1} 
// Examples:  

// Input : 800
// Output : Currency  Count 
//          500 : 1
//          200 : 1
//          100 : 1

// Input : 2456
// Output : Currency  Count
//          2000 : 1
//          200 : 2
//          50 : 1
//          5 : 1
//          1 : 1

// C++ program to accept an amount
// and count number of notes
#include  <iostream>
using namespace std;

// function to count and 
// print currency notes
void countCurrency(int amount)
{
    int notes[9] = { 2000, 500, 200, 100,
                     50, 20, 10, 5, 1 };
    int noteCounter[9] = { 0 };
    
    // count notes using Greedy approach
    for (int i = 0; i < 9; i++) {
        if (amount >= notes[i]) {
            noteCounter[i] = amount / notes[i];
            amount = amount % notes[i];
        }
    }
    
    // Print notes
    cout << "Currency Count ->" << endl;
    for (int i = 0; i < 9; i++) {
        if (noteCounter[i] != 0) {
            cout << notes[i] << " : " 
                << noteCounter[i] << endl;
        }
    }
}

// Driver function
int main()
{
    int amount = 868;
    countCurrency(amount);
    return 0;
}