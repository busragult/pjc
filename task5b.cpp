#include <iostream>

template <typename F, typename S>
class Pair
{
    F fst;
    S scn;

public:
    Pair(F first, S second)
    {
        fst = first;
        scn = second;
    }

    Pair(const Pair<int, int> &otherPair)
    {
        fst = otherPair.first();
        scn = otherPair.second();
    }

    Pair &operator=(const Pair &other)
    {
        if (this != &other)
        {
            fst = other.first();
            scn = other.second();
        }
        return *this;
    }

    F first() const
    {
        return fst;
    }
    S second() const
    {
        return scn;
    }

    template <typename, typename>
    friend std::ostream &operator<<(std::ostream &s, const Pair<F, S> &p);

    bool operator<(Pair<F, S> otherPair) const;
    bool operator<=(Pair<F, S> otherPair) const;
    bool operator>(Pair<F, S> otherPair) const;
    bool operator>=(Pair<F, S> otherPair) const;
    bool operator==(Pair<F, S> otherPair) const;
    bool operator!=(Pair<F, S> otherPair) const;
};

template <typename F, typename S>
bool Pair<F, S>::operator<(Pair<F, S> otherPair) const
{
    if (this->first() < otherPair.first())
        return true;
    if (this->first() == otherPair.first())
        if (this->second() < otherPair.second())
            return true;
    return false;
}

template <typename F, typename S>
bool Pair<F, S>::operator<=(Pair<F, S> otherPair) const
{
    if (this->first() < otherPair.first())
        return true;
    if (this->first() == otherPair.first())
        if (this->second() <= otherPair.second())
            return true;
    return false;
}

template <typename F, typename S>
bool Pair<F, S>::operator>(Pair<F, S> otherPair) const
{
    if (this->first() > otherPair.first())
        return true;
    if (this->first() == otherPair.first())
        if (this->second() > otherPair.second())
            return true;
    return false;
}

template <typename F, typename S>
bool Pair<F, S>::operator>=(Pair<F, S> otherPair) const
{
    if (this->first() >= otherPair.first())
        return true;
    if (this->first() == otherPair.first())
        if (this->second() >= otherPair.second())
            return true;
    return false;
}

template <typename F, typename S>
bool Pair<F, S>::operator==(Pair<F, S> otherPair) const
{
    if (this->first() == otherPair.first() && this->second() == otherPair.second())
        return true;
    return false;
}

template <typename F, typename S>
bool Pair<F, S>::operator!=(Pair<F, S> otherPair) const
{
    if (this->first() != otherPair.first())
        return true;
    if (this->second() != otherPair.second())
        return true;
    return false;
}

template <typename F, typename S>
std::ostream &operator<<(std::ostream &s, const Pair<F, S> &p)
{
    s << "[" << p.first() << ", " << p.second() << "]";
    return s;
}

template <typename PAIR>
void check(const PAIR &lhs, const PAIR &rhs)
{
    using std::cout;
    using std::endl;
    auto flags = cout.flags();
    cout << std::boolalpha;
    cout << "\nLHS=" << lhs << "  RHS=" << rhs << endl;
    cout << "lhs <  rhs: " << (lhs < rhs) << endl;
    cout << "lhs <= rhs: " << (lhs <= rhs) << endl;
    cout << "lhs >  rhs: " << (lhs > rhs) << endl;
    cout << "lhs >= rhs: " << (lhs >= rhs) << endl;
    cout << "lhs == rhs: " << (lhs == rhs) << endl;
    cout << "lhs != rhs: " << (lhs != rhs) << endl;
    cout.flags(flags);
}

int main()
{
    check(Pair<int, int>(3, 3), Pair<int, int>(4, 2));
    check(Pair<int, int>(3, 3), Pair<int, int>(3, 2));
    check(Pair<int, int>(4, 3), Pair<int, int>(4, 3));

    Pair<int, int> pia{3, 4};
    Pair<int, int> pib{4, 5};
    Pair<double, double> pd(pia);
    std::cout << pia << std::endl;
    std::cout << pd << std::endl;
    pd = pib;
    std::cout << pd << std::endl;
}