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
  cout << " wrote: " << comment << endl;
  
}
// void addcomment(string c){
//   comment=c;
// }
~commentlist(){
  // cout<<"Comment with ID "<<id<<" deleted"<<endl;
}
};
