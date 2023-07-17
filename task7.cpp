#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

template <typename T>
struct Node
{
    T data;
    Node *next;
};

template <typename T>
void showList(const Node<T> *head)
{
    Node<T> *temp = new Node<T>;
    *temp = *head;
    while (temp->next != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "" << endl;
}

template <typename T>
Node<T> *arrayToList(const T a[], size_t size)
{
    Node<T> *head = new Node<T>;
    Node<T> *temp = head;
    for (size_t i = 0; i < size; i++)
    {
        temp->next = new Node<T>;
        temp->data = a[i];
        temp = temp->next;
    }
    temp->next = nullptr;
    return head;
}

template <typename T, typename Pred>
Node<T> *extract(Node<T> *&head, Pred pred)
{
    Node<T> *temp = new Node<T>;
    Node<T> *prev = new Node<T>;
    temp = head;
    prev = temp;

    Node<T> *biHead = new Node<T>;
    Node<T> *newTemp = biHead;

    while (temp->next != nullptr)
    {
        if (!pred(temp->data))
        {
            newTemp->next = new Node<T>;
            newTemp->data = temp->data;
            newTemp = newTemp->next;

            if (temp == head)
                head = temp->next;

            if (prev == head)
            {
                prev->next = prev->next->next;
                head = prev;
            }

            prev->next = temp->next;
        }
        else
        {
            prev = temp;
        }
        temp = temp->next;
    }
    newTemp->next = nullptr;
    return biHead;
}

template <typename T>
void deleteList(Node<T> *&head)
{
    Node<T> *temp = new Node<T>;
    Node<T> *prev = new Node<T>;
    *temp = *head;
    *prev = *head;
    while (temp->next != nullptr)
    {
        cout << "DEL " << temp->data << "; ";
        prev = temp;
        temp = temp->next;
        free(prev);
    }
    cout << "" << endl;
}

bool isLong(const std::string &s) { return s.size() >= 5; }

int main()
{
    int tabi[] = {2, 1, 4, 3, 6, 5, 7, 8};
    size_t sizei = sizeof(tabi) / sizeof(tabi[0]);
    Node<int> *listAi = arrayToList(tabi, sizei);
    showList(listAi);
    Node<int> *listBi = extract(listAi, [](int n)
                                { return n % 2 == 0; });
    showList(listAi);
    showList(listBi);
    deleteList(listAi);
    deleteList(listBi);

    std::string tabs[]{"Kasia", "Ola", "Ala",
                       "Zosia", "Ela", "Basia"};
    size_t sizes = sizeof(tabs) / sizeof(tabs[0]);
    Node<std::string> *listAs = arrayToList(tabs, sizes);
    showList(listAs);
    Node<std::string> *listBs = extract(listAs, isLong);
    showList(listAs);
    showList(listBs);
    deleteList(listAs);
    deleteList(listBs);
}
