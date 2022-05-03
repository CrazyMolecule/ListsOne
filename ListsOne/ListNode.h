#ifndef LISTNODE_H
#define LISTNODE_H
#include <memory>

template< typename T >
struct ListNode
{
  T m_Data;
  std::shared_ptr< ListNode > m_PointerNext;

  ListNode(const T& data = T(), std::shared_ptr< ListNode > pNext = nullptr) : m_PointerNext(pNext), m_Data(data) {}
};
#endif
