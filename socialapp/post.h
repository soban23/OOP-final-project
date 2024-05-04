#include <iostream>
using namespace std;

class post{
private:
  string id;
  string title;
  int likes;
  string* likelist;
  int comments;
  string *commentlist;
public:
  post(){
    id="";
    title="";
    likes=0;
    likelist=nullptr;
    comments=0;
    commentlist=nullptr;
    
  }
  void setrid(string i){
    id=i;
  }
  void settitle(string t){
    title=t;
  }
  void setlikes(int l){
    likes=l;
  }
  void setcomments(int c){
    comments=c;
  }

};
