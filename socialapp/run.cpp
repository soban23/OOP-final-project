#include "page.hpp"
#include "user.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

user *readuserfile() {
  ifstream file("socialapp/users.txt");

  if (!file.is_open()) {
    cout << "Failed to open the file." << endl;
    exit(0);
  }
  int totalusers;
  file >> totalusers;
  user *users = new user[totalusers];
  for (int i = 0; i < totalusers; i++) {
    string id, firstname, lastname;
    file >> id >> firstname >> lastname;
    users[i].setID(id);
    users[i].setName(firstname + " " + lastname);
    string friendId;
    while (file >> friendId && friendId != "-1") {
      users[i].addFriend(friendId);
    }

    string pageId;
    while (file >> pageId && pageId != "-1") {
      users[i].LikePage(pageId);
    }
  }

  file.close();
  return users;
}
page *readpagefile() {
  ifstream file("socialapp/pages.txt");
  if (!file.is_open()) {
    cout << "Failed to open the file." << endl;
    exit(0);
  }
  string id, title;
  int totalpages;
  file >> totalpages;
  page *pages = new page[totalpages];
  for (int i = 0; i < totalpages; i++) {
    file >> id;
    getline(file, title);
    pages[i].set_id(id);
    pages[i].set_title(title);
  }
  file.close();
  return pages;
}

int main() {

  int totalpages, totalusers;
  ifstream f1("socialapp/users.txt");
  f1 >> totalusers;
  f1.close();
  ifstream f2("socialapp/pages.txt");
  f2 >> totalpages;
  f2.close();

  user *users = readuserfile();
  page *pages = readpagefile();
  for (int i = 0; i < totalpages; i++) {
    for (int j = 0; j < totalusers; j++) {
      if (users[j].checklikes(pages[i].get_id())) {
        pages[i].increment_likes();
      }
    }
  }

  for (int i = 0; i < totalusers; i++) {
    users[i].print();

    cout << endl;
  }

  for (int i = 0; i < totalpages; i++) {
    pages[i].print();

    cout << endl;
  }

  return 0;
}
