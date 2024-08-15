#include <iostream>
#include <string>

bool isPalindrome(const std::string &str) {
    int left = 0;
    int right = str.length() - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

std::string findLongestPalindrome(const std::string &binaryNumber) {
    int maxLength = 0;
    std::string longestPalindrome;

    for (int i = 0; i < binaryNumber.length(); ++i) {
        for (int j = i; j < binaryNumber.length(); ++j) {
            std::string substring = binaryNumber.substr(i, j - i + 1);
            if (isPalindrome(substring) && substring.length() > maxLength) {
                maxLength = substring.length();
                longestPalindrome = substring;
            }
        }
    }

    return longestPalindrome;
}

int main() {
    std::string binaryNumber;

    // Input binary number from the user
    std::cout << "Enter a binary number: ";
    std::cin >> binaryNumber;

    // Find and display the longest palindrome
    std::string longestPalindrome = findLongestPalindrome(binaryNumber);
    if (longestPalindrome.empty()) {
        std::cout << "No palindrome found in the given binary number." << std::endl;
    } else {
        std::cout << "Longest palindrome in the binary number: " << longestPalindrome << std::endl;
    }

    return 0;
}
