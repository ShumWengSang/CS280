#include <iostream>
#include <iomanip>
#include <tuple>
#include "lariat.h"


#if 1
template <typename T, int Size>
std::ostream& operator<<( std::ostream &os, Lariat<T, Size> const & list )
{
    typename Lariat<T, Size>::LNode * current  = list.head_;
    int index = 0;
    while ( current ) {
        os << "Node starting (count " << current->count << ")\n";
        for ( int local_index = 0; local_index < current->count; ++local_index ) {
            os << index << " -> " << current->values[local_index] << std::endl;
            ++index;
        }
        os << "-----------\n";
        current = current->next;
    }
    return os;
}

template<typename T, int Size>
void Lariat<T, Size>::insert(int index, const T &value)
{
    // Bad bound check
    if(0 > index || index > this->size_)
    {
        throw LariatException(LariatException::E_BAD_INDEX, "Subscript is out of range");
    }


    if(index == 0)
    {
        this->push_front(value);
    }
    else if(index == this->size_)
    {
        this->push_back(value);
    }
    else
    {
        LariatIndex arrIndex;
        LNode* ptr;
        std::tie(ptr, arrIndex) = findElement(index);
        auto possibleTail = Insert(ptr, arrIndex, value);
        if(ptr == tail_ && possibleTail)
            tail_ = possibleTail;
        size_++;
    }
}

template<typename T, int Size>
void Lariat<T, Size>::Split(Lariat::LNode *lnode, LariatIndex indexPoint)
{
    // You may only split full sized nodes!
    if(lnode->count != this->asize_)
        throw std::exception();

    LNode* newNode = CreateNode();
    std::swap(newNode->next, lnode->next);
    lnode->next = newNode;
    newNode->prev = lnode;

    if(newNode->next != nullptr)
        newNode->next->prev = newNode;

    int arrSize = asize_ + 1;
    int startPoint = arrSize - (arrSize / 2);

    (void)indexPoint;
    // If element is in second node, account for that.
//    if(indexPoint <= startPoint + 1)
//        startPoint += 1;


    for(int i = startPoint; i < asize_; ++i)
        newNode->PushBack(lnode->values[i]);
    lnode->count = startPoint;

}

template<typename T, int Size>
std::tuple<typename Lariat<T,Size>::LNode*, LariatIndex> Lariat<T, Size>::findElement(LariatIndex globalIndex) const
{
    LNode* node = this->head_;
    int Count = 0;
    for(  /* Empty */; (Count + node->count) <= globalIndex && node != this->tail_;
        Count += node->count, node = node->next)
    {

    }
    int remainder = globalIndex - Count;
    if(remainder >= 0)
        return std::make_tuple(node, static_cast<LariatIndex>(remainder));
    else
        return std::tuple<Lariat::LNode *, LariatIndex>(nullptr, -1);
}

template<typename T, int Size>
const T * Lariat<T, Size>::shiftRight(Lariat::LNode *node, LariatIndex index)
{
    if(index >= this->asize_)
        return nullptr;
    for(int i = index; i < this->asize_; ++i)
    {
        using std::swap;
        swap(node->values[index], node->values[i]);
    }
    // Overflow
    return &node->values[index];
}

template<typename T, int Size>
const T * Lariat<T, Size>::shiftLeft(Lariat::LNode *node, LariatIndex index)
{
    if(index < 0)
        return nullptr;
    for(int i = index; i < node->count - 1; ++i)
    {
        using std::swap;
        swap(node->values[i], node->values[i + 1]);
    }
    // Overflow
    return &node->values[index];
}

template<typename T, int Size>
Lariat<T, Size>::Lariat()
{
}

template<typename T, int Size>
typename Lariat<T, Size>::LNode* Lariat<T, Size>::Insert(Lariat::LNode *node, LariatIndex index, const T &obj)
{
    if(index < 0 || index > this->asize_)
        throw std::exception();

    if(isNodeFull(node))
    {
        T copyOverflow;
        const T* overflow = this->shiftRight(node, index);
        if(overflow)
            copyOverflow = *overflow;

        node->values[index] = obj;

        Split(node, index);

        if(overflow)
        {
            LNode* nextNode = node->next;
            nextNode->PushBack(copyOverflow);

        }

        return node->next;
    }
    else
    {
        this->shiftRight(node, index);
        node->values[index] = obj;
        node->count++;

        return nullptr;
    }

}

template<typename T, int Size>
void Lariat<T, Size>::push_back(const T &value)
{
    if(tail_ == nullptr)
    {
        push_front(value);
        return;
    }
    size_++;
    if(isNodeFull(tail_))
    {
        this->Split(tail_, tail_->count);
        tail_ = tail_->next;
        tail_->PushBack(value);

    }
    else
    {
        Insert(tail_, tail_->count, value);
    }

}

template<typename T, int Size>
void Lariat<T, Size>::push_front(const T &value)
{
    if(head_ == nullptr)
    {
        head_ = CreateNode();
        tail_ = head_;
    }

    Insert(head_, 0, value);

    // Set tail
    while(tail_->next != nullptr)
        tail_ = tail_->next;

    size_++;

}

template<typename T, int Size>
bool Lariat<T, Size>::isNodeFull(LNode* node) const
{
    return node->count == asize_;
}

template<typename T, int Size>
typename Lariat<T, Size>::LNode *Lariat<T, Size>::CreateNode() const
{
    nodecount_++;
    return new LNode();
}

template<typename T, int Size>
size_t Lariat<T, Size>::size(void) const
{
    return this->size_;
}

template<typename T, int Size>
void Lariat<T, Size>::clear(void)
{
    LNode* tmp = head_;
    while(tmp != nullptr)
    {
        LNode* nextNode = tmp->next;
        delete tmp;
        tmp = nextNode;
    }
    this->size_ = 0;
    this->nodecount_ = 0;
    this->head_ = nullptr;
    this->tail_ = nullptr;
}

template<typename T, int Size>
Lariat<T, Size>::~Lariat()
{
    this->clear();
}

template<typename T, int Size>
template<typename TYPE>
Lariat<T, Size>::Lariat(const TYPE &rhs)
{
    for(int i = 0; i < rhs.size_; i++)
    {
        this->push_back(static_cast<T>(rhs[i]));
    }
}

template<typename T, int Size>
Lariat<T, Size>::Lariat(Lariat const &rhs)
{
    if(rhs.head_ == this->head_)
        return;
    for(int i = 0; i < static_cast<int>(rhs.size_); i++)
    {
        this->push_back(static_cast<T>(rhs[i]));
    }
}

template<typename T, int Size>
Lariat<T, Size> &Lariat<T, Size>::operator=(Lariat const &rhs)
{
    if(rhs.head_ == this->head_)
        return *this;
    this->clear();
    for(int i = 0; i < static_cast<int>(rhs.size()); i++)
    {
        this->push_back(static_cast<T>(rhs[i]));
    }
    return *this;
}

template<typename T, int Size>
template<typename TYPE, int otherSize>
Lariat<T, Size> &Lariat<T, Size>::operator=(const Lariat<TYPE, otherSize> &rhs)
{
    this->clear();
    for(int i = 0; i < static_cast<int>(rhs.size()); i++)
    {
        this->push_back(static_cast<T>(rhs[i]));
    }
    return *this;
}

template<typename T, int Size>
void Lariat<T, Size>::erase(int index)
{
    if(index == 0)
    {
        this->pop_front();
    }
    else if(index == this->size_ - 1)
    {
        this->pop_back();
    }
    else
    {
        LariatIndex arrIndex;
        LNode* ptr;
        std::tie(ptr, arrIndex) = findElement(index);
        this->shiftLeft(ptr, arrIndex);
        ptr->count--;
        this->size_--;

        if(ptr->count == 0)
        {
            DestroyNode(ptr);
        }
    }
}

template<typename T, int Size>
void Lariat<T, Size>::DestroyNode(Lariat::LNode * node) const
{
    this->nodecount_--;
    if(node->prev != nullptr)
        node->prev->next = node->next;
    if(node->next != nullptr)
        node->next->prev = node->prev;
    delete node;
}

template<typename T, int Size>
void Lariat<T, Size>::pop_back()
{
    if(tail_ == nullptr)
        return;
    this->size_--;
    tail_->count--;
    if (tail_->count <= 0)
    {
        if(nodecount_ > 1)
        {
            tail_ = tail_->prev;
            DestroyNode(tail_->next);
        }
        else
        {
            DestroyNode(tail_);
            head_ = nullptr;
            tail_ = nullptr;
        }
    }
}

template<typename T, int Size>
void Lariat<T, Size>::pop_front()
{
    if(head_ == nullptr)
        return;
    this->shiftLeft(head_, 0);
    this->size_--;
    head_->count--;
    if (head_->count <= 0)
    {
        if(nodecount_ > 1)
        {
            head_ = head_->next;
            DestroyNode(head_->prev);
        }
        else
        {
            DestroyNode(head_);
            head_ = nullptr;
            tail_ = nullptr;
        }
    }
}

template<typename T, int Size>
T &Lariat<T, Size>::operator[](int index)
{
    if(!head_)
        throw LariatException(LariatException::E_BAD_INDEX, "Subscript is out of range");;
    LariatIndex arrIndex;
    LNode* ptr;
    std::tie(ptr, arrIndex) = findElement(index);

    return ptr->values[arrIndex];
}

template<typename T, int Size>
const T &Lariat<T, Size>::operator[](int index) const
{
    if(!head_)
        throw LariatException(LariatException::E_BAD_INDEX, "Subscript is out of range");
    LariatIndex arrIndex;
    LNode* ptr;
    std::tie(ptr, arrIndex) = findElement(index);

    return ptr->values[arrIndex];
}

template<typename T, int Size>
T &Lariat<T, Size>::first()
{
    if(head_ == nullptr)
        throw std::exception();
    return &head_->values[0];
}

template<typename T, int Size>
T const &Lariat<T, Size>::first() const
{
    if(head_ == nullptr)
        throw std::exception();
    return &head_->values[0];
}

template<typename T, int Size>
T &Lariat<T, Size>::last()
{
    if(tail_ == nullptr)
        throw std::exception();
    return &tail_->values[tail_->count - 1];
}

template<typename T, int Size>
T const &Lariat<T, Size>::last() const
{
    if(tail_ == nullptr)
        throw std::exception();
    return &tail_->values[tail_->count - 1];
}

template<typename T, int Size>
unsigned Lariat<T, Size>::find(const T &value) const
{
    unsigned index = 0;
    LNode* node;
    for(node = head_;  node != nullptr; node = node->next)
    {
        for(int i = 0; i < node->count; ++i, ++index)
        {
            if(value == node->values[i])
            {
                return index;
            }
        }
    }
    return index;
}

template<typename T, int Size>
void Lariat<T, Size>::compact()
{
    LNode* leftFoot = head_, * rightFoot = head_;
    int rtot = 0;

    if(!leftFoot)
        return;
    while(true)
    {
        rightFoot = rightFoot->next;
        if(rightFoot == nullptr)
            break;
        rtot = rightFoot->count;
        rightFoot->count = 0;
        if(isNodeFull(leftFoot))
        {
            leftFoot = leftFoot->next;
        }

        for(int i = 0; i < rtot; i++)
        {
            leftFoot->PushBack(rightFoot->values[i]);
            if(isNodeFull(leftFoot))
            {
                leftFoot = leftFoot->next;
            }
        }
    }

    // Remove extra nodes
    LNode* runner = head_;
    while(runner != nullptr)
    {
        if(runner->count == 0)
        {
            LNode* temp = runner->next;
            DestroyNode(runner);
            runner = temp;
        }
        else
        {
            runner = runner->next;
        }
    }

    // update tail
    tail_ = head_;
    while(tail_->next != nullptr)
    {
        tail_ = tail_->next;
    }

}

template<typename T, int Size>
void Lariat<T, Size>::LNode::PushBack(const T &obj)
{
    if(count + 1 > Size)
        throw std::exception();
    values[count++] = obj;
}

template<typename T, int Size>
T Lariat<T, Size>::LNode::PopBack()
{
    if(count == 0)
        throw std::exception();
    return values[--count];
}


#else // fancier
#endif