//
//  SUBook.h
//  SUBook
//
//  Created by Mert Coskuner on 11.12.2022.
//

#ifndef SUBook_h
#define SUBook_h

#include <iostream>
#include <vector>
using namespace std;
class User;
class Post;
class Comment;


class User{
private:
    string name;
    int num_comments=0 ;
    vector<Post*>  posts; // a list of all the posts created by the user
public:
    User(const string n): name(n){ }
    ~User();
    Post& createPost(string content);//creates a new Post object with the given content and adds it to the user's posts list. The function returns a reference to the created post.
    vector<Post*> getposts() ;//return a vector of pointers to the posts of the user
    int getNumComments();//returns the number of comments made by the user. If the user doesn’t have any comments yet, the function returns 0.
    string getName();//get the name of the user.
    friend class Post;
    friend class Comment;
};



class Post{
private:
    User & user ;
    string content ;
    vector<Comment*> comments;
public:
    Post(User& u,  string& c) : user(u), content(c){}
    ~Post();// delete all the comments
    void addComment(string content, User* commenter); // adds acomment by “commenter” with the content given
    vector<Comment*> getComments();  // get a vector of pointers at the comments on this post
    User& getUser() ;  //returns a reference to the user who made the post
    string getContent(); // return the text content of the post
friend class User;
friend class Comment;
    
};




class Comment{
private:
    User& user; //User that made the comment
    string content;
    Post& post;// the post that the comment is on
public:
    Comment(User& u, Post & p) : user(u), post(p){ }
    ~Comment() ;//A destructor that decrements the number of comments of the user that made this comment by 1
    User& getUser(); //  returns the user who made the comment
    string getContent(); //  returns the text content of the comment
    Post& getPost(); //  returns the post that this comment is on.
    friend class User;
    friend class Post;
};
#endif /* SUBook_h */
