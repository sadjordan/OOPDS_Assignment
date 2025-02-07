#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node* next;
};

template <typename T>
class Linked_List
{
private:
    Node<T>* head;
    int size; 

public:
    Linked_List() : head(nullptr), size(0) {}

    int list_size() { return size; }

    bool empty() { return head == nullptr; }

    void push_front(T value)
    {
        Node<T>* newNode = new Node<T>();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
        size++;
    }

    void push_back(T value)
    {
        Node<T>* newNode = new Node<T>();
        newNode->data = value;
        newNode->next = nullptr;

        if (empty())
        {
            head = newNode;
        }
        else
        {
            Node<T>* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }

    void deleteNode(T value)
    {
        if (empty())
        {
            cout << "List is empty. Nothing to delete.\n";
            return;
        }

        if (head->data == value)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }

        Node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data != value)
        {
            temp = temp->next;
        }

        if (temp->next == nullptr)
        {
            cout << "Value not found in the list.\n";
        }
        else
        {
            Node<T>* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            size--;
        }
    }

    void pop_front()
    {
        if (empty())
            cout << "Nothing to remove" << endl;
        else
        {
            Node<T>* ptr = head;
            head = head->next;
            delete ptr;
            size--;
        }
    }

    void pop_back()
    {
        if (empty())
            cout << "Nothing to delete" << endl;
        else if (size == 1)
        {
            delete head;
            head = nullptr;
            size--;
        }
        else
        {
            Node<T>* prev = head;
            Node<T>* ptr = prev->next;
            while (ptr->next != nullptr)
            {
                prev = prev->next;
                ptr = ptr->next;
            }
            prev->next = nullptr;
            delete ptr;
            size--;
        }
    }

    void insert(int index, T value)
    {
        if (index < 0 || index > size)
        {
            cout << "Invalid index." << endl;
            return;
        }

        if (index == 0)
            push_front(value);
        else if (index == size)
            push_back(value);
        else
        {
            Node<T>* before = head;
            for (int i = 0; i < index - 1; i++)
                before = before->next;

            Node<T>* ptr = new Node<T>();
            ptr->data = value;
            ptr->next = before->next;
            before->next = ptr;
            size++;
        }
    }

    void replace(int index, T value)
    {
        if (index < 0 || index >= size)
        {
            cout << "Invalid index." << endl;
            return;
        }

        Node<T>* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        current->data = value;
    }

    void display()
    {
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("Index out of range");
        }

        Node<T>* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }

    int find_index(T value)
    {
        Node<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->data == value)
            {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }

    ~Linked_List()
    {
        while (!empty())
        {
            pop_front();
        }
    }
};

#endif