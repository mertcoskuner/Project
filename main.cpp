//Mert Coskuner 29120
#include<iostream>
#include "StackWithLL.h"
#include "randgen_Modified.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

Stack<int>  detectneighborandrand(int x, int y , int m, int n){
    Stack<int> st;
    if(x-1>=0 && y>=0){
        st.push(x-1,y);
    }
    if(x>=0 && y-1>=0){
        st.push(x,y-1);
    }
    if(x+1<n && y<m){
        st.push(x+1,y);
    }
    if(x<n && y+1<m){
        st.push(x,y+1);
    }
    return st; 
}
void stackcheck(Stack<int> &st, int x, int y){
    int counter = 0 ;
    Stack<int> newstack ;
    while(!st.isEmpty()){
        if((st.currentnode()->elementx == x) && (st.currentnode()->elementy == y)){
            counter++;
        }
        else{
            newstack.push(st.currentnode()->elementx,st.currentnode()->elementy);
            newstack.currentnode()->r=st.currentnode()->r;
            newstack.currentnode()->l=st.currentnode()->l;
            newstack.currentnode()->u=st.currentnode()->u;
            newstack.currentnode()->d=st.currentnode()->d;
        }
        st.pop();
    }
    st = newstack;
}
int sizecheck(Stack<int> st, int &size ){
    
    while(!st.isEmpty()){
        st.pop() ;
        size++;
    }
    return size;
}
void stackcheck2(Stack<int> st, Stack<int> &st2){
    Stack<int> newstack ;
    List<int>::ListNode *topOfStack2 = st.currentnode();
    int size =0 ;
    while((st.currentnode()->next !=NULL) && (!st2.isEmpty())){
        if((st.currentnode()->elementx == st2.currentnode()->elementx) && (st.currentnode()->elementy == st2.currentnode()->elementy)){
            st2.pop();
            size++;
            st.topOfStack = topOfStack2 ;
        }
        else{
            
            st.currentnodeupdate();
        }
        if((st.currentnode()->next !=NULL) && size != sizecheck(st2, size) ){
            size++;
            newstack.push(st2.currentx(),st2.currenty());
            st2.pop();
            st.topOfStack = topOfStack2 ;
        }
        else if((st.currentnode()->next !=NULL) && size == sizecheck(st2, size) ){
            while(!newstack.isEmpty()){
                st2.push(newstack.currentx(),newstack.currenty());
                newstack.pop();
            }
            break;
        }
    }
}
void wallgeneration(Stack<int> &st, Stack<int> neighbor ){
    Stack<int> newStack ;
    int wallvarx=(st.currentnode()->elementx)-(neighbor.currentnode()->elementx) ;
    int wallvary=(st.currentnode()->elementy)-(neighbor.currentnode()->elementy);

    if(wallvarx == -1 && wallvary == 0 ){
        st.currentnode()->r=0;
        st.currentnode()->l=1;
        st.currentnode()->u=1;
        st.currentnode()->d=1;
    }
    else if(wallvarx == 0 && wallvary == 1 ){
        st.currentnode()->r=1;
        st.currentnode()->l=1;
        st.currentnode()->u=1;
        st.currentnode()->d=0;
    }
    else if(wallvarx == 1 && wallvary == 0 ){
        st.currentnode()->r=1;
        st.currentnode()->l=0;
        st.currentnode()->u=1;
        st.currentnode()->d=1;
    }
    else if(wallvarx == 0 && wallvary == -1 ){
        st.currentnode()->r=1;
        st.currentnode()->l=1;
        st.currentnode()->u=0;
        st.currentnode()->d=1;
    }
    
   newStack =st;
    while(!newStack.isEmpty()){
        if((newStack.currentnode()->elementx == st.currentnode()->elementx) && (newStack.currentnode()->elementy == st.currentnode()->elementy-1)){
            if(newStack.currentnode()->u==0){
                st.currentnode()->d=0;
            }
            
        }
        if((newStack.currentnode()->elementx == st.currentnode()->elementx) && (newStack.currentnode()->elementy == st.currentnode()->elementy+1)){
            if(newStack.currentnode()->d==0){
                st.currentnode()->u=0;
            }
            
        }
        if((newStack.currentnode()->elementx == st.currentnode()->elementx-1) && (newStack.currentnode()->elementy == st.currentnode()->elementy)){
            if(newStack.currentnode()->r==0){
                st.currentnode()->l=0;
            }
            
        }
        
        if((newStack.currentnode()->elementx == st.currentnode()->elementx+1) && (newStack.currentnode()->elementy == st.currentnode()->elementy)){
            if(newStack.currentnode()->l==0){
                st.currentnode()->r=0;
            }
            }            newStack.pop();

    }
}


int sizecheck2(Stack<Stack<int>> st, int &size ){
    
    while(!st.isEmpty()){
        st.pop() ;
        size++;
    }
    return size;
}

void control(Stack<int>st, Stack<int>& neighbor ){
    Stack<int> stnew = st;
    
    while(!stnew.isEmpty()){
        stackcheck(neighbor, stnew.currentx(), stnew.currenty());
        stnew.pop();
    }
}
void forlast(Stack<int> newStack,Stack<int> &st,int &l,int &r,int &u,int &d){
    l=1;
    r=1;
    u=1;
    d=1;
    wallgeneration(st, newStack );
 
}
void backtrackwall(Stack<int> &st, int currentxst , int currentyst , int neighborx, int neighbory){
    if((currentxst == neighborx) && (currentyst == neighbory-1)){
        st.currentnode()->u=0;
    }
    if((currentxst == neighborx) && (currentyst == neighbory+1)){
        st.currentnode()->d=0;
    }
    if((currentxst == neighborx-1) && (currentyst == neighbory)){
        st.currentnode()->r=0;
    }
    if((currentxst == neighborx+1) && (currentyst == neighbory)){
        st.currentnode()->l=0;
    }
}
void backtrack(Stack<int> &st, Stack<int> &neighbor,int m, int n,bool &x){
    Stack<int>  previouslyvisited ;
    
    forlast(st,st,st.currentnode()->l,st.currentnode()->r,st.currentnode()->u,st.currentnode()->d);
    while(neighbor.isEmpty()){
        previouslyvisited.push(st.currentnode()->elementx, st.currentnode()->elementy);
        previouslyvisited.currentnode()->r=st.currentnode()->r;
        previouslyvisited.currentnode()->l=st.currentnode()->l;
        previouslyvisited.currentnode()->u=st.currentnode()->u;
        previouslyvisited.currentnode()->d=st.currentnode()->d;
        st.pop();
        neighbor = detectneighborandrand(st.currentx(),st.currenty(),m,n);
        control(st, neighbor );
        control(previouslyvisited, neighbor );
        if(st.currentx() == 0 && st.currenty() == 0){
            x=false ;
            break;
        }
    }
    if(!(st.currentx() == 0 && st.currenty() == 0)){
        backtrackwall(st, st.currentx() , st.currenty(), neighbor.currentx(), neighbor.currenty());
    }

    while(!previouslyvisited.isEmpty()){
        st.push(previouslyvisited.currentnode()->elementx, previouslyvisited.currentnode()->elementy);
        st.currentnode()->r=previouslyvisited.currentnode()->r;
        st.currentnode()->l=previouslyvisited.currentnode()->l;
        st.currentnode()->u=previouslyvisited.currentnode()->u;
        st.currentnode()->d=previouslyvisited.currentnode()->d;
        previouslyvisited.pop();
    }
}
bool stackcheck3(Stack<int> st, int y, int x,int &l, int &r,int &u, int &d){
    while(!st.isEmpty()){
        if((st.currentnode()->elementx == x) && (st.currentnode()->elementy == y)){
            r = st.currentnode()->r;
            l = st.currentnode()->l;
            u = st.currentnode()->u;
            d = st.currentnode()->d;
            return true ;
        }
        st.pop();
    }
    return false;
}

void MazeGen2(int m, int n, Stack<int> st,int i){
    Stack<int> orderedStack;
    int l=1,r=1,u=1,d=1;
    for(int i = 0 ; i<m; i++){//y
        for(int j =0 ; j<n ; j++){//x
            if(stackcheck3(st,i,j,l,r,u,d)){
                orderedStack.push(j,i);
                orderedStack.currentnode()->r = r;
                orderedStack.currentnode()->l = l;
                orderedStack.currentnode()->u = u;
                orderedStack.currentnode()->d = d;
            }

        }
    }
    
    Stack<int> newStack2 ;
    int x = sizecheck(orderedStack, x) ;
    while(!orderedStack.isEmpty() ){
        newStack2.push(orderedStack.currentx(), orderedStack.currenty());
        newStack2.currentnode()->r=orderedStack.currentnode()->r;
        newStack2.currentnode()->l=orderedStack.currentnode()->l;
        newStack2.currentnode()->u=orderedStack.currentnode()->u;
        newStack2.currentnode()->d=orderedStack.currentnode()->d;
        orderedStack.pop();
    }
    string outfilename ="maze"+to_string(i)+".txt";
    ofstream output;
    output.open(outfilename.c_str());
    output<<m<<" "<<n<<endl;
    while(!newStack2.isEmpty()){
        output << "x="<<newStack2.currentx() <<" y="<<newStack2.currenty() << " l=" <<newStack2.currentnode()->l <<" r=" << newStack2.currentnode()->r<< " u="<<newStack2.currentnode()->u<< " d=" <<newStack2.currentnode()->d<<endl;
        newStack2.pop();
    }
}
void copy(Stack<int> st ,int x, int y, int &l , int &r, int &u, int &d ){
    
    while(!st.isEmpty()){
        if(st.currentx() == x && st.currenty() == y ){
            break;
        }
        else{
            st.pop();
        }
    }
    l = st.currentnode()->l;
    r = st.currentnode()->r;
    u = st.currentnode()->u;
    d = st.currentnode()->d;
}

void totalwallcheck(Stack<int> &st,Stack<int> newStack ){
    while(!newStack.isEmpty()){
        if((newStack.currentnode()->elementx == st.currentnode()->elementx) && (newStack.currentnode()->elementy == st.currentnode()->elementy-1)){
            if(newStack.currentnode()->u==0){
                st.currentnode()->d=0;
            }
            
        }
        if((newStack.currentnode()->elementx == st.currentnode()->elementx) && (newStack.currentnode()->elementy == st.currentnode()->elementy+1)){
            if(newStack.currentnode()->d==0){
                st.currentnode()->u=0;
            }
            
        }
        if((newStack.currentnode()->elementx == st.currentnode()->elementx-1) && (newStack.currentnode()->elementy == st.currentnode()->elementy)){
            if(newStack.currentnode()->r==0){
                st.currentnode()->l=0;
            }
            
        }
        
        if((newStack.currentnode()->elementx == st.currentnode()->elementx+1) && (newStack.currentnode()->elementy == st.currentnode()->elementy)){
            if(newStack.currentnode()->l==0){
                st.currentnode()->r=0;
            }
            }            newStack.pop();

    }

}


Stack<int> MazeGen(int m, int n, vector<Stack<int>> &stackholder ){
    Stack<int> st;
    RandGen randint;
    st.push(0,0);
    bool a = true;
    int size =0 ;
    while(a == true  ){
        Stack<int> neighbor = detectneighborandrand(st.currentx(),st.currenty(),m,n);
        control(st,  neighbor );
        Stack<int> neighbor1 ;

        if(!neighbor.isEmpty()){
            size = sizecheck(neighbor,size);
            int x = randint.RandInt(0,size-1);
            if(x==size-1 ){
                x = 0 ;
            }
            while(x!=0){//Randomly generating the path of the maze
                neighbor1.push(neighbor.currentnode()->elementx,neighbor.currentnode()->elementy);
                neighbor.pop() ;
                x--;
            }
        }
        //if no wall exists we need to backtrack
        if(neighbor.isEmpty()){
            backtrack(st,neighbor,m,n, a);
        }
        if(a!= false){
            wallgeneration(st,neighbor );
            st.push(neighbor.currentnode()->elementx,neighbor.currentnode()->elementy );
            neighbor.makeEmpty();
            neighbor1.makeEmpty();
            size =0 ;
        }
        if(st.currentx() == 0 && st.currenty() == 0){
            a=false ;
            break;
        }
    }
    totalwallcheck(st,st);
     return st;
}
void finderu(Stack<int> st, int x,int y,int &u){
    while(!st.isEmpty()){
        if(st.currentx() == x && st.currenty() == y ){
            u= st.currentnode()->u;
            break;
        }
        else{
            st.pop();
        }
    }
}
void finderd(Stack<int> st, int x,int y,int &d){
    while(!st.isEmpty()){
        if(st.currentx() == x && st.currenty() == y ){
            d= st.currentnode()->d;

            break;
        }
        else{
            st.pop();
        }
    }
    
}
Stack<int> detectneighborsforpathgen(Stack<int> st ,int x, int y,  int m, int n){
    Stack<int> neighbor;
    Stack<int> st2 =st;
    Stack<int> st3 =st;
    while(!st.isEmpty()){
        if(st.currentx() == x && st.currenty() == y ){
            break;
        }
        else{
            st.pop();
        }
    }
    if(st.currentnode()->l==0){
        neighbor.push(st.currentx()-1, st.currenty());
        copy(st2 ,neighbor.currentx(), neighbor.currenty(), neighbor.currentnode()->l , neighbor.currentnode()->r, neighbor.currentnode()->u, neighbor.currentnode()->d );
    }
    if(st.currentnode()->r==0){
        neighbor.push(st.currentx()+1, st.currenty());
        copy(st2 ,neighbor.currentx(), neighbor.currenty(), neighbor.currentnode()->l , neighbor.currentnode()->r, neighbor.currentnode()->u, neighbor.currentnode()->d );
    }int u ;finderd(st3,st.currentx(), st.currenty()+1,u);
    if(st.currentnode()->u==0&& (u==0) ){
        neighbor.push(st.currentx(), st.currenty()+1);
        copy(st2 ,neighbor.currentx(), neighbor.currenty(), neighbor.currentnode()->l , neighbor.currentnode()->r, neighbor.currentnode()->u, neighbor.currentnode()->d );
    }int d ;finderu(st3,st.currentx(), st.currenty()-1,d);
    if(st.currentnode()->d==0&& d==0 ){
        neighbor.push(st.currentx(), st.currenty()-1);
        copy(st2 ,neighbor.currentx(), neighbor.currenty(), neighbor.currentnode()->l , neighbor.currentnode()->r, neighbor.currentnode()->u, neighbor.currentnode()->d );
    }
    return neighbor;
}

void detectneighborsforpathgen2(Stack<int> st ,Stack<int> &stk,  int m, int n){
    Stack<int> neighbor;
    Stack<int> st2 =st;
    Stack<int> st3 =st;
    while(!st.isEmpty()){
        if(st.currentx() == stk.currentx() && st.currenty() == stk.currenty() ){
            break;
        }
        else{
            st.pop();
        }
    }
    stk.currentnode()->r = st.currentnode()->r;
    stk.currentnode()->l =st.currentnode()->l;
    stk.currentnode()->u= st.currentnode()->u;
    stk.currentnode()->d=st.currentnode()->d;

}
void stackcheckforpath(Stack<int> &st, int x, int y){
    int counter = 0 ;
    Stack<int> newstack ;
    while(!st.isEmpty()){
        if((st.currentnode()->elementx == x) && (st.currentnode()->elementy == y)){
            counter++;
        }
        else{
            newstack.push(st.currentnode()->elementx,st.currentnode()->elementy);
        }
        st.pop();
    }
    st = newstack;
}
void backtrackforpathgen(Stack<int> &st, Stack<int> &neighbor, Stack<int> stx, int m, int n,bool &x,int exitx, int exity, int enterx,int entery,Stack<int> &prevvisit){

    Stack<int>  previouslyvisited ;
    
    while(neighbor.isEmpty()){
        previouslyvisited.push(st.currentnode()->elementx, st.currentnode()->elementy);
        previouslyvisited.currentnode()->r=st.currentnode()->r;
        previouslyvisited.currentnode()->l=st.currentnode()->l;
        previouslyvisited.currentnode()->u=st.currentnode()->u;
        previouslyvisited.currentnode()->d=st.currentnode()->d;
        if(!(st.currentx() == enterx && st.currenty() == entery)){
            st.pop();
            neighbor = detectneighborsforpathgen( stx , st.currentx(),  st.currenty(),   m,  n);
            control(st, neighbor );
            control(previouslyvisited, neighbor );
            control(prevvisit, neighbor );
            if(st.currentx() == exitx && st.currenty() == exity){
                x=false ;
                break;
            }}
        else{
            x=false ;
        }
        
    }
    while(!previouslyvisited.isEmpty()){
        prevvisit.push(previouslyvisited.currentnode()->elementx, previouslyvisited.currentnode()->elementy);
        prevvisit.currentnode()->r=previouslyvisited.currentnode()->r;
        prevvisit.currentnode()->l=previouslyvisited.currentnode()->l;
        prevvisit.currentnode()->u=previouslyvisited.currentnode()->u;
        prevvisit.currentnode()->d=previouslyvisited.currentnode()->d;
        previouslyvisited.pop();
    }
}

Stack<int> PathGen(int Id,int enterx,int entery, int exitx, int exity,vector<Stack<int>> stackholder,int m ,int n){
    Stack<int> generatedPath;
    RandGen randint;
    generatedPath.push(enterx, entery);
    detectneighborsforpathgen2(stackholder[Id-1] ,generatedPath,m,  n);
    Stack<int>prevvisit;
    Stack<int> neighbor;
    Stack<int> neighbor1 ;
    Stack<int> st= stackholder[Id-1];
    bool a = true;
    int size =0;
    while(a == true  ){
        neighbor = detectneighborsforpathgen(stackholder[Id-1] , generatedPath.currentx(),  generatedPath.currenty() ,   m,  n);
        control(generatedPath,neighbor );
        if(!neighbor.isEmpty()){
            size = sizecheck(neighbor,size);
            int x = randint.RandInt(0,size-1);
            if(x==size-1 ){
                x = 0 ;
            }
            
            while(x!=0){//Randomly generating the path of the maze
                neighbor1.push(neighbor.currentnode()->elementx,neighbor.currentnode()->elementy);
                neighbor.pop() ;
                x--;
            }
        }
      
        if(neighbor.isEmpty()){
            backtrackforpathgen(generatedPath,neighbor,stackholder[Id-1],m,n,a,exitx,exity,enterx,entery,prevvisit);
        }
        
        if(a!= false){
            generatedPath.push(neighbor.currentnode()->elementx,neighbor.currentnode()->elementy );
            generatedPath.currentnode()->r=neighbor.currentnode()->r;
            generatedPath.currentnode()->l=neighbor.currentnode()->l;
            generatedPath.currentnode()->u=neighbor.currentnode()->u;
            generatedPath.currentnode()->d=neighbor.currentnode()->d;
            neighbor.makeEmpty();
            neighbor1.makeEmpty();
            size =0 ;
        }
        if(generatedPath.currentx() == exitx && generatedPath.currenty() == exity){
            a=false ;
            break;
        }
        
        
    }


    Stack<int>orderedStack =  generatedPath;
    Stack<int> newStack2 ;
    while(!orderedStack.isEmpty() ){
        newStack2.push(orderedStack.currentnode()->elementx, orderedStack.currenty());
        newStack2.currentnode()->r=orderedStack.currentnode()->r;
        newStack2.currentnode()->l=orderedStack.currentnode()->l;
        newStack2.currentnode()->u=orderedStack.currentnode()->u;
        newStack2.currentnode()->d=orderedStack.currentnode()->d;
        orderedStack.pop();
    }
    string outfilename ="maze_"+to_string(Id)+"_path_"+to_string(enterx)+"_"+to_string(entery)+"_"+to_string(exitx)+"_"+to_string(exity)+".txt";
    ofstream output;
    output.open(outfilename.c_str());
    while(!newStack2.isEmpty()){
        output<<newStack2.currentx()<<" "<<newStack2.currenty() <<endl;
        newStack2.pop();
    }
    return generatedPath;
}



int main(){
    int K,M,N, mazeId;
    int enterx,entery,exitx,exity;
    vector<Stack<int>>stackholder;
    cout<<"Enter the number of mazes: "<<endl ;
    cin>> K;
    cout<<"Enter the number of rows and columns (M and N): "<<endl ;
    cin>> M >> N;
    for(int i=0; i< K ; i++){
        stackholder.push_back(MazeGen( M,  N, stackholder ));
    }
    for(int i=0; i< K ; i++){
        MazeGen2( M,  N, stackholder[i],i);
    }
    cout<<"All mazes are generated."<<endl;
    cout<<endl;
    cout<<"Enter a maze ID between 1 to 5 inclusive to find a path: "<<endl ;
    cin>>mazeId;
    cout<<"Enter x and y coordinates of the entry points (x,y) or (column,row): "<<endl;
    cin>>enterx>>entery;
    cout<<"Enter x and y coordinates of the exit points (x,y) or (column,row): " <<endl;
    cin>>exitx>> exity;
    PathGen(mazeId,enterx,entery,exitx,exity,stackholder,M,N);
    return 0;
}
