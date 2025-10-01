#include "../include/String.hpp"
#include <iostream>

int main() {

    String s1;
    std::cout << "Testing default constructor. Default s1: " << s1 << std::endl;
    
    String s2;
    std::cout << "Testing constructor with char*. Enter a string for s2: ";
    std::cin >> s2;
    std::cout << "s2: " << s2 << std::endl;

    std::cout << "Testing constructor with size. Enter size for s3: ";
    int size;
    std::cin >> size;
    String s3(size);
    std::cout << "s3 (size " << size << "): " << s3 << std::endl;

    String s4(s2);
    std::cout << "Testing copy constructor. s4 is a copy of s2. s4: " << s4 << std::endl;

    String s5 = s2 + s4;
    std::cout << "Testing operator+. s5 = s2 + s4. Result: " << s5 << std::endl;

    String s6 = s2 + " World";
    std::cout << "Testing operator+. s6 = s2 + ' World'. Result: " << s6 << std::endl;

    String s7 = "Test" + s2;
    std::cout << "Testing operator+. s7 = 'Test' + s2. Result: " << s7 << std::endl;

    s2 += s4;
    std::cout << "Testing operator+=. s2 += s4. New s2: " << s2 << std::endl;

    std::cout << "Testing operator[]. Enter index for s2: ";
    int index;
    std::cin >> index;
    std::cout << "s2[" << index << "]: " << s2[index] << std::endl;

    std::cout << "Testing operator(). Enter start and end indices for s2 substring: ";
    int start, end;
    std::cin >> start >> end;
    String s8 = s2(start, end);
    std::cout << "s2(" << start << "," << end << "): " << s8 << std::endl;
    
    String s9;
    std::cout << "Testing operator> and <. Enter string for s9: ";
    std::cin >> s9;
    String s10;
    std::cout << "Enter string for s10: ";
    std::cin >> s10;
    std::cout << "s9 > s10: " << (s9 > s10) << std::endl;
    std::cout << "s9 < s10: " << (s9 < s10) << std::endl;

    String s11;
    std::cout << "Testing operator++ and --. Enter string for s11: ";
    std::cin >> s11;
    ++s11;
    std::cout << "++s11 (encode): " << s11 << std::endl;
    --s11;
    std::cout << "--s11 (decode): " << s11 << std::endl;

    std::cout << "Testing operator>>. Enter a string for s12: ";
    String s12;
    std::cin >> s12;
    std::cout << "s12: " << s12 << std::endl;

    String s13 = s2;
    std::cout << "Testing operator=. s13 = s2. Result: " << s13 << std::endl;

    return 0;
}