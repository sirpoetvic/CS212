/*
 * {Victor}
 * Spring 2024, CS212, William Iverson
 * {April 8th, 2024}
 * {Program 2}
 * {Bits of a C++ program}
 */
#include <iostream>

using namespace std;
const int TEST = 14; // #define in C or const in C++
int main(int argc, char const *argv[])
{
    int test = 14;
    cout << ( 2 & 5 ) << '\n'; // no common bits between 00000010 and 00000101 (bitwise AND), output 0
    cout << ( 2 | 5 ) << '\n'; // inclusive-or 00000010 and 00000101 (bitwise OR), output 7
    cout << ( 256 & 128 ) << '\n'; // no common bits between 1000000000 and 010000000 (bitwise AND), output 0
    cout << ( 256 | 128 ) << '\n'; // inclusive-or 1000000000 and 010000000 (bitwise OR), output 384
    cout << ( TEST ) << '\n'; // it is the const int TEST value, output 14
    cout << ( TEST << 2 ) << '\n'; // left bitwise on 14, or 00001110, moving the values to the left twice, or 00111000 output 56
    cout << ( 14 << 2 ) << '\n'; // left bitwise on 14, or 00001110, moving the values to the left twice, or 00111000 output 56
    cout << ( test << 2 ) << '\n'; // left bitwise on 14, or 00001110, moving the values to the left twice, or 00111000 output 56
    cout << ( test ) << '\n'; // it is the const int test value, output 14
    cout << ( 'G' >> 2 ) << '\n'; // right bitwise on G, or 01000111, moving the values to the right twice, or 00010001, output 17
    cout << ( 'G' << 2 ) << '\n'; // left bitwise on G, or 01000111, moving the values to the left twice, or 100011100, output 284
    cout << ( 'G' & 'H' ) << '\n'; // 1 common bit between 01000111 and 01001000, on the 7th bit, (bitwise AND), output 64
    cout << ( 'G' | 'H' ) << '\n'; // inclusive-or 01000111 and 01001000, (bitwise OR), output 79
    cout << ( 'G' << 222 ) << '\n'; // left bitwise on G, moving the values to the left 222 times, but moves the data out of 32-bit space, output 0
    cout << ( 'G' >> 222 ) << '\n'; // right bitwise on G, moving the values to the right 222 times, but moves the data out of the 32-bit space, output 0
    cout << ( '\n' << 2 ) << '\n'; // left bitwise on \n, or 00001010 moving the values to the left 2 times, or 00101000, output 40 
    cout << ( '\n' >> 2 ) << '\n'; // right bitwise on \n, or 00001010 moving the values to the right 2 times, or 00000010, output 2
    cout << ( 0x14 ) << '\n'; // it is hexadecimal 20, output 20
    cout << ( 0x0000ff00 ) << '\n'; // it is hexadecimal 65280, output 65280
    cout << ( 0x12abcdef ) << '\n'; // it is hexadecimal 313249263, output 313249263
    return 0;
}
