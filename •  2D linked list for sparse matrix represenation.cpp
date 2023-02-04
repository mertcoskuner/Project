//
//  mertcoskuner-HW2
//
//   Mert Coskuner 29120
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include "sparse_matrix_2d_linked_list.h"
using namespace std;



cell_node* cell_node_initialize (cell_node* head,int column_count, int numb){
    head = new cell_node();
    head->column =column_count-1 ;
    head -> value = numb ;
    head-> left =NULL;
    head-> right =NULL;
    return head;
}
void cell_node_add_function(cell_node* head,int column_count, int numb){
    while(head-> right != NULL){
        head = head ->right;
    }

    head-> right = new cell_node();
    head-> right->column =column_count-1 ;
    head-> right -> value = numb ;
    head-> right-> right =NULL;
    head-> right-> left = head ;
   
}
row_node* last_row_node_erase(row_node* head){
    row_node* templast =head ;
    row_node* templast1 = NULL;
    
    while(templast-> down != NULL){
        templast1 =templast ;
        templast = templast->down;
    }
    templast1 ->down  = NULL ;
    free(templast);
    return head;
}
cell_node* last_cell_node_erase(cell_node* head){
    cell_node* templast =head ;
    cell_node* templast1 = NULL;
    
    while(templast-> right != NULL){
        templast1 =templast ;
        templast = templast->right;
    }
    templast1 ->right  = NULL ;
    free(templast);
    return head;
}
row_node* read_matrix(const string& filename, int& num_rows, int& num_columns){
    ifstream input ;
    string matline;
    int counter = 0 ,rowNumber = 0,columnNumber = 0;
    input.open(filename.c_str());
    if(input.fail()){
        cout << "Error"<< endl;}
    getline(input, matline);
    stringstream rowcolumn(matline);
    while(counter!=2){// getting the information of column numbers and row numbers
        rowcolumn >> rowNumber;
        counter++;
        rowcolumn >> columnNumber;
        counter++;
    }
    num_rows = rowNumber;
    num_columns= columnNumber;
    
    row_node* head_row_node = nullptr; //Starting to create the linked list
    cell_node* head_cell_node = nullptr ;
    cell_node* new_cell_node = new cell_node();
    cell_node* tempx= nullptr;
    while(!input.eof() ){
        getline(input, matline);
        stringstream ss(matline);
        int numb;
        int column_count =0;
        if(matline.empty() ){
            break;
        }
        while(ss>>numb){//reading the file number by number
            column_count++;
            if(-9<=numb<=9 && numb != 0){
                if(head_row_node == NULL){//checking if the head row is initialized
                    head_row_node = new row_node();
                    if(head_cell_node ==NULL){
                        head_cell_node = cell_node_initialize(head_cell_node, column_count,  numb);
                    }
                    head_row_node->cell = head_cell_node ;
                }
                else if(head_row_node != NULL && head_row_node ->down != NULL){
                    row_node* temp1 =head_row_node ;
                    while(temp1-> down != NULL){
                        temp1 = temp1 ->down;
                    }
                    if(temp1 ->cell  ==  NULL){
                        if(tempx ==NULL){
                            tempx = cell_node_initialize(tempx, column_count,  numb);
                        }
                    }
                    else{
                        cell_node* tempy = tempx ;
                        cell_node_add_function(tempy,column_count, numb);
                    }
                    temp1->cell = tempx ;
                }
                else{
                    cell_node* temp = head_cell_node ;
                    cell_node_add_function(temp,column_count, numb);
                }
            }
            }
        
        row_node* temp2 =head_row_node ;
        while(temp2-> down != NULL){// adding new row node
            temp2 = temp2 ->down;
        }
        temp2-> down = new row_node();
        tempx= nullptr;
        
        }
    
  return last_row_node_erase(head_row_node);
}





void print_matrix(row_node* head, int num_rows, int num_cols){ //prints row by row
    row_node* tempo = head;
    cell_node* tempo1 = head->cell;
    int columnCheck = 0; // column check for all the variables(including 0)
    int columnCheckForVar = 0 ; // column check for all the variables(not including 0)

    while(tempo->down  != NULL ||tempo->down  == NULL ){
        if(tempo->cell == NULL){ //for the last cell
            for(int i =0 ; i<num_cols; i++){
                cout<<"0"<<" " ;
            }
            if(tempo->down  == NULL){
                cout<<endl;
                break ;
            }
            else{
                columnCheck =0  ;
                columnCheckForVar = 0;
                cout<<endl;
                tempo = tempo ->down ;
                tempo1 = tempo->cell ;
                
            }
            
        }
        else{
        while(tempo1 -> right != NULL ||tempo1 -> right == NULL){
            columnCheck++;
            if(tempo1-> column ==columnCheck-1 ){
                cout<<tempo1->value<<" ";
                columnCheckForVar++;
                
            }
            else{
                while((tempo1->column)+1-columnCheck != 0){
                    cout<<"0"<<" " ;
                    columnCheck++;
                }
                
                cout<<tempo1->value<<" ";
                columnCheckForVar++;

            }
            
            if(tempo1->right  == NULL){
                for(int i =0 ; i< num_cols- (tempo1->column+1); i++){//checking the column value of the index if there is a gap print 0
                    cout<<"0"<<" " ;
                    columnCheck++;

                }
                break ;
            }
            else{
                tempo1 = tempo1 ->right;
                
            }
          
            
        }
        
        if((columnCheck) != num_cols){//last check if there are zero's at the end check the column number and print 0's
            for(int j =0 ; j<num_cols-columnCheck ; j++ ){
                cout<< "0"<< " ";
            }
        }
        if(tempo->down  == NULL){
            cout<<endl;
            break ;
        }
        else{
            columnCheck =0  ;
            columnCheckForVar = 0;
            cout<<endl;//for next line
            tempo = tempo ->down ;
            tempo1 = tempo->cell ;
            
        }
      
    }
    }

}
void delete_matrix_func(cell_node* last,cell_node* last1){ // for simplyfy the main delete function
    while(last != NULL){
        while(last-> right != NULL){// deleting cell nodes starting by last
            last1 =last ;
            last = last->right;
        }
        if(last-> right == NULL){
            last = NULL;
            free(last);
        }
        else{
            last1 ->right  = NULL ;

        }
    }
}
void delete_matrix(row_node* head){

    while(head !=NULL){//deleting row by row
            row_node* fhead =head ;
            row_node* fhead1 = NULL;
            cell_node* last1 = NULL;
            if(fhead-> down == NULL){//checking if it is in  the last index
                cell_node* last = fhead->cell;
                head = NULL;
                free(head);
                delete_matrix_func( last, last1);

                
            }
            else{
                while(fhead-> down != NULL){
                    fhead1 =fhead ;
                    fhead = fhead->down;
                }
                cell_node* last = fhead->cell;
                delete_matrix_func(last,last1);
                fhead1 ->down  = NULL ;
                free(fhead);
            
                
            }
    }

}

int cell_index_return(row_node* head, int row_number, int column_number ){//returns the given index in linked list if there is not returns 0
    cell_node* temp  =NULL;
    row_node* temp1 = head;
    for(int i = 0 ; i< row_number; i++){
        temp1 = temp1->down;
    }
    temp =  temp1-> cell;
    if(temp1->cell ==NULL){
        return 0;

    }
    while(temp-> right != NULL ||temp-> right ==NULL ){
        if(temp -> column  == column_number ){
            return temp->value;
        }
        if(temp-> right ==NULL ||temp ==NULL){
            break ;
        }
        else{
            temp = temp -> right;
        }
    }
    return 0;
}


bool is_symmetric(row_node* head, int num_rows, int num_columns){
    row_node* tempForHead= head;
    cell_node* tempForHeadCell = head->cell ;
    int row_count = 0 ;

    if(num_rows != num_columns){ //At first, check if it is square
           return false;
       }
    else{
        while (tempForHead -> down != NULL || tempForHead -> down == NULL){ //reading the matrix in order with respect to the column and row vaşues
            row_count++;
            while(tempForHeadCell-> right != NULL || tempForHeadCell-> right == NULL){//because we are reading in order we know the row number and column number
                if(cell_index_return(head, tempForHeadCell->column,row_count-1) == 0 ){//check the specific index for the symmetric by changing the values of row and column
                    return false;

                }
                else if(tempForHeadCell->value != cell_index_return(head, tempForHeadCell->column,row_count-1) ){
                    return false;
                }
                if(tempForHeadCell-> right == NULL){
                    break;
                }
                else{
                    tempForHeadCell = tempForHeadCell -> right;

                }
            }

            if(tempForHead -> down  == NULL){
                break;
            }
            else{
                tempForHead = tempForHead -> down ;
                tempForHeadCell = tempForHead -> cell ;
            }
            
        }
        
        
    }
    return true;
}



row_node* transpose_add(row_node* head , int num_row, int num_column, cell_node* x,int value,int column_number ){
    //adding nodes to the transpose matrix
    //transpose node cell node and row node are changed
    row_node* temp = head ;
    for(int i =0 ; i< num_column ; i++){
        temp = temp-> down;
    }
    if(temp->cell == NULL){//initializing transpose cell node
    cell_node* head_cell_node = new cell_node();
    temp-> cell = head_cell_node    ;
    head_cell_node-> value = value;
    head_cell_node -> column = num_row ;
    if(num_row < column_number){
        head_cell_node-> right = new cell_node() ;
        }

   

}
    else{
        cell_node* temp1  =temp->cell;
        while(temp1 -> right != NULL){
            temp1 = temp1 -> right ;
        }
        temp1-> value = value;
        temp1 -> column = num_row ;
        if(num_row < column_number){
            temp1-> right = new cell_node() ;

        }
        
    }
   
    


    return head;
}

row_node* transpose_clean(row_node* head){ //cleaning in the tranpose matrices each row's cell linked list's last index
    row_node* temp_transpose = head;
     
      while(temp_transpose != NULL){
          
          cell_node* templast =temp_transpose->cell ;
          cell_node* templast1 = NULL;
          if(templast== NULL){
              temp_transpose = temp_transpose ->down ;

          }
          else {
              while(templast-> right != NULL){
                  templast1 =templast ;
                  templast = templast->right;
              }
              templast1 ->right   = NULL ;
              free(templast);
              temp_transpose = temp_transpose ->down ;

              
          }
          
          
          
          
      }
    return head;
}

row_node* transpose(row_node* head, int num_row, int num_columns){
    //if it is symmetric no need to do the operation
    //else
    row_node* tempForHead= head;
    cell_node* tempForHeadCell = head->cell ;
    
    row_node* transpose_head  = new row_node() ;
    cell_node* transpose_head_cell = new cell_node() ;
    row_node* temp_transpose_head = transpose_head;
    
    for(int i= 0 ; i< num_columns ; i++){ //creating new row nodes for transpose matrix
        if(i==0){
            temp_transpose_head-> down  = new row_node() ;

        }
        else{
            while(temp_transpose_head->down != NULL){
                temp_transpose_head = temp_transpose_head -> down ;
            }
            temp_transpose_head-> down  = new row_node() ;

        }
        
    }
    row_node* templast =transpose_head ;
    row_node* templast1 = NULL;
    
    while(templast-> down != NULL){
        templast1 =templast ;
        templast = templast->down;
    }
    templast1 ->down  = NULL ;
    free(templast);
    int row_count = 0 ;
    int column_count = 0 ;
    if(is_symmetric(head, num_row, num_columns)){ //if it is symmetric no need to do the operation
        return head;
    }
    else{//we are adding in an order row by row always the ordered index in the cell nodes
        while((tempForHead-> down != NULL|| tempForHead-> down == NULL)&&(tempForHead->cell != NULL)){
            row_count++;
            while(tempForHeadCell -> right != NULL || tempForHeadCell -> right == NULL){
                column_count++;
                
                if(tempForHeadCell -> right == NULL){
                   
                    transpose_add(transpose_head, row_count-1, tempForHeadCell->column , tempForHeadCell, tempForHeadCell->value,num_row);
                    break ;

                }
                else{
                    transpose_add(transpose_head, row_count-1, tempForHeadCell->column  , tempForHeadCell, tempForHeadCell->value,num_row);
                    tempForHeadCell =tempForHeadCell->right;
                    
                }
            }
            column_count=0;
            if(tempForHead-> down == NULL){
                break ;
            }
            else{
                tempForHead = tempForHead->down ;
                tempForHeadCell = tempForHead ->cell ;

            }
        }
        ;
        return transpose_clean(transpose_head);
    }
    
    
    
    
    
    
}
void add_matrices_func(cell_node* head,cell_node* side){ // just for simplifying the add_matrices function
    //same operations
    head->value = side->value ;
    head->column = side->column;
    head->right =new cell_node();

}

row_node* add_matrices(row_node* lhs, row_node* rhs, int num_rows, int num_cols){
 //cannot simplify too much the function because there are to many adresses
    row_node* head  =new row_node();
    cell_node* head1 =nullptr;
    
    cell_node* lhs1 = lhs -> cell;
    cell_node* rhs1 = rhs -> cell ;
    row_node* temp1 = head;
    cell_node* temp = head1;
    row_node* temp3 = temp1;

    while(lhs-> down != NULL || lhs-> down == NULL){
        while(lhs1->right!=NULL||lhs1->right==NULL){
            if(rhs!=NULL && rhs->cell == NULL){
                if(head1 == NULL){
                    head1 = new cell_node();
             
                    add_matrices_func( head1, lhs1);
                    lhs1 = lhs1->right;

                }
                else{
                    
                    add_matrices_func( temp, lhs1);
                    lhs1 = lhs1->right;

                    
                }
            }
            else if (lhs!=NULL && lhs->cell == NULL){
                if(head1 == NULL){
                    head1 = new cell_node();
             
                    
                    add_matrices_func( head1, rhs1);
                    rhs1 = rhs1->right;

                }
                else{
                  
                    add_matrices_func( temp, rhs1);

                    rhs1 = rhs1->right;
               

                    
                }
            }
             else if(rhs1->column == lhs1->column && (rhs->cell != NULL || lhs->cell !=NULL)){// if column values are equal add them
                    if(head1 == NULL){
                        head1 = new cell_node();
                        head1->value =rhs1->value +lhs1->value;
                        head1->column = rhs1->column;
                        lhs1 = lhs1->right;
                        rhs1= rhs1-> right;
                        head1->right =new cell_node();

                        
                    }
                    else{
                        temp->value =rhs1->value +lhs1->value;
                        temp ->column = rhs1->column;
                        lhs1 = lhs1->right;
                        rhs1= rhs1-> right;
                        temp->right =new cell_node();

                        
                        
                    }
                    
                }
                else if(rhs1->column > lhs1->column && (rhs->cell != NULL || lhs->cell !=NULL)){//checking the column values if it is smaller than add
                    if(head1 == NULL){
                        head1 = new cell_node();
                 
                        
                        add_matrices_func( head1, lhs1);

                        lhs1 = lhs1->right;

                    }
                    else{
                      
                        add_matrices_func( temp, lhs1);
                        lhs1 = lhs1->right;

                        
                    }
                }
                else if(rhs1->column < lhs1->column && (rhs->cell != NULL || lhs->cell !=NULL)){//checking the column values if it is smaller than add
                    if(head1 == NULL){
                        head1 = new cell_node();
                 
                   
                        add_matrices_func( head1, rhs1);

                        rhs1 = rhs1->right;

                    }
                    else{
                      
                        add_matrices_func( temp, rhs1);
                        rhs1 = rhs1->right;

                        
                    }
                }
            temp = head1;
            

            while(temp->right !=NULL){
                temp =temp ->right;
            }
            if(rhs1== NULL && lhs1 ==NULL){
                break ;
            }
            }

        last_cell_node_erase( head1);//erase the unused node
       
        
        while(temp1->down !=NULL){
            temp1 =temp1 ->down;
                }
        temp1->cell  = head1;
        temp1 ->down  = new row_node();
        temp1 = head -> down  ;
        head1 = nullptr;
        if(lhs->down  == NULL || rhs->down == NULL){
            break ;
        }
        else{
            lhs =lhs->down;
            rhs = rhs->down;
            lhs1 = lhs -> cell;
            rhs1 = rhs -> cell ;
        }
        
    }
    last_row_node_erase( head);//erase the unused node

   

    return  head;
}

