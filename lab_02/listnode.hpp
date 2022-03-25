#ifndef _LISTNODE_HPP_
#define _LISTNODE_HPP_

#include "listnode.h"
//конструктор по умолчанию
template <typename T>
ListNode<T>::ListNode()
{
    data = (0);
    next = (nullptr);
}
//конструктор копирования
template <typename T>
ListNode<T>::ListNode(const T data)
{
    this->data = (data);
    next = (nullptr);
}
//конструктор от укзателя
template <typename T>
ListNode<T>::ListNode(const std::shared_ptr<ListNode<T>> node) : data(node->data)
{
    next = node;
}
//конструктор копирования с переходом на новый узел
template <typename T>
ListNode<T>::ListNode(const T data, const std::shared_ptr<ListNode<T>> nextNode) : data(data)
{
    next = nextNode;
}
//деструктор
template <typename T>
ListNode<T>::~ListNode()
{
    data = 0;
    next = nullptr;
}
//сеттер
template <typename T>
void ListNode<T>::setData(const T data)
{
    this->data = data;
}
//геттер
template <typename T>
T ListNode<T>::getData() const
{
    return data;
}
//геттер на адрес
template <typename T>
T& ListNode<T>::getPtrData()
{
    return data;
}
//сеттер следующего узла
template <typename T>
void ListNode<T>::setNext(const std::shared_ptr<ListNode<T>> nextNode)
{
    next = nextNode;
}
//геттер следующего узла
template <typename T>
std::shared_ptr<ListNode<T>> ListNode<T>::getNext()
{
    return next;
}
// operator==
template <typename T>
bool ListNode<T>::operator==(const ListNode& secondNode) const
{
    return (this->data == secondNode.data) ? true : false;
}
// operator!=
template <typename T>
bool ListNode<T>::operator!=(const ListNode& secondNode) const
{
    return (data != secondNode.data) ? true : false;
}
// operator>
template <typename T>
bool ListNode<T>::operator>(const ListNode& secondNode) const
{
    return (data > secondNode.data) ? true : false;
}
// operator<
template <typename T>
bool ListNode<T>::operator<(const ListNode& secondNode) const
{
    return (data < secondNode.data) ? true : false;
}
// operator>=
template <typename T>
bool ListNode<T>::operator>=(const ListNode& secondNode) const
{
    return (data < secondNode.data) ? false : true;
}
// operator<=
template <typename T>
bool ListNode<T>::operator<=(const ListNode& secondNode) const
{
    return (data > secondNode.data) ? false : true;
}

#endif
