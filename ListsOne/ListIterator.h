#ifndef LISTITERATOR_H
#define LISTITERATOR_H
#include <assert.h>
#include <memory>
#include "ListNode.h"

template<class T>
class ListIterator : public std::iterator< std::forward_iterator_tag, T >
{
public:
    using Node = ListNode< T >;
    using Iterator = ListIterator< T >;

    ListIterator();
    ListIterator(std::shared_ptr< Node > pointer);
    ListIterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    bool operator==(const Iterator&) const;
    bool operator!=(const Iterator&) const;
    T& operator*() const;
    std::shared_ptr< T > operator->() const;
    Iterator& operator++();
    Iterator operator++(int);

private:
    std::shared_ptr< Node > m_Current;
};

template< class T >
ListIterator< T >::ListIterator() : m_Current(nullptr) {}

template< class T >
ListIterator< T >::ListIterator(std::shared_ptr< Node > pointer) : m_Current(pointer) {}

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
