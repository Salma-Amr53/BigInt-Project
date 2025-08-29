#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

class BigInt
{
private:
    string number;   // Stores the number as a string
    bool isNegative; // True if number is negative

    // Remove unnecessary leading zeros from the number string
    void removeLeadingZeros()
    {
        // TODO: Implement this function
    }

    // Compare absolute values of two BigInts (ignore signs)
    // Returns: 1 if |this| > |other|, 0 if equal, -1 if |this| < |other|
    int compareMagnitude(const BigInt &other) const
    {
        // TODO: Implement this function
        return 0;
    }

public:
    // Default constructor - initialize to zero
    BigInt()
    {
        // TODO: Implement this constructor
    }

    // Constructor from 64-bit integer
    BigInt(int64_t value)
    {
        // TODO: Implement this constructor
        int64_t x = (value);
    }

    // Constructor from string representation
    BigInt(const string &str)
    {
        // TODO: Implement this constructor
    }

    // Copy constructor
    BigInt(const BigInt &other)
    {
        // TODO: Implement this constructor
    }

    // Destructor
    ~BigInt()
    {
        // TODO: Implement if needed
    }

    BigInt &operator=(const BigInt &other)
    {
        // TODO: Implement this operator
        return *this;
    }

    // Unary negation operator (-x)
    BigInt operator-() const
    {
        BigInt result;
        result.number = this->number;

        if (number == "0") // if 0 then don't do anything
        {
            result.isNegative = false;
        }
        else
        {
            result.isNegative = !(this->isNegative); // this means the given BigInt ex - 1234 "1234" is "this"
        }

        return result;
    }

    // Unary plus operator (+x)
    BigInt operator+() const
    {
        // TODO: Implement this operator
        BigInt result;
        result.number = this->number;
        result.isNegative = this->isNegative;
        return result;
    }

    // Addition assignment operator (x += y)
    BigInt &operator+=(const BigInt &other)
    {
        // TODO: Implement this operator
        *this = *this + other;
        return *this;
    }

    // Subtraction assignment operator (x -= y)
    BigInt &operator-=(const BigInt &other)
    {
        // TODO: Implement this operator
        *this = *this - other;
        return *this;
    }

    // Multiplication assignment operator (x *= y)
    BigInt &operator*=(const BigInt &other)
    {
        // TODO: Implement this operator
        *this = *this * other;
        return *this;
    }

    // Division assignment operator (x /= y)
    BigInt &operator/=(const BigInt &other)
    {
        // TODO: Implement this operator
        *this = *this / other;
        return *this;
    }

    // Modulus assignment operator (x %= y)
    BigInt &operator%=(const BigInt &other)
    {
        // TODO: Implement this operator
        *this = *this % other;
        return *this;
    }

    // Pre-increment operator (++x)
    BigInt &operator++()
    {
        *this += BigInt(1); // add 1 to current object
        return *this;       // returns the added object before doing the intended function
    }

    // Post-increment operator (x++)
    BigInt operator++(int)
    {
        BigInt temp = *this; // save this current value
        *this += BigInt(1);  // increment it
        return temp;         // but return the old value to do the needed
    }

    // Pre-decrement operator (--x)   THE SAME AS THE INCREMENT
    BigInt &operator--()
    {
        *this -= BigInt(1);
        return *this;
    }

    // Post-decrement operator (x--)
    BigInt operator--(int)
    {
        BigInt temp = *this;
        *this -= BigInt(1);
        return temp;
    }

    // Convert BigInt to string representation
    string toString() const
    {
        // TODO: Implement this function    // hint use the isNegative bool to add '-' or not
        return "";
    }

    // Output stream operator (for printing)            -hazem
    friend ostream &operator<<(ostream &os, const BigInt &num) // os here is like cout <<
    {                                                          //  this is os <------/     | - > operator
        // TODO: Implement this operator
        if (num.isNegative && num.number != "0") // if the number is negative
        {
            os << "-"; // print "-"
        }
        // prints the number anyway if it was negative the if condition above handles it
        os << num.number;
        return os;
    }

    // Input stream operator (for reading from input)
    friend istream &operator>>(istream &is, BigInt &num) // -hazem
    {
        string input;        // if the user enters "1235" it is stored as a string
        is >> input;         // read the string from input (like cin) and store it in input
        num = BigInt(input); // then use input to make string constructor to create BigInt
        return is;
    }

    // Friend declarations for comparison operators
    friend bool operator==(const BigInt &lhs, const BigInt &rhs);
    friend bool operator<(const BigInt &lhs, const BigInt &rhs);
    friend BigInt operator+(BigInt lhs, const BigInt &rhs);
    friend BigInt operator-(BigInt lhs, const BigInt &rhs);

    bool getNegative() const
    {
        return isNegative;
    }
    string getNumber() const
    {
        return number;
    }
};

// Binary addition operator (x + y)
BigInt operator+(BigInt lhs, const BigInt &rhs)
{
    BigInt result;

    int carry = 0;
    // get sizes
    int i = lhs.number.length() - 1;
    int j = rhs.number.length() - 1;

    while (i >= 0 && j >= 0)
    {
        int firstDigit = lhs.number[i] - '0';  // the rightmost number in the first number
        int secondDigit = rhs.number[j] - '0'; // the rightmost number in the second number

        int sum = firstDigit + secondDigit + carry;

        // if sum is 16 then carry is 1 and digit is 6

        carry = sum / 10;     // carry is 0 or 1
        int digit = sum % 10; // digit is 0-9      , this is the digit to add in the result

        // enters that number in the beginning of result ex result is "123" sum is 8 so new number is "8123"
        result.number = char(digit + '0') + result.number; // change it to char because it is one digit

        i--;
        j--;
    }

    // the next 2 whiles is just getting every number out of either the first number or the second number
    while (i >= 0)
    {
        int firstDigit = lhs.number[i] - '0';
        int sum = firstDigit + carry;
        carry = sum / 10;
        int digit = sum % 10;
        result.number = char(digit + '0') + result.number;
        i--;
    }

    while (j >= 0)
    {
        int secondDigit = rhs.number[j] - '0';
        int sum = secondDigit + carry;
        carry = sum / 10;
        int digit = sum % 10;
        result.number = char(digit + '0') + result.number;
        j--;
    }

    // if there is still a carry after finishing then it means that there is no 1 at the end
    // so we must add it
    if (carry) // 0 or 1
    {
        result.number = char(carry + '0') + result.number;
    }

    return result;
}

// Binary subtraction operator (x - y)
BigInt operator-(BigInt lhs, const BigInt &rhs)
{
    BigInt result;
    result.number = "";
    result.isNegative = false;

    int borrow = 0;
    int i = lhs.number.length() - 1;
    int j = rhs.number.length() - 1;

    while (i >= 0 && j >= 0)
    {
        int firstDigit = lhs.number[i] - '0';
        int secondDigit = rhs.number[j] - '0';

        if (borrow)
        {
            if (firstDigit == 0)
            {
                // if the digit is 0 and i take borrow from it it becomes -1 but
                // but -1 is invalid so we have to take borrow from the left so it becomes -1 + 10 = 9
                firstDigit = 9;
                // leave borrow = 1 because we took 1 from the left digit
            }
            else
            {
                firstDigit--;
                borrow = 0;
            }
            int digit;
            if (firstDigit >= secondDigit)
            {
                digit = firstDigit - secondDigit;
            }
            else
            {
                firstDigit += 10;
                borrow = 1;
                digit = firstDigit - secondDigit;
            }
            result.number = char(digit + '0') + result.number;
            i--;
            j--;
        }
    }
    // handle remaining digits from first number
    int firstDigit = lhs.number[i] - '0';
    if (borrow)
    {
        if (firstDigit == 0)
        {
            firstDigit = 9;
        }
        else
        {
            firstDigit--;
        }
        borrow = 0;
        lhs.number[i] = char(firstDigit + '0');
    }

    while (i >= 0)
    {
        int firstDigit = lhs.number[i] - '0';
        i--;
    }

    // Second number shouldn't have remaining digits in proper subtraction
    // If j >= 0, it means rhs > lhs, which would give negative result
    // For now, we'll ignore remaining digits from rhs

    // Remove leading zeros but keep at least one digit
    while (result.number.length() > 1 && result.number[0] == '0')
    {
        result.number = result.number.substr(1);
    }

    return result;
}

// Binary multiplication operator (x * y)
BigInt operator*(BigInt lhs, const BigInt &rhs)
{
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Binary division operator (x / y)
BigInt operator/(BigInt lhs, const BigInt &rhs)
{
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Binary modulus operator (x % y)
BigInt operator%(BigInt lhs, const BigInt &rhs)
{
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Equality comparison operator (x == y)
bool operator==(const BigInt &lhs, const BigInt &rhs)
{

    return (lhs.getNegative() == rhs.getNegative()) && (lhs.getNumber() == rhs.getNumber());
}

// Inequality comparison operator (x != y)
bool operator!=(const BigInt &lhs, const BigInt &rhs)
{

    return (lhs.getNegative() != rhs.getNegative()) || (lhs.getNumber() != rhs.getNumber());
}

// Less-than comparison operator (x < y)
bool operator<(const BigInt &lhs, const BigInt &rhs)
{
    if (lhs.isNegative && !rhs.isNegative)
    {
        return true;
    }
    if (!lhs.getNegative() && rhs.getNegative())
    {
        return false;
    }
    int x = lhs.compareMagnitude(rhs);
    if (!lhs.getNegative() && !rhs.getNegative())
    {
        return x < 0;
    }
    else
    {
        return x > 0;
    }
    return false;
    // TODO: Implement this operator
}

// Less-than-or-equal comparison operator (x <= y)
bool operator<=(const BigInt &lhs, const BigInt &rhs)
{
    return (lhs < rhs) || (lhs == rhs);
    // TODO: Implement this operator
    return false;
}

// Greater-than comparison operator (x > y)
bool operator>(const BigInt &lhs, const BigInt &rhs)
{
    return !(lhs <= rhs);
    // TODO: Implement this operator
    return false;
}

// Greater-than-or-equal comparison operator (x >= y)
bool operator>=(const BigInt &lhs, const BigInt &rhs)
{
    return (lhs > rhs) || (lhs == rhs);

    // TODO: Implement this operator
    return false;
}

int main()
{
    cout << "=== BigInt Class Test Program ===" << endl
         << endl;
    cout << "NOTE: All functions are currently empty." << endl;
    cout << "Your task is to implement ALL the functions above." << endl;
    cout << "The tests below will work once you implement them correctly." << endl
         << endl;

    /*
    // Test 1: Constructors and basic output
    cout << "1. Constructors and output:" << endl;
    BigInt a(12345);              // Should create BigInt from integer
    BigInt b("-67890");           // Should create BigInt from string
    BigInt c("0");                // Should handle zero correctly
    BigInt d = a;                 // Should use copy constructor
    cout << "a (from int): " << a << endl;        // Should print "12345"
    cout << "b (from string): " << b << endl;     // Should print "-67890"
    cout << "c (zero): " << c << endl;            // Should print "0"
    cout << "d (copy of a): " << d << endl << endl; // Should print "12345"

    // Test 2: Arithmetic operations
    cout << "2. Arithmetic operations:" << endl;
    cout << "a + b = " << a + b << endl;          // Should calculate 12345 + (-67890)
    cout << "a - b = " << a - b << endl;          // Should calculate 12345 - (-67890)
    cout << "a * b = " << a * b << endl;          // Should calculate 12345 * (-67890)
    cout << "b / a = " << b / a << endl;          // Should calculate (-67890) / 12345
    cout << "a % 100 = " << a % BigInt(100) << endl << endl; // Should calculate 12345 % 100

    // Test 3: Relational operators
    cout << "3. Relational operators:" << endl;
    cout << "a == d: " << (a == d) << endl;       // Should be true (12345 == 12345)
    cout << "a != b: " << (a != b) << endl;       // Should be true (12345 != -67890)
    cout << "a < b: " << (a < b) << endl;         // Should be false (12345 < -67890)
    cout << "a > b: " << (a > b) << endl;         // Should be true (12345 > -67890)
    cout << "c == 0: " << (c == BigInt(0)) << endl << endl; // Should be true (0 == 0)

    // Test 4: Unary operators and increments
    cout << "4. Unary operators and increments:" << endl;
    cout << "-a: " << -a << endl;                 // Should print "-12345"
    cout << "++a: " << ++a << endl;               // Should increment and print "12346"
    cout << "a--: " << a-- << endl;               // Should print "12346" then decrement
    cout << "a after decrement: " << a << endl << endl; // Should print "12345"

    // Test 5: Large number operations
    cout << "5. Large number operations:" << endl;
    BigInt num1("12345678901234567890");
    BigInt num2("98765432109876543210");
    cout << "Very large addition: " << num1 + num2 << endl;
    cout << "Very large multiplication: " << num1 * num2 << endl << endl;

    // Test 6: Edge cases and error handling
    cout << "6. Edge cases:" << endl;
    BigInt zero(0);
    BigInt one(1);
    try {
        BigInt result = one / zero;               // Should throw division by zero error
        cout << "Division by zero succeeded (unexpected)" << endl;
    } catch (const runtime_error& e) {
        cout << "Division by zero correctly threw error: " << e.what() << endl;
    }
    cout << "Multiplication by zero: " << one * zero << endl;        // Should be "0"
    cout << "Negative multiplication: " << BigInt(-5) * BigInt(3) << endl;  // Should be "-15"
    cout << "Negative division: " << BigInt(-10) / BigInt(3) << endl;       // Should be "-3"
    cout << "Negative modulus: " << BigInt(-10) % BigInt(3) << endl;        // Should be "-1"
    */

    return 0;
}
