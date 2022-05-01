#ifndef LISTITERATOR_H
#define LISTITERATOR_H
#include <assert.h>
#include <memory>
#include "ListNode.h"

template< class T >
class ListIterator : public std::iterator< std::forward_iterator_tag, T >
{
public:
    using Node = ListNode< T >;

    ListIterator() = default;
    ListIterator(std::shared_ptr< Node > pointer) = default;
    ListIterator(const ListIterator< T >&) = default;
    ListIterator< T >& operator=(const ListIterator< T >&) = default;
    bool operator==(const ListIterator< T >&) const;
    bool operator!=(const ListIterator< T >&) const;
    ListIterator< T >& operator++();
    ListIterator< T > operator++(int);

protected:
    std::shared_ptr< Node > m_Current;
};

template< class T >
class ConstIterator : public ListIterator< T >
{
public:
    using Node = ListNode< T >;

    ConstIterator() = default;
    ConstIterator(std::shared_ptr< Node > pointer);
    ConstIterator(const ConstIterator< T >&) = default;
    ConstIterator< T >& operator=(const ConstIterator< T >&) = default;
    const T& operator*() const;
    const std::shared_ptr< T > operator->() const;
};

template< class T >
class Iterator : public ListIterator< T >
{
public:
    using Node = ListNode< T >;

    Iterator();
    Iterator(std::shared_ptr< Node > pointer);
    Iterator(const Iterator< T >&) = default;
    Iterator< T >& operator=(const Iterator< T >&) = default;
    T& operator*() const;
    std::shared_ptr< T > operator->() const;
};

template< class T >
bool ListIterator< T >::operator==(const ListIterator< T >& other) const
{
    return m_Current == other.m_Current;
}

template< class T >
bool ListIterator< T >::operator!=(const ListIterator< T >& other) const
{
    return !(*this == other);
}

template< class T >
T& ListIterator< T >::operator*() const
{
    assert(m_Current != nullptr);
    return m_Current->m_Data;
}

template< class T >
std::shared_ptr< T > ListIterator< T >::operator->() const
{
    assert(m_Current != nullptr);
    return std::make_shared< T >(m_Current->m_Data);
}

template< class T >
ListIterator< T >& ListIterator< T >::operator++()
{
    assert(m_Current != nullptr);
    m_Current = m_Current->m_PointerNext;
    return *this;
}

template< class T >
ListIterator< T > ListIterator< T >::operator++(int)
{
    ListIterator< T > temp(*this);
    operator++();
    return temp;
}
#endif
