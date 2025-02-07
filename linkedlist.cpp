#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include <iostream>
using namespace std;

// Node structure template
template <typename T>
struct Node
{
    T data;     // Data part
    Node* next; // Pointer to the next node
};

template <typename T>
class Linked_List
{
private:
    Node<T>* head; // Pointer to the first node
    int size;      // Used to keep track of list size

public:
    Linked_List() : head(nullptr), size(0) {} // Constructor that creates an empty list

    // Return size of list
    int list_size() { return size; }

    // Check if list is empty
    bool empty() { return head == nullptr; }

    // Insert a new node at the beginning
    void push_front(T value)
    {
        Node<T>* newNode = new Node<T>(); // Create a new node
        newNode->data = value;            // Set the data
        newNode->next = head;             // Link new node to the previous head
        head = newNode;                   // Update head to point to the new node
        size++;                           // Update size of list
    }

    // Insert a new node at the end
    void push_back(T value)
    {
        Node<T>* newNode = new Node<T>();
        newNode->data = value;
        newNode->next = nullptr;

        if (empty())
        { // If the list is empty
            head = newNode;
        }
        else
        {
            Node<T>* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode; // Link the last node to the new node
        }
        size++;
    }

    // Delete a node by value
    void deleteNode(T value)
    {
        if (empty())
        {
            cout << "List is empty. Nothing to delete.\n";
            return;
        }

        // If the node to be deleted is the head
        if (head->data == value)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }

        // Traverse to find the node to delete
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

    // Delete first element
    void pop_front()
    {
        if (empty())
            cout << "Nothing to remove" << endl;
        else
        {
            Node<T>* ptr = head;  // point to node 0
            head = head->next; // skip the first node
            delete ptr;        // free the deleted node

            // update size
            size--;
        }
    }

    // Delete last element
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

    // Insert value by index
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
            for (int i = 0; i < index - 1; i++) // Moves "before ptr" to the node behind the intended index
                before = before->next;

            // allocate a new node
            Node<T>* ptr = new Node<T>();

            // fill the data inside the node
            ptr->data = value;

            // Links the new node and the next node
            ptr->next = before->next;

            // Links the prev node with the new node
            before->next = ptr;
            size++;
        }
    }

    // Replace a value at intended index
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
            current = current->next; // Traverse to the node at the index
        }
        current->data = value; // Replace the value at the node
    }

    // Display the linked list
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
            current = current->next; // Traverse to the node at the index
        }
        return current->data; // Return the data at the node
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

    // Destructor to free all nodes
    ~Linked_List()
    {
        while (!empty())
        {
            pop_front();
        }
    }
};

#endif
