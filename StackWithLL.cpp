#include <iostream>
#include <string>
#include "StackWithLL.h"
using namespace std;


template <class Object>
Stack<Object>::Stack(int x,int y, int l, int r,int u, int d)
{
    
      topOfStack = NULL;
}
template <class Object>
Stack<Object>::Stack()
{
    
      topOfStack = NULL;
}

template <class Object>
bool Stack<Object>::isEmpty( ) const
{
      return topOfStack == NULL;
}
template <class Object>
List<int>::ListNode *  Stack<Object>::currentnode( ) const
{
      return topOfStack ;
}
template <class Object>
void Stack<Object>::currentnodeupdate() 
{
       topOfStack =topOfStack->next ;
}
template <class Object>
int Stack<Object>::currentx( ) const
{
    int x = topOfStack ->elementx;
    return x ;
}
template <class Object>
int Stack<Object>::currenty( ) const
{
      return topOfStack ->elementy;
}

template <class Object>
const Object & Stack<Object>::top( ) const
{
     if ( isEmpty( ) )
         cout<<"Underflow";
    return topOfList->element;
}
template <class Object>
void Stack<Object>::pop( ) 
{
     if ( isEmpty( ) )
          cout<<"Underflow";
    List<int>::ListNode * oldTop = topOfStack;
topOfStack = topOfStack->next;
delete oldTop;
}
template <class Object>
void Stack<Object>::push( const Object & x , const Object & y)
{
     topOfStack = new List<int>::ListNode ( x,y, topOfStack );
}



template <class Object>
Object Stack<Object>::topAndPop( )
{
     Object topItem = top( );
     pop( );
     return topItem;
}
template <class Object>
void Stack<Object>::makeEmpty( )
{
    while ( ! isEmpty( ) )
         pop( );
}

template <class Object>
const Stack<Object> & Stack<Object>:: operator=( const Stack<Object> & rhs )//deep copy
{
      if ( this != &rhs )
      {
           makeEmpty( );
           if ( rhs.isEmpty( ) )
                return *this;

          List<int>::ListNode *rptr = rhs.topOfStack;
          List<int>::ListNode  *ptr  = new List<int>::ListNode (rptr->elementx,rptr->elementy, rptr->l, rptr->r, rptr->u, rptr->d );
          topOfStack = ptr;

           for ( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
               ptr = ptr->next = new List<int>::ListNode (rptr->elementx,rptr->elementy, rptr->l, rptr->r, rptr->u, rptr->d );
    }
    return *this;
}

template <class Object>
Stack<Object>::Stack( const Stack<Object> & rhs )//copy constructor
{
       topOfStack = NULL;
       *this = rhs; // deep copy
}
template <class Object>
Stack<Object>::~Stack( )//destructor
{
      makeEmpty( );
}
