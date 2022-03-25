/*Класс узла*/
#ifndef _LISTNODE_H_
#define _LISTNODE_H_
#include <memory>

template <typename T>
class ListNode
{
private:
    T data;
    std::shared_ptr<ListNode<T>> next;
public:
    //конструкторы
    ListNode();
    explicit ListNode(const T dataToAdd);
    explicit ListNode(const std::shared_ptr<ListNode<T>> node);
    ListNode(const T data, const std::shared_ptr<ListNode<T>> nextNode);
    //деструктор
    virtual ~ListNode();

    //геттеры, сеттеры
    void setData(const T data);
    T getData() const;
    T& getPtrData();

    void setNext(const std::shared_ptr<ListNode<T>> nextNode);
    std::shared_ptr<ListNode<T>> getNext();

    //операторы перегрузка
    bool operator==(const ListNode<T>& secondNode) const;
    bool operator!=(const ListNode<T>& secondNode) const;
    bool operator>(const ListNode<T>& secondNode) const;
    bool operator<(const ListNode<T>& secondNode) const;
    bool operator>=(const ListNode<T>& secondNode) const;
    bool operator<=(const ListNode<T>& secondNode) const;
};

#endif
