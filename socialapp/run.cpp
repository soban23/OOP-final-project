#include "comment.hpp"
#include "page.hpp"
#include "post.hpp"
#include "user.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

// class post;

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
    file.ignore();
    getline(file, title);
    pages[i].set_id(id);
    pages[i].set_title(title);
  }
  file.close();
  return pages;
}
post *readpostfile() {
  ifstream file("socialapp/posts.txt");
  if (!file.is_open()) {
    cout << "Failed to open the file." << endl;
    exit(0);
  }
  string id, title, value, liker, owner;
  int totalposts, activity, day, month, year, type;
  file >> totalposts;
  post *posts = new post[totalposts];
  for (int i = 0; i < totalposts; i++) {
    file >> activity;
    file >> id;
    file >> day;
    file >> month;
    file >> year;

    file.ignore();
    getline(file, title);
    if (activity == 2) {
      file >> type;
      file.ignore();
      getline(file, value);
      posts[i].settype(type);
      posts[i].setvalue(value);
    }
    file >> owner;
    while (file >> liker && liker != "-1") {
      posts[i].addlike(liker);
    }
    posts[i].setday(day);
    posts[i].setmonth(month);
    posts[i].setyear(year);
    posts[i].setid(id);
    posts[i].settitle(title);
    posts[i].setowner(owner);
  }

  file.close();
  return posts;
}
commentlist *readcommentfile() {
  ifstream file("socialapp/comments.txt");
  if (!file.is_open()) {
    cout << "Failed to open the file." << endl;
    exit(0);
  }
  string id, postid, owner, comment;
  int totalcomments;
  file >> totalcomments;
  commentlist *comments = new commentlist[totalcomments];
  for (int i = 0; i < totalcomments; i++) {
    file >> id;
    file >> postid;
    file >> owner;
    file.ignore();
    getline(file, comment);
    comments[i].setid(id);
    comments[i].setpostid(postid);
    comments[i].setowner(owner);
    comments[i].setcomment(comment);
  }
  file.close();
  return comments;
}
int main() {

  int totalpages, totalusers, totalposts, totalcomments;;
  ifstream f1("socialapp/users.txt");
  f1 >> totalusers;
  f1.close();
  ifstream f2("socialapp/pages.txt");
  f2 >> totalpages;
  f2.close();
  ifstream f3("socialapp/posts.txt");
  f3 >> totalposts;
  f3.close();
  ifstream f4("socialapp/comments.txt");
  f4 >> totalcomments;
  f4.close();

  user *users = readuserfile();
  page *pages = readpagefile();
  post* posts = readpostfile();
  commentlist *comments = readcommentfile();
  for (int i = 0; i < totalpages; i++) {
    for (int j = 0; j < totalusers; j++) {
      if (users[j].checklikes(pages[i].get_id())) {
        pages[i].increment_likes();
      }
    }
  }

  for (int i = 0; i < totalusers; i++) {
    // users[i].print();

    cout << endl;
  }

  for (int i = 0; i < totalpages; i++) {
    // pages[i].print();

    cout << endl;
  }
  for (int i = 0; i < totalposts; i++) {
    // posts[i].print();
    cout << endl;
  }
  
  for(int i = 0; i < totalcomments; i++){
    for(int j = 0; j < totalposts; j++){
      if(comments[i].getpostid() == posts[j].getid()){
        posts[j].addcomment(comments[i].getcomment());
        
      }
      
    }
  }
  // for (int i = 0; i < totalcomments; i++){
  //    comments[i].print();
  //   cout << endl;
  // }
  for (int i = 0; i < totalposts; i++) {
    posts[i].print();
    cout << endl;
  }

  return 0;
}
