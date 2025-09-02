#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

class BigInt // BigInt x(237846)        x.number  = "237846"
{
private:
    string number;   // Stores the number as a string
    bool isNegative; // True if number is negative

    // Remove unnecessary leading zeros from the number string
    void removeLeadingZeros()
    {
        // handling empty string
        if (number.empty())
        {
            number = "0";
            return;
        }

        int firstNonZero = 0;
        // if there is a zero in the beginning
        while (firstNonZero < number.length() && number[firstNonZero] == '0')
        {
            firstNonZero++; // keep moving the pointer
        }

        // if all digits are zero return '0'
        if (firstNonZero == number.length()) // since the pointer = the length then the number was ex : "00000"
        {
            number = "0";
        }
        else
        {
            number = number.substr(firstNonZero); // substr makes a string from the index firstNonZero
        }
    }

    // Compare absolute values of two BigInts (ignore signs)
    // Returns: 1 if |this| > |other|, 0 if equal, -1 if |this| < |other|
    int compareMagnitude(const BigInt &other) const
    {
        if (this->number.length() > other.number.length())
        {
            return 1;
        }
        if (this->number.length() < other.number.length())
        {
            return -1;
        }
        for (int i = 0; i < number.length(); i++)
        {
            if (number[i] > other.number[i])
            {
                return 1;
            }
            if (number[i] < other.number[i])
            {
                return -1;
            }
        }
        return 0;
    }

public:
    // Default constructor - initialize to zero
    BigInt()
    {
        number = "0";
        isNegative = false;
    }

    // Constructor from 64-bit integer
    BigInt(int64_t value) // ex BigInt right (12315) ,
    {
        if (value < 0)
        {
            isNegative = true;
            value = -value;
        }
        else
        {
            isNegative = false;
        }
        number = to_string(value);
    }

    // Constructor from string representation
    BigInt(const string &str)
    {
        if (str.empty())
        {
            number = "0";
            isNegative = false;
            return;
        }
        int first = 0;
        if (str[0] == '-')
        {
            isNegative = true;
            first = 1;
        }
        else if (str[0] == '+')
        {
            isNegative = false;
            first = 1;
        }
        else
        {
            isNegative = false;
        }
        number = str.substr(first);
        removeLeadingZeros();
    }

    // Copy constructor
    BigInt(const BigInt &other)
    {
        number = other.number;
        isNegative = other.isNegative;

        // TODO: Implement this constructor
    }

    // Destructor
    ~BigInt()
    {
        // TODO: Implement if needed
        // no destructor needed
    }

    BigInt &operator=(const BigInt &other) // rana
    {
        if (this != &other)
        {
            this->number = other.number;
            this->isNegative = other.isNegative;
        }
        // TODO: Implement this operator
        return *this;
    }

    // Unary negation operator (-x)
    BigInt operator-() const
    {
        BigInt result;
        result.number = number;

        if (number == "0") // if 0 then don't do anything
        {
            result.isNegative = false;
        }
        else
        {
            result.isNegative = !isNegative; // this means the given BigInt ex - 1234 "1234" is "this"
        }

        return result;
    }

    // Unary plus operator (+x)
    BigInt operator+() const
    {
        // TODO: Implement this operator
        BigInt result;
        result.number = number;
        result.isNegative = isNegative;
        return result;
    }

    // Addition assignment operator (x += y)    x = x + y    *this = x
    BigInt &operator+=(const BigInt &other)
    {
        // TODO: Implement this operator
        BigInt temp = *this;  // this temp is because some compilers you can't do
        *this = temp + other; // *this = *this + other
        return *this;
    }

    // Subtraction assignment operator (x -= y)
    BigInt &operator-=(const BigInt &other)
    {
        // TODO: Implement this operator
        BigInt temp = *this;
        *this = temp - other;
        return *this;
    }

    // Multiplication assignment operator (x *= y)
    BigInt &operator*=(const BigInt &other)
    {
        // TODO: Implement this operator
        BigInt temp = *this;
        *this = temp * other;
        return *this;
    }
    bool getIsNegative() const
    {
        return isNegative;
    }

    void setIsNegative(bool negative) { isNegative = negative; }

    string getNumber() const
    {
        return number;
    }

    // Division assignment operator (x /= y)
    BigInt &operator/=(const BigInt &other)
    {
        // TODO: Implement this operator
        BigInt temp = *this;
        *this = temp / other;
        return *this;
    }

    // Modulus assignment operator (x %= y)
    BigInt &operator%=(const BigInt &other)
    {
        // TODO: Implement this operator
        BigInt temp = *this;
        *this = temp % other;
        return *this;
    }

    // Pre-increment operator (++x)         // x = 5    cout << (x++) + (++x)    5   +   7
    BigInt &operator++()
    {
        *this += BigInt(1); // add 1 to current object
        return *this;       // returns the added object before doing the intended function
    }

    // Post-increment operator (x++)      // cout << x++ // temp = x , cout << temp , x+=1
    BigInt operator++(int)
    {
        BigInt temp = *this; // save this current value
        *this += BigInt(1);  // increment it
        return temp;         // but return the old value to do the needed function
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
        // hint use the isNegative bool to add '-' or not
        if (isNegative && number != "0")
        {
            return "-" + number;
        }
        return number;
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
};

// Binary addition operator (x + y)
BigInt operator+(BigInt lhs, const BigInt &rhs)
{
    // Handle different sign combinations
    if (lhs.isNegative && !rhs.isNegative)
    {
        // (-a) + b = b - a
        lhs.isNegative = false;
        return rhs - lhs;
    }
    if (!lhs.isNegative && rhs.isNegative)
    {
        // a + (-b) = a - b
        BigInt temp = rhs;
        temp.isNegative = false;
        return lhs - temp;
    }

    // Both same sign: add magnitudes and keep the sign
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
    // HANDLING SIGNS
    if (rhs.isNegative && lhs.isNegative) // if both are negative  ex -x - (-y) return y - x
    {
        return rhs - lhs;
    }
    if (rhs.isNegative) // handle case if rhs is negative
    {
        return (lhs + rhs);
    }
    if (lhs.isNegative) // handle case if lhs is negative
    {
        return -(lhs + rhs);
    }

    BigInt Minuend, Subtrahend, result; // if x - y , then x is minuend and y is subtrahend (mathematical names)

    // HANDLING WHICH NUMBER IS BIGGER
    if (lhs > rhs)
    {
        Minuend = lhs; // if x is bigger than y , then do normal x - y
        Subtrahend = rhs;
    }
    else if (lhs < rhs)
    {
        Minuend = rhs; // if y is bigger than x , then do y - x and make isNegative true because -ve number
        Subtrahend = lhs;
        result.isNegative = true;
    }
    else
    {
        return BigInt(0); // if x - x return 0
    }
    //   ---------    X - Y    ---------
    int borrow = 0;
    int i = Minuend.number.length() - 1;    // length of x
    int j = Subtrahend.number.length() - 1; // length of y

    while (i >= 0 && j >= 0)
    {
        int firstDigit = Minuend.number[i] - '0';     // takes the rightmost digit in "x"
        int secondDigit = Subtrahend.number[j] - '0'; // takes the rightmost digit in "y"

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
                firstDigit--; // else just borrow 1 from the digit
                borrow = 0;
            }

            int digit;
            if (firstDigit >= secondDigit)
            {
                digit = firstDigit - secondDigit;
            }
            else
            {
                firstDigit += 10; // ex 116 - 8   taking (6 - 8) 8 is bigger so borrow
                borrow = 1;       // so now 6 is 16 - 8 is 8 and the number 116 becomes 10 (16-8) so 108
                digit = firstDigit - secondDigit;
            }
            result.number = char(digit + '0') + result.number; // put this digit in the left of the string
            i--;
            j--;
        }
    }
    int firstDigit = Minuend.number[i] - '0';
    int secondDigit = Minuend.number[i] - '0';
    // handle the last borrow
    if (borrow && i >= 0)
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
        Minuend.number[i] = char(firstDigit + '0');
    }
    // handle remaining digits from first number
    while (i >= 0)
    {
        char thisChar = Minuend.number[i];
        result.number = thisChar + result.number;
        i--;
    }

    result.removeLeadingZeros(); // remove zeros from the beginning of the number
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
}

// Less-than-or-equal comparison operator (x <= y)
bool operator<=(const BigInt &lhs, const BigInt &rhs)
{
    // TODO: Implement this operator
    return false;
}

// Greater-than comparison operator (x > y)
bool operator>(const BigInt &lhs, const BigInt &rhs)
{
    // TODO: Implement this operator
    return false;
}

// Greater-than-or-equal comparison operator (x >= y)
bool operator>=(const BigInt &lhs, const BigInt &rhs)
{
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
