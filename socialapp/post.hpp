#include <iostream>
// #include "comment.hpp"
// #include <cmath>

using namespace std;

class post{
private:
  string id;
  string title;
  int likes;
  string* likelist;
  int comments;
  string *commentlist;
  int day;
  int month;
  int year;
  int type;
  string value;
  string owner;
  
public:
  post(){
    id="";
    title="";
    likes=0;
    likelist=nullptr;
    comments=0;
    commentlist=nullptr;
    day=0;
    month=0;
    year=0;
    type=0;
    value="";
    owner="";
    
    
  }
void setowner(string o){
  owner=o;
}
string getowner(){
  return owner;
}
  void setid(string i){
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
int getlikes(){
  return likes;
}
  string getid(){
    return id;
  }
  string gettitle(){
    return title;
  }
  int getcomments(){
    return comments;
  }
  void setday(int d){
    day=d;
  }
  void setmonth(int m){
    month=m;
  }
  void setyear(int y){
    year=y;
  }
  int getday(){
    return day;
  }
  int getmonth(){
    return month;
  }
  int getyear(){
    return year;
  }
  int gettype(){
    return type;
  }
  string getvalue(){
    return value;
  }
  void settype(int t){
    type=t;
  }
  void setvalue(string v){
    value=v;
  }
  void print(){
    string act= "";
    if(type==1){
      act="feeling";;
    }else if(type==2){
      act="thinking about";
    }else if(type==3){
      act="making";
    }else if(type==4){
      act="celebrating";
    }
    if(act == ""){
      cout << " shared "<< title << endl;
    } else {
      cout <<" is "<<act<<" "<<value<<endl;
      cout << title << endl;
    }
    
    
    
  }
  void addlike(string u){
    likes++;
    string *temp=new string[likes];
    for(int i=0;i<likes-1;i++){
      temp[i]=likelist[i];
      
    }
    temp[likes-1]=u;
    delete[] likelist;
    likelist=temp;
    
  }
  void displaylikers(){
    for(int i=0;i<likes;i++){
      cout  << likelist[i] << endl;
    }
  }
  void addcomment(string c){
    comments++;
    string *temp=new string[comments];
    for(int i=0;i<comments-1;i++){
      temp[i]=commentlist[i];
      
    }
    temp[comments-1]=c;
    delete[] commentlist;
    commentlist=temp;
    
  }
~post(){
  delete[] likelist;
  delete[] commentlist;
}

    
  
};
