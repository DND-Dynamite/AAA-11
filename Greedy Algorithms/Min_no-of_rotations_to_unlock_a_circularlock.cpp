// You are given a lock which is made up of n-different circular rings and each ring has 0-9 digit 
// printed serially on it. Initially all n-rings together show a n-digit integer but there
// is particular code only which can open the lock. You can rotate each ring any number of
// time in either direction. You have to find the minimum number of rotation done on rings
// of lock to open the lock.

// Input : Input = 2345, Unlock code = 5432 
// Output : Rotations required = 8
// Explanation : 1st ring is rotated thrice as 2->3->4->5
//               2nd ring is rotated once as 3->4
//               3rd ring is rotated once as 4->3
//               4th ring is rotated thrice as 5->4->3->2

// Input : Input = 1919, Unlock code = 0000 
// Output : Rotations required = 4
// Explanation : 1st ring is rotated once as 1->0
//               2nd ring is rotated once as 9->0
//               3rd ring is rotated once as 1->0
//               4th ring is rotated once as 9->0 


// CPP program for min rotation to unlock
#include <iostream>
#include <cmath>

using namespace std;

// function for min rotation
int minRotation(int input, int unlock_code)
{
    int rotation = 0;
    int input_digit, code_digit;

    // iterate till input and unlock code become 0
    while (input || unlock_code) {
  
        // input and unlock last digit as reminder
        input_digit = input % 10;
        code_digit = unlock_code % 10;

        // find min rotation
        rotation += min(abs(input_digit - code_digit), 
                   10 - abs(input_digit - code_digit));

        // update code and input
        input /= 10;
        unlock_code /= 10;
    }

    return rotation;
}

// driver code
int main()
{
    int input = 28756;
    int unlock_code = 98234;
    cout << "Minimum Rotation = "
        << minRotation(input, unlock_code);
    return 0;
}