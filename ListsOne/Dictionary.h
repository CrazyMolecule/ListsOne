#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <utility>
#include <stdexcept>
#include "ForwardList.h"

namespace bavykin
{
    template< typename K, typename V, typename Cmp = std::less< K > >
    class Dictionary
    {
    public:
        Dictionary(const std::string& name = "dictionary");
        Dictionary(const Dictionary& right);

        Dictionary& operator=(const Dictionary& right);
        V operator[](K key) const;
        friend std::ostream& operator<<(std::ostream& out, Dictionary< K, V, Cmp >& value)
        {
            if (value.size() == 0)
            {
                out << "<EMPTY>";
                return out;
            }

            out << value.m_Name << " ";
            for (size_t i = 0; i < value.size(); i++)
            {
                out << value.m_Data[i].first << " " << value.m_Data[i].second;
                if (i != value.size() - 1)
                {
                    out << " ";
                }
            }

            return out;
        }

        size_t size() const;
        void tryEmplace(K key, V value);
        std::pair< K, V >& findPair(const K& key) const;
        bool contains(const K& key) const;
        std::pair< K, V > find(K key) const;
        void extract(K key);

        void changeName(std::string name);

        Dictionary getUnion(const Dictionary& right) const;
        Dictionary getIntersect(const Dictionary& right) const;
        Dictionary getComplement(const Dictionary& right) const;

        using iterator = typename forward_list< std::pair< K, V > >::iterator;
        using const_iterator = typename forward_list< std::pair< K, V > >::const_iterator;
        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;

    private:
        forward_list< std::pair< K, V > > m_Data;
        std::string m_Name;

        void sort();
    };
    template< typename K, typename V, typename Cmp = std::less< K > >
    using dictionary = Dictionary< K, V, Cmp >;

    template< typename K, typename V, typename Cmp >
    Dictionary< K, V, Cmp >::Dictionary(const std::string& name)
    {
        m_Data = forward_list< std::pair< K, V > >();
        m_Name = name;
    }

    template< typename K, typename V, typename Cmp >
    Dictionary< K, V, Cmp >::Dictionary(const Dictionary& right)
    {
        m_Data = right.m_Data;
        m_Name = right.m_Name;
    }

    template< typename K, typename V, typename Cmp >
    void Dictionary< K, V, Cmp >::changeName(std::string name)
    {
        m_Name = name;
    }

    template< typename K, typename V, typename Cmp >
    size_t Dictionary< K, V, Cmp >::size() const
    {
        return m_Data.getCount();
    }

    template< typename K, typename V, typename Cmp >
    void Dictionary< K, V, Cmp >::tryEmplace(K key, V value)
    {
        if (contains(key))
        {
            extract(key);
        }
        m_Data.pushFront(std::pair< K, V >(key, value));

        sort();
    }

    template< typename K, typename V, typename Cmp >
    std::pair< K, V > Dictionary< K, V, Cmp >::find(K key) const
    {
        return findPair(key);
    }

    template< typename K, typename V, typename Cmp >
    bool Dictionary< K, V, Cmp >::contains(const K& key) const
    {
        try
        {
            findPair(key);
            return true;
        }
        catch (const std::runtime_error&)
        {
            return false;
        }
    }

    template< typename K, typename V, typename Cmp >
    void Dictionary< K, V, Cmp >::sort()
    {
        forward_list< std::pair< K, V > > tempData = m_Data;

        for (int i = 0; i < m_Data.getCount() - 1; i++)
        {
            for (int j = 0; j < m_Data.getCount() - i - 1; j++)
            {
                if (Cmp{}(tempData[j].first, tempData[j + 1].first))
                {
                    std::swap(tempData[j], tempData[j + 1]);
                }
            }
        }

        m_Data = tempData;
    }

    template< typename K, typename V, typename Cmp >
    std::pair< K, V >& Dictionary< K, V, Cmp >::findPair(const K& key) const
    {
        for (std::pair< K, V > element : m_Data)
        {
            if (element.first == key)
            {
                return element;
            }
        }

        throw std::runtime_error("Trying to find value from dictionary by key, which is not present.");
    }

    template< typename K, typename V, typename Cmp >
    void Dictionary< K, V, Cmp >::extract(K key)
    {
        bool keyWasFound = false;
        for (size_t i = 0; i < m_Data.getCount(); i++)
        {
            if (m_Data[i].first == key)
            {
                keyWasFound = true;
                m_Data.removeAt(i);
            }
        }

        if (!keyWasFound)
        {
            throw std::runtime_error("Trying to find value from dictionary by key, which is not present.");
        }
    }

    template< typename K, typename V, typename Cmp >
    Dictionary< K, V, Cmp > Dictionary< K, V, Cmp >::getUnion(const Dictionary& right) const
    {
        Dictionary newDict(right);

        for (size_t i = 0; i < size(); i++)
        {
            newDict.tryEmplace(m_Data[i].first, m_Data[i].second);
        }

        newDict.m_Name = m_Name;

        return newDict;
    }

    template< typename K, typename V, typename Cmp >
    Dictionary< K, V, Cmp > Dictionary< K, V, Cmp >::getIntersect(const Dictionary& right) const
    {
        Dictionary newDict(m_Name);
        Dictionary copiedRightDict(right);

        for (size_t i = 0; i < size(); i++)
        {
            if (copiedRightDict.contains(m_Data[i].first))
            {
                newDict.tryEmplace(m_Data[i].first, m_Data[i].second);
            }
        }

        return newDict;
    }

    template< typename K, typename V, typename Cmp >
    Dictionary< K, V, Cmp > Dictionary< K, V, Cmp >::getComplement(const Dictionary& right) const
    {
        Dictionary newDict(m_Name);
        Dictionary copiedRightDict(right);

        for (size_t i = 0; i < size(); i++)
        {
            if (!copiedRightDict.contains(m_Data[i].first))
            {
                newDict.tryEmplace(m_Data[i].first, m_Data[i].second);
            }
        }

        return newDict;
    }

    template< typename K, typename V, typename Cmp >
    typename Dictionary< K, V, Cmp >::iterator Dictionary< K, V, Cmp >::begin()
    {
        return m_Data.begin();
    }

    template< typename K, typename V, typename Cmp >
    typename Dictionary< K, V, Cmp >::iterator Dictionary< K, V, Cmp >::end()
    {
        return m_Data.end();
    }

    template< typename K, typename V, typename Cmp >
    typename Dictionary< K, V, Cmp >::const_iterator Dictionary< K, V, Cmp >::cbegin() const
    {
        return m_Data.cbegin();
    }

    template< typename K, typename V, typename Cmp >
    typename Dictionary< K, V, Cmp >::const_iterator Dictionary< K, V, Cmp >::cend() const
    {
        return m_Data.cend();
    }

    template< typename K, typename V, typename Cmp >
    Dictionary< K, V, Cmp >& Dictionary< K, V, Cmp >::operator=(const Dictionary& right)
    {
        m_Data = right.m_Data;
        m_Name = right.m_Name;

        return *this;
    }

    template< typename K, typename V, typename Cmp >
    V Dictionary< K, V, Cmp >::operator[](K key) const
    {
        return find(key).second;
    }
}
#endif
