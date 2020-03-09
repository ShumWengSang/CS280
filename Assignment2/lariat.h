////////////////////////////////////////////////////////////////////////////////
#ifndef LARIAT_H
#define LARIAT_H
////////////////////////////////////////////////////////////////////////////////

#include <string>     // error strings
#include <utility>    // error strings
#include <cstring>     // memcpy

class LariatException : public std::exception
{
private:
    int m_ErrCode;
    std::string m_Description;

public:
    LariatException(int ErrCode, const std::string &Description) :
            m_ErrCode(ErrCode), m_Description(Description) {}

    virtual int code(void) const
    {
        return m_ErrCode;
    }

    virtual const char *what(void) const throw()
    {
        return m_Description.c_str();
    }

    virtual ~LariatException() throw()
    {
    }

    enum LARIAT_EXCEPTION
    {
        E_NO_MEMORY, E_BAD_INDEX, E_DATA_ERROR
    };
};

// forward declaration for 1-1 operator<< 
template<typename T, int Size>
class Lariat;

using LariatIndex = int;

template<typename T, int Size>
std::ostream &operator<<(std::ostream &os, Lariat<T, Size> const &rhs);

template<typename T, int Size>
class Lariat
{
public:

    Lariat();         // default constructor

    template <typename TYPE>
    Lariat(TYPE const& rhs);    // template copy constructor
    Lariat(Lariat const &rhs);  // copy constructor
    ~Lariat();                  // destructor

    Lariat& operator= (Lariat const &rhs);  // Assignment operator
    template<typename TYPE, int otherSize>
    Lariat& operator= (Lariat<TYPE, otherSize> const& rhs);    // template assignment operator

    // inserts
    void insert(int index, const T &value);

    void push_back(const T &value);

    void push_front(const T &value);

    // deletes
    void erase(int index);

    void pop_back();

    void pop_front();

    //access
    T &operator[](int index);       // for l-values
    const T &operator[](int index) const; // for r-values
    T &first();

    T const &first() const;

    T &last();

    T const &last() const;

    unsigned find(const T &value) const;       // returns index, size (one past last) if not found

    friend std::ostream &operator<<<T, Size>(std::ostream &os, Lariat<T, Size> const &list);

    // and some more
    size_t size(void) const;   // total number of items (not nodes)
    void clear(void);          // make it empty

    void compact();            // push data in front reusing empty positions and delete remaining nodes
private:
    struct LNode
    { // DO NOT modify provided code
        LNode *next = nullptr;
        LNode *prev = nullptr;
        int count = 0;         // number of items currently in the node
        T values[Size];

        void PushBack(const T&);
        T PopBack();
    };
    // DO NOT modify provided code
    LNode *head_ = nullptr;           // points to the first node
    LNode *tail_ = nullptr;           // points to the last node
    int size_ = 0;              // the number of items (not nodes) in the list
    mutable int nodecount_ = 0; // the number of nodes in the list
    int asize_= Size;             // the size of the array within the nodes

private:
    // HELPER FUNCTIONS
    void Split(LNode* lnode, LariatIndex indexPoint = 0);
    std::tuple<LNode*, LariatIndex> findElement(LariatIndex globalIndex) const;
    const T * shiftRight(LNode *node, LariatIndex index);
    const T * shiftLeft(LNode *node, LariatIndex index);

    // Given a node and the index, inserts T at that location.
    // Assumes node size isn't big. Returns the new node if one is created.
    LNode* Insert(LNode* node, LariatIndex index, T const & obj);

    bool isNodeFull(LNode*) const;
    void DestroyNode(LNode*) const;
    LNode* CreateNode() const;

    // Friend
    template <typename TYPE, int OtherSize>
    friend class Lariat;
};

#include "lariat.cpp"

#endif // LARIAT_H
