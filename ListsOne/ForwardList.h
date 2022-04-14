#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <stdexcept>
#include <iostream>
template< typename T >
class ForwardList
{
public:
    ForwardList();

    ForwardList& operator=(const ForwardList& right);
    T& operator[] (const int index);

    int getCount();

    void popFront();
    void popBack();
    void removeAt(int index);

    void pushFront(T data);
    void pushBack(T data);
    void insert(T data, int index);
    void clear();

private:
    template< typename T >
    class Node
    {
    public:
        std::shared_ptr< Node > m_PointerNext;
        T m_Data;

        Node(T data = T(), std::shared_ptr< Node > pNext = nullptr)
        {
            m_PointerNext = pNext;
            m_Data = data;
        }
    };

    int m_Size;
    std::shared_ptr< Node< T > > m_Head;
};
template< typename T >
using forward_list = ForwardList< T >;

template< typename T >
int ForwardList< T >::getCount()
{
    return m_Size;
}

template< typename T >
ForwardList< T >::ForwardList()
{
    m_Size = 0;
    m_Head = nullptr;
}

template< typename T >
ForwardList< T >& ForwardList< T >::operator=(const ForwardList& right)
{
    m_Size = right.m_Size;
    m_Head = right.m_Head;

    return *this;
}

template< typename T >
void ForwardList< T >::popFront()
{
    if (m_Size == 0)
    {
        throw std::length_error("The element cannot be pulled out.");
    }

    std::shared_ptr< Node< T > > temp = m_Head;
    m_Head = m_Head->m_PointerNext;

    m_Size--;
}

template< typename T >
void ForwardList<T>::popBack()
{
    if (m_Size == 0)
    {
        throw std::length_error("The element cannot be pulled out.");
    }

    removeAt(m_Size - 1);
}

template< typename T >
void ForwardList<T>::pushFront(T data)
{
    m_Head = std::shared_ptr< Node< T > >(new Node< T >(data, m_Head));
    m_Size++;
}

template< typename T >
void ForwardList< T >::pushBack(T data)
{
    if (m_Head == nullptr)
    {
        m_Head = std::shared_ptr< Node< T > >(new Node< T >(data));
    }
    else
    {
        std::shared_ptr< Node< T > > current = m_Head;

        while (current->m_PointerNext != nullptr)
        {
            current = current->m_PointerNext;
        }

        current->m_PointerNext = std::shared_ptr< Node< T > >(new Node< T >(data));
    }
    m_Size++;
}

template< typename T >
void ForwardList< T >::insert(T data, int index)
{
    if (index == 0)
    {
        pushFront(data);
    }
    else
    {
        std::shared_ptr< Node< T > > previous = m_Head;

        for (int i = 0; i < index - 1; i++)
        {
            previous = previous->m_PointerNext;
        }

        previous->m_PointerNext = std::shared_ptr< Node< T > >(new Node< T >(data, previous->m_PointerNext));

        m_Size++;
    }
}

template< typename T >
void ForwardList< T >::removeAt(int index)
{
    if (index < 0 || index >= m_Size)
    {
        throw std::length_error("Specified index is not valid.");
    }

    if (index == 0)
    {
        popFront();
    }
    else
    {
        std::shared_ptr< Node< T > > previous = m_Head;

        for (int i = 0; i < index - 1; i++)
        {
            previous = previous->m_PointerNext;
        }

        std::shared_ptr< Node< T > > toDelete = previous->m_PointerNext;

        previous->m_PointerNext = toDelete->m_PointerNext;

        m_Size--;
    }
}

template< typename T >
void ForwardList<T>::clear()
{
    while (m_Size)
    {
        popFront();
    }
}

template< typename T >
T& ForwardList<T>::operator[](const int index)
{
    if (index < 0 || index >= m_Size)
    {
        throw std::length_error("Specified index is not valid.");
    }

    int counter = 0;
    std::shared_ptr< Node< T > > current = m_Head;

    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->m_Data;
        }
        current = current->m_PointerNext;
        counter++;
    }
}
#endif
