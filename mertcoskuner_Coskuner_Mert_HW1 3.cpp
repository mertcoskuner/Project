//
//  main.cpp
//  mertcoskuner-the1
//
//  Created by Mert Coskuner on 7.10.2022.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;



bool FunctionForLHSAndCheck(ifstream &input, vector<vector<int>> &LHS1, vector<int> &LHS2,ofstream &output){
    string line;
    int row = 0, column = 0;
    getline(input, line);
    stringstream rowcolumn(line);
    int count = 0 ;
    while(count!=2){
        rowcolumn >> row;
        rowcolumn >> column;
        count++ ;
      }
    while(!input.eof())
      {
        
        getline(input, line);
        stringstream ss(line);
        int num;
        LHS2.clear();
        while(ss >> num)
      {
          if((1<= num <= 9) || num == -1){
              LHS2.push_back(num);

          }
          else{
              cout<<"Error"<<endl ;
              output <<"Error"<<endl ;
              return false;

          }
          
      }
          LHS1.push_back(LHS2);

      }
    
    if (LHS1.size() != row || LHS1[0].size() != column ){
        cout<<"Error"<<endl ;
        output <<"Error"<<endl ;

        return false;
    }
    return true;
}

bool  FunctionForRHSAndCheck(ifstream &input, vector<int> &RHS1,ofstream &output){
    string line ;
    int row = 0, column;
    getline(input,line) ;
    stringstream rowcolumn(line);
    int count=0 ;
    while(count!=2){
        rowcolumn >> row ;
        rowcolumn>>column ;
        count++ ;
    }
    while(!input.eof()){
        getline(input,line) ;
        stringstream ss(line) ;
        int num;
        while(ss>>num){
            int counter = 0 ;
            if((1<= num <= 9) || num == -1){
                RHS1.push_back(num);
                counter++ ;
                if(counter >=2) {
                    cout<<"Error"<<endl ;
                    output <<"Error"<<endl ;

                    return false;

                    break ;
                }
                
            }
            else{
                cout<<"Error"<<endl ;
                output <<"Error"<<endl ;

                return false;

                
            }
           
        }
       
    
    }
    if(row != RHS1.size()){
        cout<<"Error"<<endl ;
        output <<"Error"<<endl ;

        return false;
    }
    return true;
}



bool FunctionForRESAndCheck(ifstream &input, vector<int> &RES1,ofstream &output){
    string line ;
    int row = 0, column;
    getline(input,line) ;
    stringstream rowcolumn(line);
    int count=0 ;
    while(count!=2){
        rowcolumn >> row ;
        rowcolumn>>column ;
        count++ ;
    }
    
    while(!input.eof()){
        getline(input,line) ;
        stringstream ss(line) ;
        
        int num;
        while(ss>>num){
            int counter = 0 ;
            if(num>=1){
                RES1.push_back(num);
                counter++ ;
                if(counter >=2) {
                    cout<<"Error"<<endl ;
                    output <<"Error"<<endl ;

                    return false;

                    break ;
                }
                
            }
            else{
                cout<<"Error"<<endl ;
                output <<"Error"<<endl ;

                return false;

            }
        }
       
    }
    if(row != RES1.size()){
        cout<<"Error"<<endl ;
        output <<"Error"<<endl ;

        return false;
    }
    return 1;
}
void print(vector <int>  &places ,vector <int>  &places1,vector <int>  &numbers, ofstream &output) {

for(int i=0; i < places1.size(); i++){
    cout << places1.at(i) << " " << places.at(i)<< " " << numbers.at(i)<<endl ;
    output << places1.at(i) << " " << places.at(i)<< " " << numbers.at(i)<<endl ;

            }

}

bool optimizationfunc(int numbersize,int num1,vector<int> numbers, int res, vector<int> coeff ){
    if (numbersize == 0){
        return false ;
    }
    else{
        numbers.at(numbersize-1) = 9;
        int num=0 ;
        for(int l=0 ; l<coeff.size() ; l++){
            num += coeff[l] * numbers[l];
            
        }
        if(num >= res){
            return false ;
        }
        else{
            return true ;
        }
    }
    
}


void MatrixMultiplication(vector<vector<int>> LHS1,vector<int> RHS1,vector<int> RES1,ofstream &output){
    vector<int> coeff;
    vector<int> valuesforcoeff ;
    vector<int> places;
    vector<int> places1;

    

    for(int i=0 ; i< LHS1.size() ; i++){
     for(int j= 0 ; j< LHS1[0].size() ; j++){
         
         if(LHS1[i][j] == -1){
             coeff.push_back(RHS1[j]);
             places1.push_back(i);
             places.push_back(j);
         }
         else{
             RES1[i] -= (LHS1[i][j]* RHS1[j]) ;
         }
     }
        
            
            vector<int> numbers; // need to pushback 1's in order to use as a number for loop
            int num1=0;
           
            
            for(int k= 0; k< coeff.size()  ; k++){
                num1 += pow(10,k);
                numbers.push_back(1) ;
            }
        
            int max_power = pow(10,coeff.size())-1;
            int num ;

        
            int y;
           
            
            for(int n = num1 ; n<=max_power ; n++  ){
                while (optimizationfunc( numbers.size(), num1, numbers, RES1[i]  , coeff )&& numbers.at(coeff.size()-2) <10 && coeff.size()>0) {
                    
                    numbers.at(coeff.size()-2) += 1 ;
                    n+=10;
                }
                if(num == RES1[i]){
                    print(places ,places1,numbers, output);
                    numbers.clear();
                    places.clear();
                    places1.clear() ;
                    coeff.clear();
                    break;
                    }
                    y=0;    
                    
                    num = 0;
                    numbers.clear();
                    if(n % 10 == 0){
                        n=n+1;
                        
                    }
                    int num2= n ;
                    
                
                    while(num2>0)
                    {
                         
                        numbers.push_back(num2 % 10);
                        num2/=10;
                    }
                    reverse(numbers.begin(), numbers.end());
                    

                    for(int l=0 ; l<coeff.size() ; l++){
                        num += coeff[l] * numbers[l];
                        
                    }}
          }
        
          
        
    }
int main() {
    vector<vector<int>> LHS1 ;
    vector<int> LHS2;
    vector<int> RHS1;
    vector<int> RES1;
    string outfilename;
    ifstream input,input1,input2;
    ofstream output;
    string LHS,RHS,RES;
    cout<<"Enter LHS matrix filename: " ;
    cin >> LHS;
    input.open(LHS.c_str());
    
    cout<<"Enter RHS matrix filename: " ;
    cin>>RHS ;
    input1.open(RHS.c_str());
    
    cout<<"Enter RES matrix filename: " ;
    cin>>RES;
    input2.open(RES.c_str());
    
    cout<< "Enter output file name: ";
    cin>> outfilename;
    output.open(outfilename.c_str());

    if(input.fail()||input1.fail()||input2.fail()||output.fail()){
        cout << "Error"<< endl;
        output <<"Error"<<endl ;
        return 0;

    }
       //inputs/tc5/lhs.txt
    //inputs/tc5/rhs.txt
    //inputs/tc5/res.txt
    //output.txt
    
       
    if(FunctionForLHSAndCheck(input,  LHS1,  LHS2,output) == false ||FunctionForRHSAndCheck(input1,RHS1,output) == false||FunctionForRESAndCheck(input2,RES1,output) == false){
        return 0;
    }
    
    
   
    MatrixMultiplication( LHS1,RHS1,RES1, output);
 
    return 0 ;
    
}

