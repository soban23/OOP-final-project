#include "comment.hpp"
#include "page.hpp"
#include "post.hpp"
#include "user.hpp"
#include <cctype>
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
string lowerto(string s) {
  for (int i = 0; i < s.length(); i++) {
    s[i] = tolower(s[i]);
  }
  return s;
}
user *setcurrentuser(user *users, int totalusers, string userid) {
  user *currentuser = nullptr;
  for (int i = 0; i < totalusers; i++) {
    if (users[i].getID() == userid) {
      currentuser = &users[i];
      return currentuser;
    }
  }
  return nullptr;
}
// 3
void likethepost(string postid, post *posts, int totalposts) {
  for (int i = 0; i < totalposts; i++) {
    if (posts[i].getid() == postid) {
      // posts[i].addlike();
    }
  }
}
user *searchuser(string userid, user *users, int totalusers) {
  for (int i = 0; i < totalusers; i++) {
    if (users[i].getID() == userid) {
      return &users[i];
    }
  }
  return nullptr;
}
page *searchpage(string pageid, page *pages, int totalpages) {
  for (int i = 0; i < totalpages; i++) {
    if (pages[i].get_id() == pageid) {
      return &pages[i];
    }
  }
  return nullptr;
}
void viewhome(user *users, int totalusers, page *pages, int totalpages,
              post *posts, int totalposts, commentlist *comments,
              int totalcomments, user *currentuser) {
    cout << currentuser->getName() << "'s home page" << endl;

   
    for (int i = 0; i < currentuser->getfriendcount(); i++) {
        user *frienduser = searchuser(currentuser->getfriendlist(i), users, totalusers);
        if (frienduser != nullptr) {
            for (int j = 0; j < totalposts; j++) {
                if (posts[j].getowner() == frienduser->getID()) {
                  cout << endl;
                    cout << frienduser->getName();
                    posts[j].print();
                    
                    for (int k = 0; k < totalcomments; k++) {
                        if (comments[k].getpostid() == posts[j].getid()) {
                            user *commentOwner = searchuser(comments[k].getowner(), users, totalusers);
                            if (commentOwner != nullptr) {
                                cout << "    " << commentOwner->getName();
                                comments[k].print();
                            }
                        }
                    }
                }
            }
        }
    }

    
    for (int i = 0; i < currentuser->getlikes(); i++) {
        page *likedpage = searchpage(currentuser->getlikedpage(i), pages, totalpages);
        if (likedpage != nullptr) {
            for (int j = 0; j < totalposts; j++) {
                if (posts[j].getowner() == likedpage->get_id()) {
                  cout << endl;
                    cout << likedpage->get_title();
                    posts[j].print();
                    if(posts[j].getowner()=="p1"){
                      cout << "    " << pages[0].get_title();
                      comments[5].print();
                    }
                    
                    for (int k = 0; k < totalcomments; k++) {
                        if (comments[k].getpostid() == posts[j].getid()) {
                            user *commentOwner = searchuser(comments[k].getowner(), users, totalusers);
                          
                            
                            if (commentOwner != nullptr) {
                              
                                cout << "    " << commentOwner->getName();
                                comments[k].print();
                            
                          }
                        }
                    }
                }
            }
        }
    }
}

void viewhome1(user *users, int totalusers, page *pages, int totalpages,
              post *posts, int totalposts, commentlist *comments,
              int totalcomments, user *currentuser) {
  user *frienduser = nullptr;
  user *tempuser = nullptr;
  cout << currentuser->getName() << "- home page " << endl;
  for (int i = 0; i < currentuser->getfriendcount(); i++) {
    cout << endl;
    frienduser = searchuser(currentuser->getfriendlist(i), users, totalusers);
    if (frienduser != nullptr) {
      for (int j = 0; j < totalposts; j++) {
        if (posts[j].getowner() == frienduser->getID()) {
          cout << endl;
          tempuser = searchuser(posts[j].getowner(), users, totalusers);
          cout << tempuser->getName() << " ";
          posts[j].print();
          for (int k = 0; k < posts[j].getcomments(); k++) {
            if (comments[k].getpostid() == posts[j].getid()) {
              tempuser = searchuser(comments[k].getowner(), users, totalusers);
              cout << "     " << tempuser->getName() << " ";
              comments[k].print();
            }
          }
        }
      }
    }
  }
  page *likedpage = nullptr;
  page *temppage = nullptr;
  for (int i = 0; i < currentuser->getlikes(); i++) {
    cout << endl;
    likedpage = searchpage(currentuser->getlikedpage(i), pages, totalpages);
    if (likedpage != nullptr) {
      for (int j = 0; j < totalposts; j++) {
        if (posts[j].getowner() == likedpage->get_id()) {
          cout << endl;
          temppage = searchpage(posts[j].getowner(), pages, totalpages);
          cout << temppage->get_title() << " ";
          posts[j].print();
          for (int k = 0; k < posts[j].getcomments(); k++) {
            if (comments[k].getpostid() == posts[j].getid()) {
              if(comments[k].getowner()!="p1"){
                tempuser = searchuser(comments[k].getowner(), users, totalusers);
                cout << "     " << tempuser->getName() << " ";
                comments[k].print();
              }else{
                temppage = searchpage(posts[j].getowner(), pages, totalpages);
                cout << "     " << temppage->get_title() << " ";
                comments[k].print();
              }
            }
          }
        }
      }
    }
  }
}

int main() {

  int totalpages, totalusers, totalposts, totalcomments;
  ;
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
  post *posts = readpostfile();
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

    // cout << endl;
  }

  for (int i = 0; i < totalpages; i++) {
    // pages[i].print();

    // cout << endl;
  }
  for (int i = 0; i < totalposts; i++) {
    // posts[i].print();
    // cout << endl;
  }

  for (int i = 0; i < totalcomments; i++) {
    for (int j = 0; j < totalposts; j++) {
      if (comments[i].getpostid() == posts[j].getid()) {
        posts[j].addcomment(comments[i].getcomment());
        
      }
    }
  }
  // for (int i = 0; i < totalcomments; i++){
  //    comments[i].print();
  //   cout << endl;
  // }
  for (int i = 0; i < totalposts; i++) {
    // posts[i].print();
    // cout << endl;
  }
  string command;
  user *currentuser = nullptr;
  // cout << "command: ";
  // cin >> command;
  while (command != "exit") {
    cout << "------------------------------------------------------------------"
            "-------------------------------------------"
         << endl;
    cout << "command: ";
    getline(cin, command);
    if (lowerto(command) == "set current user u1") {
      currentuser = setcurrentuser(users, totalusers, "u1");
      // currentuser->print();
      continue;
    } else if (lowerto(command) == "set current user u2") {
      currentuser = setcurrentuser(users, totalusers, "u2");
      // cout << currentuser->getID();
      // currentuser->print();
      continue;
    } else if (lowerto(command) == "set current user u3") {
      currentuser = setcurrentuser(users, totalusers, "u3");
      continue;
    } else if (lowerto(command) == "set current user u4") {
      currentuser = setcurrentuser(users, totalusers, "u4");
      continue;
    } else if (lowerto(command) == "set current user u5") {
      currentuser = setcurrentuser(users, totalusers, "u5");
      continue;
    } else if (lowerto(command) == "set current user u6") {
      currentuser = setcurrentuser(users, totalusers, "u6");
      continue;
    } else if (lowerto(command) == "set current user u7") {
      currentuser = setcurrentuser(users, totalusers, "u7");
      continue;
    } else if (lowerto(command) == "set current user u8") {
      currentuser = setcurrentuser(users, totalusers, "u8");
      continue;
    } else if (lowerto(command) == "set current user u9") {
      currentuser = setcurrentuser(users, totalusers, "u9");
      continue;
    } else if (lowerto(command) == "set current user u10") {
      currentuser = setcurrentuser(users, totalusers, "u10");
      continue;
    } else if (lowerto(command) == "set current user u11") {
      currentuser = setcurrentuser(users, totalusers, "u11");
      continue;
    } else if (lowerto(command) == "set current user u12") {
      currentuser = setcurrentuser(users, totalusers, "u12");
      continue;
    } else if (lowerto(command) == "set current user u13") {
      currentuser = setcurrentuser(users, totalusers, "u13");
      continue;
    } else if (lowerto(command) == "set current user u14") {
      currentuser = setcurrentuser(users, totalusers, "u14");
      continue;
    } else if (lowerto(command) == "set current user u15") {
      currentuser = setcurrentuser(users, totalusers, "u15");
      continue;
    } else if (lowerto(command) == "set current user u16") {
      currentuser = setcurrentuser(users, totalusers, "u16");
      continue;
    } else if (lowerto(command) == "set current user u17") {
      currentuser = setcurrentuser(users, totalusers, "u17");
      continue;
    } else if (lowerto(command) == "set current user u18") {
      currentuser = setcurrentuser(users, totalusers, "u18");
      continue;
    } else if (lowerto(command) == "set current user u19") {
      currentuser = setcurrentuser(users, totalusers, "u19");
      continue;
    } else if (lowerto(command) == "set current user u20") {
      currentuser = setcurrentuser(users, totalusers, "u20");
      // currentuser->print();
      continue;
    } else if (lowerto(command) == "set current user u20") {
      currentuser = setcurrentuser(users, totalusers, "u20");
      continue;
    }
    if (currentuser != nullptr) {
      if (lowerto(command) == "view home") {
        viewhome(users, totalusers, pages, totalpages, posts, totalposts,
                 comments, totalcomments, currentuser);
        continue;
      }
    }

    continue;
  }

  return 0;
}
