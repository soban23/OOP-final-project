#include "page.h"
#include <cstring>
#include <iostream>
using namespace std;

class user {
  friend ostream &operator<<(ostream &out, const user &currentuser) {
    out << "ID: " << currentuser.id << endl;
    out << "Name: " << currentuser.name << endl;

    return out;
  }

private:
  string id;
  string name;
  user *friendlist;
  int friendcount;
  page *likedpages;
  int likedpagecount;

public:
  user() {
    id = "";
    name = "Unknown";
    friendlist = nullptr;
    friendcount = 0;
    likedpages = nullptr;
    likedpagecount = 0;
  }
  user(string i, string n, user *list1 = nullptr, int fc = 0,
       page *list2 = nullptr, int lp=0) {
    id = i;
    name = n;
    friendlist = list1;
    friendcount = fc;
    likedpages = list2;
    likedpagecount=lp;
  }
  void setID(string i) { id = i; }
  void setName(string n) { name = n; }
  string getID() { return id; }
  string getName() { return name; }
  void print() {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Friend Count: " << friendcount << endl;
    cout << "Friend List: " << endl;
    for (int i = 0; i < friendcount; i++) {
      cout << "  ";
      cout << friendlist[i] << endl;
    }
  }
  void addFriend(user u) {
    friendcount++;
    user *temp;
    temp = new user[friendcount];
    for (int i = 0; i < friendcount - 1; i++) {
      temp[i] = friendlist[i];
    }
    temp[friendcount - 1] = u;
    friendlist = temp;
  }
  ~user() { delete[] friendlist; }
  user searchfriend(string u) {
    for (int i = 0; i < friendcount; i++) {
      if (friendlist[i].getID() == u) {
        // cout << "Friend found" << endl;
        return friendlist[i];
      }
    }
    return user();
  }
void likedpage(page p){
  page *temp;
  
  temp=new page[likedpagecount+1];
  for(int i=0;i<likedpagecount;i++){
    temp[i]=likedpages[i];
    
  }
  temp[likedpagecount+1]=p;
  likedpages=temp;
  likedpagecount++;
}
};
