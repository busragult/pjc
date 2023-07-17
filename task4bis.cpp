#include <iostream>
#include <stdexcept>   // out_of_range
#include <type_traits> // is_trivially_copyable
#include <cstring>     // memcpy, memmove
using namespace std;

template <typename T>
class MyVector
{
    size_t size = 0;
    size_t cap = 2;
    T *arr;

public:
    bool copyable()
    {
        return std::is_trivially_copyable<T>::value;
    }
    MyVector();

    MyVector(const MyVector &other);

    MyVector &operator=(const MyVector &other)
    {
        if (this != &other)
        {
            delete[] arr;

            size = other.getSize();
            cap = other.getCap();
            arr = new T[other.getCap()];
            std::memcpy(arr, other.getArr + 0, sizeof(T) * cap);
        }
        return *this;
    }

    MyVector(MyVector &&other);

    MyVector &operator=(MyVector &&other)
    {

        if (this != &other)
        {
            delete[] arr;

            arr = other.getArr();
            cap = other.getCap();
            size = other.getSize();

            other.setCap();
            other.setSize();
            other.setArr();
        }
        return *this;
    }

    template <typename>
    friend std::ostream &operator<<(ostream &s, const MyVector<T> &v);
    T operator[](size_t i) const;
    T &operator[](size_t i);
    void insert(size_t ind, const T e[], size_t sz);
    void insert(size_t ind, const T &e);
    void append(const T &e);
    void append(const T e[], size_t sz);
    size_t remove(const T &e, size_t from = 0);
    bool removeAll(const T &e, size_t from = 0);
    ~MyVector();

    size_t getSize() const
    {
        return this->size;
    }
    size_t getCap() const
    {
        return this->cap;
    }
    T *getArr() const
    {
        return this->arr;
    }
    void setSize()
    {
        size = 0;
    }
    void setCap()
    {
        cap = 2;
    }
    void setArr()
    {
        arr == nullptr;
    }
};

template <typename T>
MyVector<T>::MyVector()
{
    cap = 2;
    size = 0;
    arr = new T[cap];
}

template <typename T>
MyVector<T>::MyVector(const MyVector &other)
        : cap(other.getCap()), size(other.getSize()), arr(new T[other.getCap()])
{
    std::memcpy(arr, other.getArr + 0, sizeof(T) * cap);
}

template <typename T>
MyVector<T>::MyVector(MyVector &&other)
        : arr(nullptr), size(0), cap(2)
{
    arr = other.getArr();
    cap = other.getCap();
    size = other.getSize();

    other.setCap();
    other.setSize();
    other.setArr();
}

template <typename T>
void MyVector<T>::insert(size_t ind, const T e[], size_t sz)
{
    if (ind > size)
    {
        throw std::out_of_range("ind is greater or equal than size");
    }
    else if ((sz + size) > cap)
    {
        T *newArr;
        newArr = new T[2 * (size + sz)];

        if (copyable())
        {
            std::memcpy(newArr, arr + 0, sizeof(T) * ind);
            std::memcpy(newArr + ind, e + 0, sizeof(T) * sz);
            std::memcpy(newArr + ind + sz, arr + ind, sizeof(T) * (size - sz));
        }
        else
        {
            for (size_t i = 0; i < ind; i++)
            {
                newArr[i] = arr[i];
            }
            size_t j = 0;
            for (size_t i = ind; i < ind + sz; i++)
            {
                newArr[i] = e[j];

                j++;
            }
            j = ind;
            for (size_t i = ind + sz; i < cap; i++)
            {
                newArr[i] = arr[j];
                j++;
            }
        }
        cap = 2 * (size + sz);
        size += sz;
        free(arr);
        arr = newArr;
    }
    else
    {
        if (copyable())
        {
            std::memmove(arr + ind + sz, arr + ind, sizeof(T) * sz + 1);
            std::memcpy(arr + ind, e + 0, sizeof(T) * sz);
        }
        else
        {
            for (size_t i = size; i > ind; i--)
            {
                arr[i + sz] = arr[i];
            }
            size_t j = 0;
            for (size_t i = ind; i < ind + sz; i++)
            {
                arr[i] = e[j];
                j++;
            }
       }

        size += sz;
    }
}

template <typename T>
void MyVector<T>::insert(size_t ind, const T &e)
{
    if (ind >= size)
    {
        throw std::out_of_range("ind is greater or equal than size");
    }
    else if ((1 + size) > cap)
    {
        T *newArr;
        newArr = new T[2 * (size + 1)];

        if (copyable())
        {
            std::memcpy(newArr, arr + 0, sizeof(T) * ind);
            newArr[ind] = e;
            std::memcpy(newArr + ind + 1, arr + ind, sizeof(T) * (size - 1));
        }
        else
        {
            for (size_t i = 0; i < ind; i++)
            {
                newArr[i] = arr[i];
            }
            newArr[ind] = e;
            for (size_t i = ind + 1; i < cap; i++)
            {
                newArr[i] = arr[i - 1];
            }
        }
        cap = 2 * (size + 1);
        size++;
        free(arr);
        arr = newArr;
    }
    else
    {
        if (copyable())
        {
            std::memmove(arr + ind + 1, arr + ind, sizeof(T) * 1 + 1);
            arr[ind] = e;
        }
        else
        {
            for (size_t i = size; i > ind; i--)
            {
                arr[i + 1] = arr[i];
            }
            arr[ind] = e;
        }
        size++;
    }
}

template <typename T>
void MyVector<T>::append(const T &e)
{
    if (size < cap)
    {
        arr[size] = e;
    }
    else
    {
        T *newArr;
        newArr = new T[2 * (size + 1)];
        if (copyable())
        {
            std::memcpy(newArr, arr + 0, sizeof(T) * cap);
        }
        else
        {
            for (size_t i = 0; i < cap; i++)
            {
                newArr[i] = arr[i];
            }
        }
        newArr[size] = e;
        cap = 2 * (size + 1);
        arr = newArr;
    }
    size++;
}

template <typename T>
void MyVector<T>::append(const T e[], size_t sz)
{
    if ((sz + size) > cap)
    {
        T *newArr;
        newArr = new T[2 * (size + sz)];
        if (copyable())
        {
            std::memcpy(newArr, arr + 0, sizeof(T) * cap);
            std::memcpy(newArr + size, e + 0, sizeof(T) * sz);
        }
        else
        {
            for (size_t i = 0; i < size; i++)
            {
                newArr[i] = arr[i];
            }
            size_t j = 0;
            for (size_t i = size; i < size + sz; i++)
            {
                newArr[i] = e[j];
                j++;
            }
        }
        cap = 2 * (size + sz);
        size += sz;
        free(arr);
        arr = newArr;
    }
    else
    {
        if (copyable())
        {
            std::memcpy(arr + size, e + 0, sizeof(T) * sz);
        }
        else
        {
            size_t j = 0;
            for (size_t i = size; i < size + sz; i++)
            {
                arr[i] = e[j];
                j++;
            }
        }

        size += sz;
    }
}

template <typename T>
size_t MyVector<T>::remove(const T &e, size_t from)
{
    if (from >= size)
    {
        throw std::out_of_range("from is greater or equal size");
    }
    else
    {
        for (size_t i = from; i < size; i++)
        {
            if (arr[i] == e)
            {
                if (copyable())
                {
                    std::memmove(arr + i, arr + i + 1, sizeof(T) * size);
                }
                else
                {
                    for (size_t j = i; j < size; j++)
                    {
                        arr[j] = arr[j + 1];
                    }
                }
                size--;
                return i;
            }
        }
    }
}

template <typename T>
bool MyVector<T>::removeAll(const T &e, size_t from)
{

    bool res = false;
    if (from >= size)
    {
        throw std::out_of_range("from is greater or equal size");
    }
    else
    {
        for (size_t i = from; i < size; i++)
        {
            if (arr[i] == e)
            {

                if (copyable())
                {
                    std::memmove(arr + i, arr + i + 1, sizeof(T) * size);
                }
                else
                {
                    for (size_t j = i; j < size; j++)
                    {
                        arr[j] = arr[j + 1];
                    }
                }
                res = true;
                i--;
                size--;
            }
        }
    }
    return res;
}

template <typename T>
T MyVector<T>::operator[](size_t i) const
{
    if (i >= size)
    {
        throw std::out_of_range("from is greater or equal size");
    }
    else
    {
        return arr[i];
    }
}

template <typename T>
T &MyVector<T>::operator[](size_t i)
{
    if (i >= size)
    {
        throw std::out_of_range("from is greater or equal size");
    }
    else
    {
        return *arr[i];
    }
}

template <typename T>
MyVector<T>::~MyVector()
{
    delete[] arr;
}

template <typename T>
std::ostream &operator<<(std::ostream &s, const MyVector<T> &v)
{
    s << "(" << v.getSize() << "/" << v.getCap() << ") ";
    if (v.getSize() == 0)
    {
        return s;
    }
    T *arr;
    arr = new T[v.getCap()];
    arr = v.getArr();
    s << "[ ";
    for (std::size_t i = 0; i < v.getSize(); i++)
    {
        if (i < v.getSize() - 1)
            s << arr[i] << ", ";
    }
    s << arr[v.getSize() - 1] << " ]";
    return s;
}

int main()
{
    int a[]{1, 2};
    MyVector<int> vi;

    std::cout << "*0*  " << vi << std::endl;

    vi.insert(0, a, 2);
    std::cout << "*1*  " << vi << std::endl;

    vi.insert(2, a, 2);
    std::cout << "*2*  " << vi << std::endl;

    vi.insert(2, &a[1], 1);
    std::cout << "*3*  " << vi << std::endl;

    vi.append(a, 2);
    vi.append(3);
    vi.append(4);
    std::cout << "*4* " << vi << std::endl;

    vi.removeAll(2);
    std::cout << "*5* " << vi << std::endl;

    size_t res = vi.remove(1);
    std::cout << "*6* " << vi << " "
              << "res=" << res << std::endl;

    res = vi.remove(4);
    std::cout << "*7* " << vi << " "
              << "res=" << res << std::endl;
}
