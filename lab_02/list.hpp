#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <memory>
#include <ctime>
#include <iterator>
#include <algorithm>

#include "list.h"

//конструктор по умолчанию
template <typename T>
List<T>::List() : head(nullptr), tail(nullptr) {}
template <typename T>
size_t List<T>::get_size() const
{
    return sizeList;
}
//конструктор копирования
template <typename T>
List<T>::List(const List<T> &someList) : head(nullptr), tail(nullptr)
{
    this->extend(someList);
}
//конструктор перемещения
template <typename T>
List<T>::List(List<T> &&someList)
{
    this->sizeList = someList->sizeList;
    this->head.reset(someList->head);
    this->tail.reset(someList->tail);

    someList->sizeList = 0;
    someList->head = nullptr;
    someList->tail = nullptr;
}
//конструктор от списка
template <typename T>
List<T>::List(std::initializer_list<T> someList) : head(nullptr), tail(nullptr)
{
    for (const auto &data : someList)
        append(data);
}
//конструктор от массива
template <typename T>
List<T>::List(const T *arr, const int size)
{
    for (int i = 0; i < size; i++)
        this->append(arr[i]);
}
//конструктор от итератора
template <typename T>
template <typename T_>
List<T>::List(T_ begin, T_ end)
{
    for (auto it = begin; end != it; ++it)
        this->append(*it);
}
//operator= копирование
template <typename T>
List<T> &List<T>::operator=(const List &someList)
{
    if (this != &someList)
    {
        this->clear();
        this->extend(someList);
    }

    return *this;
}
//operator= перемещение
template <typename T>
List<T> &List<T>::operator=(List &&someList)
{
    if (this != someList)
    {
        this->clear();
        this->sizeList = someList->sizeList;
        this->head = someList->head;
        this->tail = someList->tail;

        someList->sizeList = 0;
        someList->head = nullptr;
        someList->tail = nullptr;
    }

    return *this;
}
//operator= от списка
template <typename T>
List<T> &List<T>::operator=(std::initializer_list<T> someList)
{
    if (this != &someList)
    {
        this->clear();
        this->sizeList = someList->size;
        this->head = someList->begin;
        this->tail = someList->end;

        someList->size = 0;
        someList->begin = nullptr;
        someList->end = nullptr;
    }

    return *this;
}
//добавить элемент в конец
template <typename T>
List<T> &List<T>::append(const T &data)
{
    std::shared_ptr<ListNode<T>> newNode = initNode(data);

    if (this->isEmpty())
        this->head = newNode;
    else
        this->tail->setNext(newNode);

    this->tail = newNode;

    return *this;
}
//добавить элемент в конец
template <typename T>
List<T> &List<T>::operator+=(const T &data)
{
    this->append(data);
    return *this;
}
//добавить элемент в конец
template <typename T>
List<T> &List<T>::add(const T &data) const
{
    List<T> newList(*this);
    newList.append(data);
    return newList;
}
//добавить элемент в конец
template <typename T>
List<T> List<T>::operator+(const T &data) const
{
    return *this->add(data);
}
//вставить элемент по значению итератора
template <typename T>
List<T> &List<T>::insert(const T &data, const Iterator<T> &iter) noexcept
{
    time_t t_time = time(NULL);
    std::shared_ptr<ListNode<T>> curNode = this->head;
    std::shared_ptr<ListNode<T>> tmp = nullptr;
    Iterator<T> cur = this->begin();

    if (this->head == nullptr && cur == iter)
    {
        std::shared_ptr<ListNode<T>> newNode = initNode(data);
        this->head = newNode;
        this->tail = newNode;
        return *this;
    }

    while(curNode && cur != iter)
    {
        tmp=curNode;
        curNode=curNode->getNext();
        cur.next();
    }

    if (curNode == nullptr)
        throw ListRangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    std::shared_ptr<ListNode<T>> newNode = initNode(data, curNode);

    if (curNode == this->head)
        this->head = newNode;
    else
        tmp->setNext(newNode);

    return *this;
}
//добавить список к концу
template <typename T>
List<T> &List<T>::extend(const List &ListToAdd)
{
    if (ListToAdd.isEmpty())
        return *this;

    if (this == &ListToAdd)
    {
        List<T> ListCopy;
        ListCopy = ListToAdd;
        addList(ListCopy);
    }
    else
        addList(ListToAdd);

    return *this;
}
//добавить список к концу
template <typename T>
List<T> &List<T>::operator+=(const List<T> &someList)
{
    this->extend(someList);
    return *this;
}
//добавить список к концу
template <typename T>
List<T> &List<T>::addlist(const List<T> &someList) const
{
    List<T> newList(*this);
    newList.extend(someList);
    return newList;
}
//добавить список к концу
template <typename T>
List<T> List<T>::operator+(const List<T> &someList) const
{
    return *this->addlist(someList);
}
//удалить элемент с конца
template <typename T>
const T List<T>::pop()
{
    time_t t_time = time(NULL);
    if (this->isEmpty())
        throw ListEmptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    Iterator<T> iter = this->end();

    return remove(iter);
}
//удалить элемент по итератору
template <typename T>
const T List<T>::remove(const Iterator<T> &iter)
{
    time_t t_time = time(NULL);
    if (this->isEmpty())
        throw ListEmptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    std::shared_ptr<ListNode<T>> curNode = this->head;
    std::shared_ptr<ListNode<T>> tmp = nullptr;
    Iterator<T> cur = this->begin();

    while(curNode && cur != iter)
    {
        tmp=curNode;
        curNode=curNode->getNext();
        cur.next();
    }

    if (curNode == nullptr)
        throw ListRangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    T retData = iter.getCur();

    if (curNode->getNext() == nullptr)
        this->tail = tmp;

    if (curNode == this->head)
        this->head = this->head->getNext();
    else
        tmp->setNext(curNode->getNext());

    this->sizeList -= 1;

    return retData;
}
//очистка списка
template <typename T>
List<T> &List<T>::clear()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->sizeList = 0;

    return *this;
}
//проверка на равенство
template <typename T>
bool List<T>::isEqual(const List<T> &someList) const
{
    return isNodesEqual(someList);
}
//проверка на равенство
template <typename T>
bool List<T>::operator==(const List &someList) const
{
    return isNodesEqual(someList);
}
//проверка на неравенство
template <typename T>
bool List<T>::isNotEqual(const List<T> &someList) const
{
    return !isNodesEqual(someList);
}
//проверка на неравенство
template <typename T>
bool List<T>::operator!=(const List &someList) const
{
    return !isNodesEqual(someList);
}
//итератор начало
template <typename T>
Iterator<T> List<T>::begin()
{
    return Iterator<T>(head);
}
//итератор конец
template <typename T>
Iterator<T> List<T>::end()
{
    return Iterator<T>(tail);
}
//итератор начало
template <typename T>
const Iterator<T> List<T>::c_begin() const
{
    return Iterator<T>(head);
}
//итератор конец
template <typename T>
const Iterator<T> List<T>::c_end() const
{
    return Iterator<T>(tail);
}
//новый узел
template <typename T>
std::shared_ptr<ListNode<T>> List<T>::initNode(const T &data, std::shared_ptr<ListNode<T>> ptrNode)
{
    time_t t_time = time(NULL);
    std::shared_ptr<ListNode<T>> newNode;
    newNode = std::make_shared<ListNode<T>>();
    if (!newNode)
        throw ListMemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

    newNode->setData(data);
    newNode->setNext(ptrNode);
    this->sizeList += 1;

    return newNode;
}
//добавить список к концу (private)
template <typename T>
void List<T>::addList(const List &ListToAdd)
{
    T data = ListToAdd.head->getData();
    std::shared_ptr<ListNode<T>> nextNode = ListToAdd.head->getNext();
    std::shared_ptr<ListNode<T>> nodeToAdd = initNode(data, nextNode);
    std::shared_ptr<ListNode<T>> cur = this->head;

    if (this->isEmpty())
    {
        cur = nodeToAdd;
        this->head = cur;
    }
    else
    {
        for (; cur->getNext(); cur = cur->getNext())
            ;
        cur->setNext(nodeToAdd);
        cur = cur->getNext();
    }

    std::shared_ptr<ListNode<T>> curToAdd = nextNode;

    for (; curToAdd; curToAdd = curToAdd->getNext(), cur = cur->getNext()) // пока есть след-ий
    {
        data = curToAdd->getData();
        nextNode = curToAdd->getNext();
        nodeToAdd = initNode(data, nextNode);
        cur->setNext(nodeToAdd);
    }
    this->tail = nodeToAdd;
}
//проверка узлов на равенство
template <typename T>
bool List<T>::isNodesEqual(const List<T> &someList) const
{
    std::shared_ptr<ListNode<T>> curL = this->head;
    std::shared_ptr<ListNode<T>> curR = someList.head;
    for (; curL && curR && curL->getData() == curR->getData();)
    {
        curL = curL->getNext();
        curR = curR->getNext();
    }

    return (curL == nullptr && curR == nullptr) ? true : false;
}
//проверка, пуст ли список
template <typename T>
bool List<T>::isEmpty() const
{
    return (this->head == nullptr) ? true : false;
}
//operator<<
template <typename T>
std::ostream &operator<<(std::ostream &stream, List<T> &list)
{
    stream << "List";
    Iterator<T> iter = list.begin();
    if (!iter.checkRange())
        stream << " is empty";
    else
    {
        stream << ":";
        for (; iter.checkRange(); iter.next())
            stream << " " << iter.getCur();
    }

    return stream;
}

#endif
