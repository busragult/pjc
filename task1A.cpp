#include <iostream>
#include <utility> // swap (may be useful)
#include <string>
using std::cout;
using std::endl;
using std::string;

template <typename T>
class DLL
{

    struct Node
    {
        T data;
        Node *next;
        Node *prev;
    };
    Node *sent; // sentinel
public:
    DLL() : sent(new Node{ T(), NULL, NULL})
    {
        sent->next = sent->prev = sent;
    }

    bool empty() const
    {
        if (sent->data == "")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void push_front(const T &t)
    {
        Node *temp = sent;

        if (this->empty())
        {
            temp->data = t;
            temp->next = NULL;
            temp->prev = NULL;
        }
        else
        {
            Node *front = new Node;
            front->data = t;
            front->next = temp;
            temp->prev = new Node;
            temp->prev = front;
            front->prev = NULL;
            sent = front;
        }
    }
    void push_back(const T &t) const
    {
        Node *temp = sent;
        Node *previous_temp = sent;
        if (this->empty())
        {
            temp->data = t;
            temp->next = NULL;
            temp->prev = NULL;
        }
        else
        {
            while (temp->next != NULL)
            {
                previous_temp = temp;
                temp = temp->next;
            }
            temp->next = new Node;
            temp->next->data = t;
            temp->next->next = NULL;
            temp->next->prev = previous_temp;
        }
    }
    void print_fwd(std::ostream &str = std::cout) const
    {
        Node *temp = sent;
        if (!this->empty())
        {
            while (temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << "" << endl;
        }
        else
        {
            cout << "The list is empty." << endl;
        }
    }
    void print_rev(std::ostream &str = std::cout) const
    {
        Node *temp = sent;
        if (!this->empty())
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            while (temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->prev;
            }
            cout << "" << endl;
        }
        else
        {
            cout << "The list is empty." << endl;
        }
    }
    Node *find_first(const T &e) const
    {
        Node *temp = sent;
        if (!this->empty())
        {
            while (temp != NULL)
            {
                if (temp->data == e)
                {
                    return temp;
                }
                temp = temp->next;
            }
        }
        else
        {
            cout << "The list is empty." << endl;
        }
    }
    Node *find_last(const T &e) const
    {
        Node *temp = sent;
        if (!this->empty())
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            while (temp != NULL)
            {
                if (temp->data == e)
                {
                    return temp;
                }
                temp = temp->prev;
            }
        }
        else
        {
            cout << "The list is empty." << endl;
        }
    }
    void insert_after(Node *a, const T &t) const
    {
        Node *newAfter = new Node;
        newAfter->data = t;
        newAfter->next = NULL;
        newAfter->prev = new Node;

        if (a->next == NULL)
        {
            a->next = new Node;
            a->next = newAfter;
            newAfter->prev = a;
        }
        else
        {
            newAfter->prev = a;
            newAfter->next = new Node;
            newAfter->next = a->next;
            a->next = newAfter;
        }
    }
    void insert_before(Node *b, const T &t)
    {
        Node *newBefore = new Node;
        newBefore->data = t;
        newBefore->next = new Node;
        newBefore->prev = NULL;
        if (b->prev == NULL)
        {
            b->prev = new Node;
            b->prev = newBefore;
            newBefore->next = b;
            sent = newBefore;
        }
        else
        {
            newBefore->next = b;
            newBefore->prev = new Node;
            newBefore->prev = b->prev;
            b->prev->next = newBefore;
            b->prev = newBefore;
        }
    }
    void delete_node(const Node *d) const
    {
        cout << "del:" << d->data << " ";
        d->prev->next = d->next;
        d->next->prev = d->prev;
    }
    void reverse()
    {
        Node *left = sent;
        Node *right = sent;

        while (right->next != NULL)
        {
            right = right->next;
        }

        while (left != right && left->prev != right)
        {
            swap(left->data, right->data);

            left = left->next;

            right = right->prev;
        }
    }
    void clear()
    {
        Node *temp = sent;

        while (temp != NULL)
        {
            cout << "DEL:" << temp->data << " ";
            temp = temp->next;
            if (temp != NULL)
            {
                free(temp->prev);
            }
        }
        cout << endl;
        sent = new Node;
    }
    ~DLL()
    {
        this->clear();
    }
};

int main()
{

    DLL<std::string> *listStr = new DLL<std::string>();
    listStr->push_back("X");
    listStr->push_back("E");
    listStr->push_front("C");
    listStr->push_front("X");
    listStr->push_front("A");
    cout << "List printed in both directions:" << endl;
    listStr->print_fwd();
    listStr->print_rev();

    listStr->delete_node(listStr->find_first("X"));
    listStr->delete_node(listStr->find_last("X"));
    cout << "\nList after deleting X's:" << endl;
    listStr->print_fwd();

    listStr->insert_after(listStr->find_first("A"), "B");
    listStr->insert_before(listStr->find_last("E"), "D");
    cout << "List after inserting B and D:" << endl;
    listStr->print_fwd();

    listStr->reverse();
    cout << "List after reversing:" << endl;
    listStr->print_fwd();

    std::cout << "Is list empty? " << std::boolalpha << listStr->empty() << std::endl;
    std::cout << "Clearing the listt" << std::endl;
    listStr->clear();

    std::cout << "Adding one element (Z)" << std::endl;
    listStr->push_front("Z");

    std::cout << "Deleting the list" << std::endl;
    delete listStr;
}