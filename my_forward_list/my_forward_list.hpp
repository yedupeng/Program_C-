#ifndef MY_FORWARD_LIST_HPP
#define MY_FORWARD_LIST_HPP

#include <algorithm>
#include <iostream>
template <typename T>
class Forward_list
{
public:
    class Node
    {
    public:
        // A node will hold data of type T
        T data{};
        // next will point to the next node in the list
        // we initialise next to nullptr
        Node* next = nullptr;

        // Because we have already intialised the variables
        // the default constructor doesn't need to do anything
        Node(){}

        // To make life easier we also provide a constructor
        // that takes the T data to be copied into the data member variable 
        // There is an optional second argument which is
        // used to update the next pointer.  This defaults to nullptr 
        // if the constructor is called with just one argument.
        Node(T input_data, Node* next_node= nullptr)
        {
            data = input_data;
            next = next_node;
        }

        // Destructor
        ~Node(){}
    };

private:
    // private member variables for Forward_list
    // the trailing underscore is a stylistic choice to 
    // distinguish these as private member variables
    unsigned size_ = 0;
    Node* head_ = nullptr;

public:
    // public member functions of the Forward_list class
    // We have generally used the same names as for the
    // corresponding functions of std::forward_list

    // Default constructor does not need to do anything 
    // and is provided for you.
    Forward_list();
   
    // The destructor is implemented for you
    ~Forward_list();

    // Copy constructor
    //*** For you to implement
    Forward_list(const Forward_list<T>& other);

    // Constructor from initializer list
    //*** For you to implement
    Forward_list(std::initializer_list<T> input);

    // Add an element to the front of the list
    //*** For you to implement
    void push_front(const T& data);

    // Remove the first element of the list
    //*** For you to implement
    void pop_front();

    // Return the data held in the first item of the list
    // This function should not change the list, which is 
    // why it is declared const
    //*** For you to implement
    T front() const;

    // Print out all the data in the list in sequence
    //*** For you to implement
    void display() const;

    // Outputs if the list is empty or not
    // Implemented for you
    bool empty() const;

    // outputs the size of the list
    // Implemented for you, but your code should properly 
    // update the size_ member variable as needed
    unsigned size() const;


    // methods related to sorting     

    // merge two sorted lists, *this and other
    //*** For you to implement
    void merge(Forward_list& other);

    // split *this into its first half, which becomes the new *this,
    // and its second half which is returned
    //*** For you to implement
    Forward_list split();

    // The sort function uses the helper functions 
    // merge and split that you write
    // You do not need to modify sort itself
    void sort();

private:

    // sort is implemented via a recursive merge sort
    // You do not need to modify this function
    void merge_sort(Forward_list&);

};

// Default Constructor
// You do not need to change this
template <typename T>
Forward_list<T>::Forward_list()
{

}

// Destructor
// The destructor is implemented for you
template <typename T>
Forward_list<T>::~Forward_list()
{
    while(head_ != nullptr)
    {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
        --size_;
    }
}

// Copy constructor
// ***For you to implement

// The copy constructor takes as argument a const reference to a 
// another Forward_list "other" 
// The const means that the function should not modify other
// The function should make a "deep copy" of the other list,
// that is create a new node for every node in other and copy 
// the data of other into these new nodes.  
template <typename T>
Forward_list<T>::Forward_list(const Forward_list& other)
{
    this->head_=NULL;
    Node* temp=other.head_;
    while(temp!=NULL)
    {
        Node* pnew=new Node;
        pnew->next=NULL;
        pnew->data=temp->data;
        if(head_==NULL)
            head_=pnew;
        else
        {
            Node* prear=head_;
            while(prear->next!=NULL)prear=prear->next;
            prear->next=pnew;
        }
        temp=temp->next;
        ++size_;
    }
}

// Constructor from initializer list
// ***For you to implement

// This implements the functionality you see with, for example, 
// std::forward_list<int> my_list = {1,2,3}
// which creates a new linked list where the first node holds 1, second 2, and 
// third 3.
// The {1,2,3} here is of type std::initializer_list<int> and you 
// see this is the argument to this constructor (with data of type T
// rather than just int). 

// You can access the elements of a std::initializer_list via an iterator
// for example you can cycle through all the elements with
// for(auto it = input.begin(); it!= input.end(); ++it){Do something with *it} 
template <typename T>
Forward_list<T>::Forward_list(std::initializer_list<T> input)
{
    for(auto it = input.end()-1; it!= input.begin()-1; it--)
    {
        Node* new_node = new Node(*it,head_);
        new_node->data = *it;
        head_=new_node;
        size_++;
    } 
}


// Add element to front of list
// ***For you to implement
template <typename T>
void Forward_list<T>::push_front(const T& data)
{
	Node* newNode = new Node;  
    newNode->data = data;           
    if (head_ == NULL) {      
        head_ = newNode;
    }else
    {
    	newNode->next = head_;       
    	head_= newNode;
    }
	++size_;
}

// Remove the front element of the list 
// If the list is empty don't do anything
// ***For you to implement

template <typename T>
void Forward_list<T>::pop_front()
{
	Node *temp = head_->next;
	free(head_);
	head_ = temp;
	--size_;
}

// Return the data in the front element of the list
// If the list is empty the behaviour is undefined:
// you can return an arbitrary value, but don't segfault 
// ***For you to implement
template <typename T>
T Forward_list<T>::front() const
{
	return head_->data;
}


// Print out the list
// ***For you to implement
template <typename T>
void Forward_list<T>::display() const
{
	Node *p = head_;
    std::cout<<"Display the list from Head to Tail:"<<std::endl;
    while(p!=0){
        std::cout << p->data <<" ";
        p=p->next;
    }
    std::cout << std::endl;
}


// Outputs if the list is empty or not
// Implemented for you
template <typename T>
bool Forward_list<T>::empty() const
{
    return (head_ == nullptr);
}

// Returns the size of the list
// It is implemented for you but you need to correctly 
// update the size_ variable in your code as needed

// Note that std::forward_list actually does not have a size function
template <typename T>
unsigned Forward_list<T>::size() const
{
    return size_;
}


// the split function splits *this into its first half, which becomes 
// the new *this, and its second half which is returned
// if the the size of *this is n, then after split the size of *this 
// should be ceiling(n/2), and the size of the returned list should be
// floor(n/2)

// As an example, if *this is of the form
// head_ -> a -> b -> c -> d -> nullptr
// then after split *this should be
// head_ -> a -> b -> nullptr
// and you should a return a Forward_list other where
// other.head_ = c -> d -> nullptr

// Don't forget to update the size_ variable of this and other
// You do not need to create any new nodes for this function,
// just change pointers.
// ***For you to implement

template <typename T>
Forward_list<T> Forward_list<T>::split()
{
	Node *begin,*last_begin;
	size_ = 0;
	int i=0;
	begin = this->head_;
	while( begin!= nullptr)
	{
		size_++;
		begin = begin->next;
	}
	if(size_%2==0) 
	{
		size_ = size_/2;
	}
	else 
	{
		size_ = (size_+1)/2;
	}
	begin = this->head_;
	last_begin = nullptr;
	for(i=0;i<size_-1;i++)
	{
		begin = begin->next;
		last_begin = begin;
	}
	Forward_list<int> list;
	list.head_ = begin->next;
	last_begin->next = nullptr;
	return list;
}
// Merging two sorted lists
// For this function it is assumed that both *this and the 
// input Forward_list other are already sorted
// The function merges the two lists into sorted order, and the merger becomes 
// the new *this

// You do not need to create any new nodes in this function,
// just update pointers.  
// Set other to be an empty list at the end of the function
//***For you to implement

template <typename T>
void Forward_list<T>::merge(Forward_list& other)
{
    Node * temp_this=head_;
    Node * temp_other=other.head_;
    Node * s;
  
 
    if(temp_this->data <= temp_other->data)
    {
        s=temp_this;
        temp_this=s->next;
        
        size_=size_+this->size_;
    }
    else{
        s=temp_other;
        temp_other=s->next;
       size_=size_+other.size_;
    }
 
    while(temp_this->next!=nullptr && temp_other->next!=nullptr)
    {
         if(temp_this->data <= temp_other->data)
         {
             s->next=temp_this;
             s=temp_this;
             temp_this=s->next;
            // size_=size_+this->size_;
         }
         else{
             s->next=temp_other;
             s=temp_other;
             temp_other=s->next;
             //size_=size_+other.size_;
         }
    }
 
    if(temp_this==nullptr)
    {
        temp_this->next=temp_other;
    }
    if(temp_other==nullptr)
    {
        temp_other->next=temp_this;
    }
}
/*
template <typename T>
void Forward_list<T>::merge(Forward_list& other)
{
	if(this->head_== nullptr)
	{
		this->head_ = other.head_;
		other.head_ = NULL;
		return;	
	}
	Node *begin,*temp,*d;
	begin = this->head_;
	while( this->head_->next!= nullptr)
	{
		this->head_ = this->head_->next;
	}
	this->head_->next = other.head_;
	other.head_ = NULL;
	this->head_ = begin;
	
  	Node *p,*q;
	p=this->head_;
	int t = 0;
	while(p)
	{
		q=p->next;
		while(q)
		{
			if(p->data > q->data)
			{
				t=p->data;p->data=q->data;q->data=t;
			}
			q=q->next;
		}
		p=p->next;
	}
}*/

template <typename T>
void Forward_list<T>::merge_sort(Forward_list& my_list)
{
    if(my_list.size() == 0 || my_list.size() == 1)
    {
        return;
    }
    Forward_list<T> second = my_list.split();
    merge_sort(my_list);
    merge_sort(second);
    my_list.merge(second);
}

// sorts the list by calling merge_sort
// once your merge and split functions are working
// sort should automatically work
// you do not need to change this function
template <typename T>
void Forward_list<T>::sort()
{
    merge_sort(*this);
}


#endif