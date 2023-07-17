#include <iostream>
#include <string>
using namespace std;

class Frac
{
private:
    int numerator;
    int denominator;

    void simplify()
    {
        int gcd = this->greatestCommonDivisor(numerator, denominator);

        numerator /= gcd;
        denominator /= gcd;

        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    int greatestCommonDivisor(int a, int b) const
    {
        while (true)
        {
            if (a == 0)
            {
                return b;
            }

            b %= a;

            if (b == 0)
            {
                return a;
            }

            a %= b;
        }
    }

public:
    Frac()
    {
        numerator = 0;
        denominator = 1;
    }

    Frac(int num, int den)
    {
        numerator = num;

        if (den == 0)
        {
            cout << "Denominator cannot be 0!" << endl;
            return;
        }

        if (numerator == 0)
        {
            denominator = 1;
        }
        else
        {
            denominator = den;
        }
        this->simplify();
    }

    Frac(int num)
    {
        numerator = num;
        denominator = 1;
    }

    Frac operator+(Frac otherFrac) const
    {
        Frac a((numerator * otherFrac.denominator) + (denominator * otherFrac.numerator), denominator * otherFrac.denominator);

        a.simplify();
        return a;
    }

    Frac operator-(Frac otherFrac) const
    {
        Frac a((numerator * otherFrac.denominator) - (denominator * otherFrac.numerator), denominator * otherFrac.denominator);

        a.simplify();
        return a;
    }

    Frac operator*(Frac otherFrac) const
    {
        Frac a(numerator * otherFrac.numerator, denominator * otherFrac.denominator);

        a.simplify();
        return a;
    }

    Frac operator/(Frac otherFrac) const
    {
        Frac a(numerator * otherFrac.denominator, denominator * otherFrac.numerator);

        a.simplify();
        return a;
    }

    friend ostream &operator<<(ostream &s, const Frac &f);
    friend Frac operator*(int num, const Frac &f);
    friend Frac operator+(int num, const Frac &f);
    friend Frac operator-(int num, const Frac &f);
    friend Frac operator/(int num, const Frac &f);
};

Frac operator*(int num, const Frac &f)
{
    Frac a(f.numerator * num, f.denominator);

    a.simplify();
    return a;
}

Frac operator+(int num, const Frac &f)
{
    Frac a(f.numerator + (f.denominator * num), f.denominator);

    a.simplify();
    return a;
}

Frac operator-(int num, const Frac &f)
{
    Frac a(f.numerator - (f.denominator * num), f.denominator);

    a.simplify();
    return a;
}

Frac operator/(int num, const Frac &f)
{
    Frac a(f.numerator, f.denominator * num);

    a.simplify();
    return a;
}

ostream &operator<<(ostream &s, const Frac &f)
{
    if (f.denominator != 1)
        s << f.numerator << '/' << f.denominator;
    else
        s << f.numerator;
    return s;
}

int main()
{
    Frac a(2), b(4, 10), c(24, -15), x(1, -3), y(2, 6);

    std::cout << -2 * ((a + b) * 5 - 4) / c << " " << (7 + x + y * 1114 / 111) << std::endl;
}
