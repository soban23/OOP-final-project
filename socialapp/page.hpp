#include <iostream>
using namespace std;

class page{

private:
  string id;
  string title;  
  int total_likes;
public:
  page(){
    id="";
    title="";
    total_likes=0;
  }
 
  void increment_likes(int l=1){
    total_likes+=l;
  }
  void decrement_likes(int l=1){
    total_likes-=l;
  }
  void set_id(string i){
    id=i;
  }
  void set_title(string t){
    title=t;
  }
  void set_likes(int l){
    total_likes=l;
  }
  string get_id(){
    return id;
  }
  string get_title(){
    return title;

  }
  int get_likes(){
    return total_likes;
  }
  void print(){
    cout<<"Page ID: "<<id<<endl;
    cout<<"Page Title: "<<title<<endl;
    cout<<"Page Likes: "<<total_likes<<endl;

  }
  ~page(){
   
  }
  

};
