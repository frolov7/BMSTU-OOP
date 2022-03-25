/*Класс List, наследующий  виртуальный класс ListBase*/
#pragma once
#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <stdarg.h>
#include <iterator>

#include "errors.h"
#include "listnode.h"
#include "listiterator.h"

//базовый класс
class ListBase
{
protected: // !!!!!!
    size_t sizeList;

public:
    virtual size_t get_size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual ~ListBase() = default;
};
//класс List
template <typename T>
class List : public ListBase
{
public: // !!!!!! public 1st
    size_t get_size() const;
    //конструкторы
    List();
    explicit List(const List<T>& someList); // !!!!!!
    explicit List(List<T>&& someList);
    explicit List(std::initializer_list<T> someList);
    List(const T* arr, const int size);
    template <typename T_>
    List(T_ begin, T_ end);
    //деструктор виртуальный, т.к класс не берет памяти из кучи
    virtual ~List() = default;

    //операторы
    List<T>& operator=(const List<T>& someList); // для копирования
    List<T>& operator=(List<T>&& someList); // для перемещения
    List<T>& operator=(std::initializer_list<T> someList); // для иницилайзер лист

    List<T>& append(const T& data);
    List<T>& operator+=(const T& data);
    List<T>& add(const T& data) const;
    List<T> operator+(const T& data) const;

    List<T>& insert(const T& data, const Iterator<T>& iter) noexcept; //!!!!!!!!!!!!!!!!!

    List<T>& extend(const List<T>& ListToAdd);
    List<T>& operator+=(const List<T>& someList);
    List<T>& addlist(const List<T>& someList) const;
    List<T> operator+(const List<T>& somelist) const;

    //удалить элемент с конца
    const T pop();

    //удалить элемент с места, куда указывает итератор
    const T remove(const Iterator<T>& iter);

    //очистка списка
    List<T>& clear();

    bool isEqual(const List<T>& someList) const;
    bool operator==(const List<T>& someList) const;
    bool isNotEqual(const List<T>& someList) const;
    bool operator!=(const List<T>& someList) const;

    //итераторы
    Iterator<T> begin(); // !!!!!!
    Iterator<T> end();

    const Iterator<T> c_begin() const;
    const Iterator<T> c_end() const;
private:
    //указатели на начало и конец списка
    std::shared_ptr<ListNode<T>> head;
    std::shared_ptr<ListNode<T>> tail;

    //создание узла
    std::shared_ptr<ListNode<T>> initNode(const T& data, std::shared_ptr<ListNode<T>> ptrNode = nullptr);
    //добавление списка
    void addList(const List<T>& ListToAdd);
    //сравнение для оператора =
    bool isNodesEqual(const List<T>& someList) const;
    //проверка, пуст ли список
    bool isEmpty() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, List<T>& list);

#endif
