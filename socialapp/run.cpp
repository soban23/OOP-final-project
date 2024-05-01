#include <iostream>
// #include "page.h"
#include "user.h"
#include "post.h"
using namespace std;


int main() {
  
  user u1;
  u1.print();
  u1.setName("Jack");
  u1.setID("u1");
  u1.print();
  user u2("u2", "Jill");
  u1.addFriend(u2);
  u1.print();
  user u3("u3", "ill");
  u1.addFriend(u3);
  u1.print();
  if(u1.searchfriend("u3").getName()!= "Unknown"){
    cout << "u3 is a friend of u1" << endl;
  }else{
    cout << "u3 is not a friend of u1" << endl;
  }
  page p1;
  p1.set_id("p1");
  p1.set_title("page1");
  page p2;
  p2.set_id("p2");
  p2.set_title("page2");
  page p3;
  p3.set_id("p3");
  p3.set_title("page3");
  string* list= new string[3];
  list[0]="p1";
  list[1]="p2";
  list[2]="p3";
  string list1[2]={"u1","u2"};
  user u4("u4", "Jack");
  search_page(list[0]);
  
  
  
  
  
}
