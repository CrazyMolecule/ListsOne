#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <utility>
#include <stdexcept>
#include "ForwardList.h"

namespace bavykin
{
  template< typename K, typename V, typename Cmp = std::greater< K > >
  class Dictionary
  {
  public:
    Dictionary(const std::string& name = "dictionary");
    Dictionary(const Dictionary& right);

    Dictionary& operator=(const Dictionary& right);
    V operator[](K key) const;
    friend std::ostream& operator<<(std::ostream& out, Dictionary< K, V, Cmp >& value)
    {
      if (value.getCount() == 0)
      {
        out << "<EMPTY>";
        return out;
      }

      out << value.m_Name << " ";
      for (size_t i = 0; i < value.getCount(); i++)
      {
        out << value.m_Data[i].first << " " << value.m_Data[i].second;
        if (i != value.getCount() - 1)
        {
          out << " ";
        }
      }

      return out;
    }

    size_t getCount() const;
    void push(K key, V value);
    std::pair< K, V >& findPair(const K& key) const;
    bool has(const K& key) const;
    std::pair< K, V > get(K key) const;
    void pop(K key);
    void changeName(std::string name);
    Dictionary getUnion(const Dictionary& right) const;
    Dictionary getIntersect(const Dictionary& right) const;
    Dictionary getComplement(const Dictionary& right) const;

  private:
    forward_list< std::pair< K, V > > m_Data;
    std::string m_Name;
  };
  template< typename K, typename V, typename Cmp = std::greater< K > >
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
  size_t Dictionary< K, V, Cmp >::getCount() const
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
    m_Data.pushFront(std::pair< K, V >(key, value));

    m_Data.sort();
  }

  template< typename K, typename V, typename Cmp >
  std::pair< K, V > Dictionary< K, V, Cmp >::get(K key) const
  {
    return findPair(key);
  }

  template< typename K, typename V, typename Cmp >
  bool Dictionary< K, V, Cmp >::has(const K& key) const
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
  std::pair< K, V >& Dictionary< K, V, Cmp >::findPair(const K& key) const
  {
    for (size_t i = 0; i < m_Data.getCount(); i++)
    {
      if (m_Data[i].first == key)
      {
        return m_Data[i];
      }
    }

    throw std::runtime_error("Trying to get value from dictionary by key, which is not present.");
  }

  template< typename K, typename V, typename Cmp >
  void Dictionary< K, V, Cmp >::pop(K key)
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
      throw std::runtime_error("Trying to get value from dictionary by key, which is not present.");
    }
  }

  template< typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp > Dictionary< K, V, Cmp >::getUnion(const Dictionary& right) const
  {
    Dictionary newDict(right);

    for (size_t i = 0; i < getCount(); i++)
    {
      newDict.push(m_Data[i].first, m_Data[i].second);
    }

    newDict.m_Name = m_Name;

    return newDict;
  }

  template< typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp > Dictionary< K, V, Cmp >::getIntersect(const Dictionary& right) const
  {
    Dictionary newDict(m_Name);
    Dictionary copiedRightDict(right);

    for (size_t i = 0; i < getCount(); i++)
    {
      if (copiedRightDict.has(m_Data[i].first))
      {
        newDict.push(m_Data[i].first, m_Data[i].second);
      }
    }

    return newDict;
  }

  template< typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp > Dictionary< K, V, Cmp >::getComplement(const Dictionary& right) const
  {
    Dictionary newDict(m_Name);
    Dictionary copiedRightDict(right);

    for (size_t i = 0; i < getCount(); i++)
    {
      if (!copiedRightDict.has(m_Data[i].first))
      {
        newDict.push(m_Data[i].first, m_Data[i].second);
      }
    }

    return newDict;
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
    return get(key).second;
  }
}
#endif
