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

    std::shared_ptr< K > first;
    std::shared_ptr< V > second;
  };
  template< typename K, typename V >
  using pair = Pair< K, V >;

  template< typename K, typename V >
  Pair< K, V >::Pair() 
  {
    first = nullptr;
    second = nullptr;
  }

  template< typename K, typename V >
  Pair< K, V >::Pair(K first, V second) : first(first), second(second) {}

  template<typename K, typename V>
  Pair< K, V >::Pair(const Pair& other) : first(other.first), second(other.second) {}

  template<typename K, typename V>
  inline Pair<K, V>& Pair<K, V>::operator=(const Pair& right)
  {
    first = right.first;
    second = right.second;

    return *this;
  }
}
#endif
