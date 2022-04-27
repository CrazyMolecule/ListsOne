#ifndef PAIR_H
#define PAIR_H

namespace bavykin
{
  template< typename K, typename V >
  class Pair
  {
  public:
    Pair();
    Pair(K, V);
    Pair(const Pair& other);

    Pair& operator=(const Pair& right);
    friend std::ostream& operator<<(std::ostream& out, Pair< K, V >& value)
    {
      out << value.first() << " " << value.second();

      return out;
    }

    K& first();
    V& second();

  private:
    std::shared_ptr< K > m_First;
    std::shared_ptr< V > m_Second;
  };
  template< typename K, typename V >
  using pair = Pair< K, V >;

  template< typename K, typename V >
  Pair< K, V >::Pair() 
  {
    m_First = nullptr;
    m_Second = nullptr;
  }

  template< typename K, typename V >
  Pair< K, V >::Pair(K first, V second) : m_First(first), m_Second(second) {}

  template<typename K, typename V>
  Pair< K, V >::Pair(const Pair& other) : m_First(other.m_First), m_Second(other.m_Second) {}

  template<typename K, typename V>
  inline Pair<K, V>& Pair<K, V>::operator=(const Pair& right)
  {
    m_First = right.m_First;
    m_Second = right.m_Second;

    return *this;
  }

  template< typename K, typename V >
  K& Pair< K, V >::first()
  {
    return *m_First;
  }

  template< typename K, typename V >
  V& Pair< K, V >::second()
  {
    return *m_Second;
  }
}
#endif
