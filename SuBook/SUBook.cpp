//
//  main.cpp
//  SUBook
//
//  Created by Mert Coskuner on 11.12.2022.
//

#include <iostream>
#include <vector>
#include "SUBook.h"


User::~User(){ //It will  delete the post storage vector
    for(int i = this->posts.size() - 1 ; i==0; i++){
        delete this->posts[i]->comments[i];
        delete this -> posts[i] ;
    }
}

Post& User::createPost(string content){//creates a new Post object with the given content and adds it to the user's posts list. The function returns a reference to the created post
    Post* new_post_ptr  = new Post(*this,content);
    (new_post_ptr->user.posts).push_back(new_post_ptr);
    return *new_post_ptr ;
}

vector<Post*> User::getposts(){//return a vector of pointers to the posts of the user
    return this->posts ;
}

int User:: getNumComments(){//returns the number of comments made by the user. If the user doesn’t have any comments yet, the function returns 0.
    return this->num_comments ; 
}

string User::getName(){
    return this->name;
}


Post:: ~Post(){
    for(int i = this->comments.size() - 1 ; i==0; i++){
        delete this -> comments[i] ;
    }
}


void Post::addComment(string content, User* commenter){// adds a comment by “commenter” with the content given
    commenter->num_comments+= 1;
    Comment* new_comment_ptr  = new Comment(*commenter,*this);
    new_comment_ptr->content= content;
    this->comments.push_back(new_comment_ptr);
}

vector<Comment*> Post::getComments(){ // get a vector of pointers at the commentson this post
    return this->comments;
}

User& Post:: getUser(){
    return this->user; 
}

string Post::getContent(){
    return this->content;
}


Comment:: ~Comment(){
    this->user.num_comments-=1;
}
User& Comment:: getUser(){
    return this->user;
}


string Comment:: getContent(){
    return this->content;
}

Post& Comment::getPost(){
    return this->post; 
}
