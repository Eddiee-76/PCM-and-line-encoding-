#include <iostream>
#include <vector>

using namespace std;

bool isPalindrome(const vector<int> &arr, int start, int end) {
    while (start < end) {
        if (arr[start] != arr[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

vector<int> findLongestPalindrome(const vector<int> &binaryArray) {
    int maxLength = 0;
    vector<int> longestPalindrome;

    for (int i = 0; i < binaryArray.size(); ++i) {
        for (int j = i; j < binaryArray.size(); ++j) {
            if (isPalindrome(binaryArray, i, j) && (j - i + 1) > maxLength) {
                maxLength = j - i + 1;
                longestPalindrome = vector<int>(binaryArray.begin() + i, binaryArray.begin() + j + 1);
            }
        }
    }

    return longestPalindrome;
}

int main() {
    vector<int> binaryArray;

    // Input binary number as an integer array
    cout << "Enter the size of the binary array: ";
    int size;
    cin >> size;

    cout << "Enter the binary array elements (0 or 1): ";
    for (int i = 0; i < size; ++i) {
        int bit;
        cin >> bit;
        binaryArray.push_back(bit);
    }

    // Find and display the longest palindrome
    vector<int> longestPalindrome = findLongestPalindrome(binaryArray);
    if (longestPalindrome.empty()) {
        cout << "No palindrome found in the given binary array." << endl;
    } else {
        cout << "Longest palindrome in the binary array: ";
        for (int bit : longestPalindrome) {
            cout << bit << " ";
        }
        cout << endl;
    }

    return 0;
}
