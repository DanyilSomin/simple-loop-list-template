#include <iostream>
#include <cmath>

template <typename T>
class LoopList
{
public:
    T current()
    {
        return mCurrent->value;
    }

    T next()
    {
        return mCurrent->next->value;
    }
    
    void eraseNext()
    {
        Node *nodeToDelete = mCurrent->next;

        if (mCurrent == nodeToDelete)
        {
            mCurrent = nullptr;
        }
        else
        {
            mCurrent->next = mCurrent->next->next;
        }
        
        delete nodeToDelete;

        --mSize;
    }

    void move()
    {
        if (!mCurrent) return;
        mCurrent = mCurrent->next;
    }

    void insert(const T &value)
    {
        Node *newNode = new Node{ value, nullptr };

        if (mCurrent == nullptr)
        {
            mCurrent = newNode;
            mCurrent->next = mCurrent;
        }
        else
        {
            newNode->next = mCurrent->next;
            mCurrent->next = newNode;
        }

        ++mSize;

        move();
    }

    size_t size()
    {
        return mSize;
    }

private:
    struct Node
    {
        T value;
        Node *next;
    };

    Node* mCurrent = nullptr;

    size_t mSize = 0;
};

size_t lastWarrirorIndex(size_t warriorsAmount) 
{
    return (warriorsAmount - pow(2, floor(log2(warriorsAmount)))) * 2 + 1;
}

size_t lastWarrirorIndexLoopedList(size_t warriorsAmount) 
{
    LoopList<int> list;

    for (size_t i = 1; i <= warriorsAmount; ++i)
    {
        list.insert(i);
    }

    list.move();

    while (list.size() > 1)
    {
        list.eraseNext();
        list.move();
    }

    return list.current();
}

int main()
{
    for (size_t i = 1; i < 100; ++i)
    {
        std::cout << lastWarrirorIndex(i) 
                  << " - " 
                  << lastWarrirorIndexLoopedList(i) 
                  << std::endl;
    }
}
