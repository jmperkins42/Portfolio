/*
    title: List.h
    author: Jonah Perkins
    date: 3/7/23
    purpose: header file for the list class
    for CSC 1310 program 2.
*/

#ifndef LIST_H
#define LIST_H


template<typename T> // templated class
class List
{
    private:
        // attributes
        struct listNode // struct defining what a node is
        {
            T data;
            listNode* next;
            listNode* prev;
        }; 
        listNode* head;
        listNode* tail;

        // private functions

        // private print function
        void print(listNode* node) // prints every node's data in the list starting with the given node
        {
            listNode* currNode = node; // sets currNode to the given node in the list
            while (currNode)
            {
                cout << "Index: " << currNode -> data -> getIndex() << " "; // prints out each node's index
                cout << "Population: " << currNode -> data -> getPopulation() << endl; // prints out each node's population
                currNode = currNode -> next; // moves to the next node
            }
        }

        // private mergesort function
        typename List<T>::listNode* mergesort(listNode* first, listNode* last)
        {
            // base case
            if (first == NULL || first -> data == last -> data)
                return first;
            // recursive case
            listNode* temp1 = first;
            listNode* temp2 = split(first, last);
            temp1 = mergesort(first, temp2 -> prev);
            temp2 = mergesort(temp2, last);
            return merge(temp1, temp2);
        }

        // private merge function
        typename List<T>::listNode* merge(listNode* first, listNode* second)
        {
            
            if (second == NULL) // if first partition is exhausted
            {
                return first;
            }
            if (first == NULL) // if second partition is exhausted
            {
                return second;
            }
            
            if (*(first -> data) < *(second -> data)) // if the second node's data is greater
            {
                listNode* temp = merge(first, second -> next); // recursive call to merge
                second -> next = temp;
                temp -> prev = second;
                second -> prev = NULL;
                return second;
            }
            else // if the first nodes data is greater
            {
                listNode* temp = merge(first -> next, second); // recursive call to merge
                first -> next = temp;
                temp -> prev = first;
                first -> prev = NULL;
                return first;
            }
        }

        // private split function
        typename List<T>::listNode* split(listNode* first, listNode* last)
        {
            listNode* front = first; // temporary pointer to front of list
            listNode* back = last; // temporary pointer to back of list
            while (front -> data != back -> data && front -> next -> data != back -> data) // finds the center of the list trhough double traversal
            {
                front = front -> next;
                back = back -> prev;
            }
            if (front == back) // accounts for an odd number of items in the list
                back = back -> next;
            front -> next = NULL;
            return back;
        }


    public: // public functions

        // constructor
        List()
        {
            head = NULL;
            tail = NULL;
        }

        // destructor
        ~List()
        {
            listNode* temp; // temporary listNode pointer
            while (head) // continues until head returns NULL, which returns false
            {
                // deletes the head and makes head -> next the new head
                temp = head;
                head = head -> next; 
                delete temp; 
            }
        }

        // print function
        void print()
        {
            print(head); // calls the private print function
        }

        // append function
        void append(T value)
        {
            listNode* newNode = new listNode; // creates the new node
            newNode -> data = value; // fills the node with the given data
            if (!head) // checks to see if the list is empty (if head is null, will return true)
            {
                head = newNode;
                tail = newNode;
            }
            else // if list isnt empty, it appends the new node onto the end of the list
            {
                tail -> next = newNode;
                newNode -> prev = tail;
                tail = newNode;
            }
        }

        // mergesort function
        void mergesort()
        {
            head = mergesort(head, tail); // calls the private mergesort function, with head and tail as arguments
            listNode* temp = head;
            while (temp -> next != NULL)
            {
                temp = temp -> next;
            }
            tail = temp;
        }
};  

#endif