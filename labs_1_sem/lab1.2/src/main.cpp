#include "../include/String.hpp"
#include <iostream>

using namespace std;

void testAdditionOperators() {
    cout << "======= Testing operator '+' =========" << endl;
    String s1, s2;
    cin >> s1 >> s2;
    const char* constString = {"const string"};
    
    String result1 = s1 + s2;
    cout << "object + object = " << result1 << endl;
    
    result1 = s1 + constString;
    cout << "object(s1) + const String('const string') = " << result1 << endl;
    
    result1 = constString + s2;
    cout << "const String('const string') + object(s2) = " << result1 << endl;

}

void testPlusEqualsOperator() {
    cout << "======== Testing operator '+=' ===============" << endl;
    String s1, s2;
    cin >> s1 >> s2;
    
    String s3 = s1;
    s3 += s2;
    cout << "s1 += s2: " << s3 << endl;
}

void testIndexOperator() {
    cout << "======= Testing operator '[]' ========" << endl;
    String s;
    cin >> s;
    
    int index;
    cout << "Enter index: ";
    cin >> index;
    cout << "Char in " << index << " position = " << s[index] << endl;
}

void testSubstringOperator() {
    cout << "======= Testing operator '()' substring ========" << endl;
    String s;
    cin >> s;
    
    int start, end;
    cout << "Enter start and end indices for substring: ";
    cin >> start >> end;
    String subString = s(start, end);
    cout << "Substring (start = " << start << ", end = " << end << ") = " << subString << endl;
}

void testComparisonOperators() {
    cout << "======= Testing comparison operators ========" << endl;
    String s1, s2;
    cin >> s1 >> s2;
    
    cout << "s1 = " << s1 << ", s2 = " << s2 << endl;
    cout << "s1 == s2: " << (s1 == s2) << endl;
    cout << "s1 != s2: " << (s1 != s2) << endl;
    cout << "s1 > s2: " << (s1 > s2) << endl;
    cout << "s1 < s2: " << (s1 < s2) << endl;
    cout << "s1 >= s2: " << (s1 >= s2) << endl;
    cout << "s1 <= s2: " << (s1 <= s2) << endl;
}

void testIncrementDecrementOperators() {
    cout << "======= Testing increment/decrement operators ========" << endl;
    String s5 = "abc";
    cout << "Original string: " << s5 << endl;

    ++s5;
    cout << "After prefix ++: " << s5 << endl;
    
    --s5;
    cout << "After prefix --: " << s5 << endl;

    cout <<"Exiting... ";
}

int main() {
    testAdditionOperators();
    testPlusEqualsOperator();
    testIndexOperator();
    testSubstringOperator();
    testComparisonOperators();
    testIncrementDecrementOperators();
    return 0;
}