#ifndef _STACKWITHLL_H
#define _STACKWITHLL_H
template <class Object>
class List{
public:
    
    struct ListNode
    {
          int l,r,u,d;
          ListNode *next;
          Object   elementx, elementy, stck;
          ListNode(const Object & x , const Object & y,ListNode * n = NULL ): elementx( x ),elementy( y ), next( n ) { }
          ListNode(const Object & x , const Object & y,const Object & l1,const Object & r1,const Object & u1,const Object & d1,ListNode * n = NULL ): elementx( x ),elementy( y ),l(l1),r(r1),u(u1),d(d1), next( n ) { }
    };
  
  
    ListNode element; 
};

template <class Object>
class Stack
{
private:
    class List<int> *topOfList; 
 public:
    class List<int>::ListNode *topOfStack;
   Stack(int x,int y, int l, int r,int u, int d);
   Stack();
   Stack( const Stack & rhs );
   ~Stack( );
   void currentnodeupdate() ;
   List<int>::ListNode * currentnode( ) const;
   void pushStack( const Object & x );
   int currentx() const;
   int currenty() const;
   bool isEmpty( ) const;
   bool isFull( ) const;
   void makeEmpty( );
   void pop() ;
   void push( const Object & x , const Object & y);
   Object topAndPop( );
   const Object & top( ) const;
   const Stack & operator=( const Stack & rhs );
   friend class List<int>;

  };
#include "StackWithLL.cpp"
#endif
