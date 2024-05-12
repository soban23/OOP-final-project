#include <iostream>


using namespace std;


class memory{
private:
  string text;
  string owner;

string postid;
int day;
int month;
int year;

public:
  memory(){
    text="";
    owner="";
    postid="";
    day=0;
    month=0;
    year=0;
    
  }
~memory(){
  
}
string gettext(){
  return text;
}
string getowner(){
  return owner;
}
string getpostid(){
  return postid;
}
void settext(string t){
  text=t;
}
void setowner(string o){
  owner=o;
  
}
void setpostid(string p){
  postid=p;
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



};
