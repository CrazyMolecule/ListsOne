#include "ForwardList.h"
#include "Pair.h"

#include <stdexcept>
#include <utility>

#ifndef DICTIONARY_H
#define DICTIONARY_H
template< typename K, typename V, typename Cmp = std::greater< K > >
class Dictionary
{
public:
    Dictionary(std::string name = "dictionary");

    Dictionary& operator=(const Dictionary& right);
    V operator[](K key);
    friend std::ostream& operator<<(std::ostream& out, Dictionary< K, V, Cmp >& value)
    {
        out << "{";
        for (size_t i = 0; i < value.getCount(); i++)
        {
            out << value.m_Data[i];
            if (i != value.getCount() - 1)
            {
                out << ", ";
            }
        }
        out << "}";

        return out;
    }

    int getCount();

    void push(K key, V value);

    pair< K, V >& findPair(K& key); // +
    bool has(const K& key); // +
    void sort();

    V get(K key); // +
    void pop(K key); // +

private:
    forward_list< pair< K, V > > m_Data;
    std::string m_Name;
};
template< typename K, typename V, typename Cmp = std::less< K > >
using dictionary = Dictionary< K, V, Cmp >;

template< typename K, typename V, typename Cmp >
Dictionary< K, V, Cmp >::Dictionary(std::string name)
{
    m_Data = forward_list< pair< K, V > >();
    m_Name = name;
}

template<typename K, typename V, typename Cmp>
int Dictionary<K, V, Cmp>::getCount()
{
    return m_Data.getCount();
}

template< typename K, typename V, typename Cmp >
void Dictionary< K, V, Cmp >::push(K key, V value)
{
    if (has(key))
    {
        pop(key);
    }
    m_Data.pushFront(pair<K, V>(key, value));

    sort();
}

template< typename K, typename V, typename Cmp >
V Dictionary< K, V, Cmp >::get(K key)
{
    return findPair(key);
}

template<typename K, typename V, typename Cmp>
bool Dictionary<K, V, Cmp>::has(const K& key)
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

template<typename K, typename V, typename Cmp>
void Dictionary<K, V, Cmp>::sort()
{
    forward_list< pair< K, V > > tempData = m_Data;

    for (int i = 0; i < m_Data.getCount() - 1; i++)
    {
        for (int j = 0; j < m_Data.getCount() - i - 1; j++)
        {
            if (Cmp{}(tempData[j].first(), tempData[j + 1].first()))
            {
                std::swap(tempData[j], tempData[j + 1]);
            }
        }
    }

    m_Data = tempData;
}

template<typename K, typename V, typename Cmp>
pair<K, V>& Dictionary<K, V, Cmp>::findPair(K& key)
{
    for (size_t i = 0; i < m_Data.getCount(); i++)
    {
        if (m_Data[i].first() == key)
        {
            return m_Data[i];
        }
    }

    throw std::runtime_error("Trying to get value from dictionary by key, which is not present.");
}

template< typename K, typename V, typename Cmp >
void Dictionary< K, V, Cmp >::pop(K key)
{
    bool flag = false;
    for (size_t i = 0; i < m_Data.getCount(); i++)
    {
        if (m_Data[i].first() == key)
        {
            flag = true;
            m_Data.removeAt(i);
        }
    }

    if (!flag)
    {
        throw std::runtime_error("Trying to get value from dictionary by key, which is not present.");
    }
}

template<typename K, typename V, typename Cmp>
inline Dictionary<K, V, Cmp>& Dictionary<K, V, Cmp>::operator=(const Dictionary& right)
{
    m_Data = right.m_Data;

    return *this;
}

template<typename K, typename V, typename Cmp>
V Dictionary<K, V, Cmp>::operator[](K key)
{
    return get(key);
}
#endif
