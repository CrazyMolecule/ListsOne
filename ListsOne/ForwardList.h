#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <stdexcept>
#include <iostream>
#include <memory>
#include "ListNode.h"
#include "ListIterator.h"

namespace bavykin
{
    template< typename T >
    class ForwardList
    {
    public:
        using Node = ListNode< T >;
        using iterator = ListIterator< T >;
        using const_iterator = ListIterator< const T >;

        ForwardList();
        ForwardList(const ForwardList& right);

        ForwardList& operator=(const ForwardList& right);
        T& operator[] (size_t index) const;

        size_t getCount() const; // TO DO: удалить походу...

        void popFront(); // +
        void popBack();
        void removeAt(int index);

        void pushFront(const T& data); // +
        void pushBack(const T& data);
        void insertAfter(const T& data, int index);
        void clear() noexcept; // +

        void sort();
        template< class Compare >
        void sort(Compare comp);

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

    private:
        size_t m_Size; // TO DO: удалить походу...
        std::shared_ptr< Node > m_Head;
    };
    template< typename T >
    using forward_list = ForwardList< T >;

    template< typename T >
    typename ForwardList< T >::iterator ForwardList< T >::begin()
    {
        return iterator(m_Head);
    }

    template< typename T >
    typename ForwardList< T >::iterator ForwardList< T >::end()
    {
        return iterator();
    }

    template< typename T >
    typename ForwardList< T >::const_iterator ForwardList< T >::begin() const
    {
        return const_iterator(m_Head);
    }

    template< typename T >
    typename ForwardList< T >::const_iterator ForwardList< T >::end() const
    {
        return const_iterator();
    }

    template< typename T >
    size_t ForwardList< T >::getCount() const
    {
        return m_Size;
    }

    template< typename T >
    ForwardList< T >::ForwardList() : m_Size(0), m_Head(nullptr) {}

    template< typename T >
    ForwardList< T >::ForwardList(const ForwardList& right) : m_Size(right.m_Size), m_Head(right.m_Head) {}

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

        m_Head = m_Head->m_PointerNext;

        m_Size--;
    }

    template< typename T >
    void ForwardList< T >::popBack()
    {
        if (m_Size == 0)
        {
            throw std::length_error("The element cannot be pulled out.");
        }

        removeAt(m_Size - 1);
    }

    template< typename T >
    void ForwardList< T >::pushFront(const T& data)
    {
        m_Head = std::shared_ptr< Node >(new Node(data, m_Head));
        m_Size++;
    }

    template< typename T >
    void ForwardList< T >::pushBack(const T& data)
    {
        if (m_Head == nullptr)
        {
            m_Head = std::shared_ptr< Node >(new Node(data));
        }
        else
        {
            std::shared_ptr< Node > current = m_Head;

            while (current->m_PointerNext != nullptr)
            {
                current = current->m_PointerNext;
            }

            current->m_PointerNext = std::shared_ptr< Node >(new Node(data));
        }
        m_Size++;
    }

    template< typename T >
    void ForwardList< T >::insertAfter(const T& data, int index)
    {
        if (index == 0)
        {
            pushFront(data);
        }
        else
        {
            std::shared_ptr< Node > previous = m_Head;

            for (size_t i = 0; i < index - 1; i++)
            {
                previous = previous->m_PointerNext;
            }

            previous->m_PointerNext = std::shared_ptr< Node >(new Node(data, previous->m_PointerNext));

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
            std::shared_ptr< Node > previous = m_Head;

            for (size_t i = 0; i < index - 1; i++)
            {
                previous = previous->m_PointerNext;
            }

            std::shared_ptr< Node > toDelete = previous->m_PointerNext;

            previous->m_PointerNext = toDelete->m_PointerNext;

            m_Size--;
        }
    }

    template< typename T >
    void ForwardList< T >::clear() noexcept
    {
        while (m_Size)
        {
            popFront();
        }
    }

    template< typename T >
    void ForwardList< T >::sort()
    {
        for (iterator i = begin(); i != end(); ++i)
        {
            for (iterator j = begin(); j != end(); ++j)
            {
                if (std::less< T >(*j, *(j++)))
                {
                    std::swap(*j, *(j++));
                }
            }
        }
    }

    template< typename T >
    template< class Compare >
    void ForwardList< T >::sort(Compare comp)
    {
        for (iterator i = begin(); i != end(); ++i)
        {
            for (iterator j = begin(); j != end(); ++j)
            {
                if (comp(*j, *(j++)))
                {
                    std::swap(*j, *(j++));
                }
            }
        }
    }

    template< typename T >
    T& ForwardList< T >::operator[](size_t index) const
    {
        if (index < 0 || index >= m_Size)
        {
            throw std::length_error("Specified index is not valid.");
        }

        int counter = 0;
        std::shared_ptr< Node > current = m_Head;

        while (current != nullptr)
        {
            if (counter == index)
            {
                return current->m_Data;
            }
            current = current->m_PointerNext;
            counter++;
        }

        return current->m_Data;
    }
}
#endif
