#include <iostream>
using namespace std;

class commentlist{
private:
string id;
string postid;
string owner;
string comment;
public:
commentlist(){
  id="";
  postid="";
  owner="";
  comment="";
  
}
void setid(string i){
  id=i;
}
void setpostid(string p){
  postid=p;
}
void setowner(string o){
  owner=o;
}
void setcomment(string c){
  comment=c;
}
string getid(){
  return id;
}
string getpostid(){
  return postid;
}
string getowner(){
  return owner;
}
string getcomment(){
  return comment;
}
void print(){
  cout<<"Comment ID: "<<id<<endl;
  cout<<"Comment Post ID: "<<postid<<endl;
  cout<<"Comment Owner: "<<owner<<endl;
  cout<<"Comment: "<<comment<<endl;
  
}
~commentlist(){
  // cout<<"Comment with ID "<<id<<" deleted"<<endl;
}
};
