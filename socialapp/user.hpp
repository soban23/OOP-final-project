#include <iostream>
#include <cstring>
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
  string *friendlist;
  int friendcount;
  string *likedpages;
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
    cout << "Liked Page Count: " << likedpagecount << endl;
    cout << "Liked Page List: " << endl;
    for (int i = 0; i < likedpagecount; i++){
      cout << "  ";
      cout << likedpages[i] << endl;
      
    }
  }

string getfriendlist(int i){
  return friendlist[i];
}
  void addFriend(string u) {
    friendcount++;
    string *temp = new string[friendcount];
    for (int i = 0; i < friendcount - 1; i++) {
      temp[i] = friendlist[i];
    }
    temp[friendcount - 1] = u;
    delete[] friendlist;
    friendlist = temp;
  }

void LikePage(string u) {
  likedpagecount++;
  string *temp = new string[likedpagecount];
  for (int i = 0; i < likedpagecount - 1; i++) {
    temp[i] = likedpages[i];
  }
  temp[likedpagecount - 1] = u;
  delete[] likedpages;
  likedpages = temp;
}
string getlikedpage(int i){
  return likedpages[i];
}
int getlikes(){
  return likedpagecount;
}

int checklikes(string p){
  for (int i = 0; i < likedpagecount; i++){
    if (p == likedpages[i]){
      return 1;
    }
  }
  return 0;
}
int getfriendcount(){
  return friendcount;
}
  ~user() {
    delete[] friendlist; 
    delete[] likedpages;
  }
 
};

