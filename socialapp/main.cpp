#include "comment.hpp"
#include "memory.hpp"
#include "page.hpp"
#include "post.hpp"
#include "user.hpp"
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

user* readuserfile() {
    ifstream file("users.txt");

    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        exit(0);
    }
    int totalusers;
    file >> totalusers;
    user* users = new user[totalusers];
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
page* readpagefile() {
    ifstream file("pages.txt");
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        exit(0);
    }
    string id, title;
    int totalpages;
    file >> totalpages;
    page* pages = new page[totalpages];
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
post* readpostfile() {
    ifstream file("posts.txt");
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        exit(0);
    }
    string id, title, value, liker, owner;
    int totalposts, activity, day, month, year, type;
    file >> totalposts;
    post* posts = new post[totalposts];
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
commentlist* readcommentfile() {
    ifstream file("comments.txt");
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        exit(0);
    }
    string id, postid, owner, comment;
    int totalcomments;
    file >> totalcomments;
    commentlist* comments = new commentlist[totalcomments];
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
user* setcurrentuser(user* users, int totalusers, string userid) {
    user* currentuser = nullptr;
    for (int i = 0; i < totalusers; i++) {
        if (users[i].getID() == userid) {
            currentuser = &users[i];
            return currentuser;
        }
    }
    return nullptr;
}

user* searchuser(string userid, user* users, int totalusers) {
    for (int i = 0; i < totalusers; i++) {
        if (users[i].getID() == userid) {
            return &users[i];
        }
    }
    return nullptr;
}
page* searchpage(string pageid, page* pages, int totalpages) {
    for (int i = 0; i < totalpages; i++) {
        if (pages[i].get_id() == pageid) {
            return &pages[i];
        }
    }
    return nullptr;
}

void viewhome(user* users, int totalusers, page* pages, int totalpages,
    post* posts, int totalposts, commentlist* comments,
    int totalcomments, user* currentuser, int day, int month,
    int year) {
    cout << currentuser->getName() << "'s home page" << endl;

    for (int i = 0; i < currentuser->getfriendcount(); i++) {
        user* frienduser =
            searchuser(currentuser->getfriendlist(i), users, totalusers);
        if (frienduser != nullptr) {
            for (int j = 0; j < totalposts; j++) {
                if (posts[j].getowner() == frienduser->getID()) {
                    if (posts[j].getmonth() != month || posts[j].getyear() != year) {
                        continue;
                    }
                    if (posts[j].getday() != day && posts[j].getday() != day - 1) {
                        continue;
                    }
                    cout << endl;
                    cout << frienduser->getName();
                    posts[j].print();

                    for (int k = 0; k < totalcomments; k++) {
                        if (comments[k].getpostid() == posts[j].getid()) {
                            user* commentOwner =
                                searchuser(comments[k].getowner(), users, totalusers);
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
        page* likedpage =
            searchpage(currentuser->getlikedpage(i), pages, totalpages);
        if (likedpage != nullptr) {
            for (int j = 0; j < totalposts; j++) {
                if (posts[j].getowner() == likedpage->get_id()) {

                    if (posts[j].getmonth() != month || posts[j].getyear() != year) {
                        continue;
                    }
                    if (posts[j].getday() != day && posts[j].getday() != day - 1) {
                        continue;
                    }
                    cout << endl;
                    cout << likedpage->get_title();
                    posts[j].print();
                    if (posts[j].getowner() == "p1") {
                        cout << "    " << pages[0].get_title();
                        comments[5].print();
                    }

                    for (int k = 0; k < totalcomments; k++) {
                        if (comments[k].getpostid() == posts[j].getid()) {
                            user* commentOwner =
                                searchuser(comments[k].getowner(), users, totalusers);

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

int likethepost(string postid, post* posts, int totalposts, user* currentuser) {
    for (int i = 0; i < totalposts; i++) {
        if (posts[i].getid() == postid) {
            if (posts[i].getlikes() != 10) {
                if (posts[i].checklike(currentuser->getID())) {
                    cout << "You have already liked this post" << endl;
                    return 0;
                }
                else {
                    posts[i].addlike(currentuser->getID());
                    return 1;
                }
            }
            else {
                cout << "Likes are maxxed" << endl;
                return 0;
            }
        }
    }
    return 0;
}
void viewlikelistofpost(string postid, post* posts, int totalposts,
    user* currentuser, user* users, int totalusers,
    page* pages, int totalpages) {
    for (int i = 0; i < totalposts; i++) {
        if (posts[i].getid() == postid) {
            if (posts[i].getlikes() != 0) {
                cout << "post liked by: " << endl;
                for (int j = 0; j < posts[i].getlikes(); j++) {
                    string likerId = posts[i].getliker(j);

                    user* likeduser = searchuser(likerId, users, totalusers);
                    if (likeduser != nullptr) {
                        cout << likeduser->getID() << " - " << likeduser->getName() << endl;
                    }
                    else {

                        page* likedpage = searchpage(likerId, pages, totalpages);
                        if (likedpage != nullptr) {
                            cout << likedpage->get_id() << " - " << likedpage->get_title()
                                << endl;
                        }
                    }
                }
            }
        }
    }
}

void postcomment(string postid, string comment, commentlist*& comments,
    int& totalcomments, user* currentuser, post* posts,
    int totalposts) {
    for (int i = 0; i < totalposts; i++) {
        if (posts[i].getid() == postid) {
            posts[i].addcomment(comment);

            commentlist* newComments = new commentlist[totalcomments + 1];

            for (int j = 0; j < totalcomments; j++) {
                newComments[j] = comments[j];
            }

            newComments[totalcomments].setid("c" + to_string(totalcomments + 1));
            newComments[totalcomments].setpostid(postid);
            newComments[totalcomments].setowner(currentuser->getID());
            newComments[totalcomments].setcomment(comment);

            totalcomments++;

            delete[] comments;

            comments = newComments;

            break;
        }
    }
}
void viewpost(string postid, post* posts, int totalposts, commentlist* comments,
    int& totalcomments, user* users, int totalusers, page* pages,
    int totalpages) {
    for (int i = 0; i < totalposts; i++) {
        if (posts[i].getid() == postid) {
            cout << endl;
            if (posts[i].getowner()[0] == 'u') {
                user* temp = searchuser(posts[i].getowner(), users, totalusers);
                if (temp != nullptr) {
                    cout << temp->getName();
                    posts[i].print();

                    for (int k = 0; k < totalcomments; k++) {
                        if (comments[k].getpostid() == posts[i].getid()) {
                            user* commentOwner =
                                searchuser(comments[k].getowner(), users, totalusers);
                            if (commentOwner != nullptr) {
                                cout << "    " << commentOwner->getName();
                                comments[k].print();
                            }
                        }
                    }
                }
            }
            else {
                page* temp = searchpage(posts[i].getowner(), pages, totalpages);
                if (temp != nullptr) {
                    cout << temp->get_title();
                    posts[i].print();

                    for (int k = 0; k < totalcomments; k++) {
                        if (comments[k].getpostid() == posts[i].getid()) {
                            if (comments[k].getowner() == "p1") {
                                cout << "    " << pages[0].get_title();
                                comments[k].print();
                                continue;
                            }
                            user* commentOwner =
                                searchuser(comments[k].getowner(), users, totalusers);
                            if (commentOwner != nullptr) {
                                cout << "    " << commentOwner->getName();
                                comments[k].print();
                            }
                        }
                    }
                }
            }
            break;
        }
    }
}

void viewprofile(user* currentuser, user* users, int totalusers, post* posts,
    int totalposts, commentlist* comments, int totalcomments,
    memory* memories, int totalmemories) {
    cout << currentuser->getName() << " - Timeline" << endl;
    for (int i = 0; i < totalmemories; i++) {
        if (memories[i].getowner() == currentuser->getID()) {
            cout << "~~~ " << currentuser->getName() << " shared a memory ~~~ "
                << endl;
            cout << memories[i].gettext() << endl;
            for (int j = 0; j < totalposts; j++) {
                if (memories[i].getpostid() == posts[j].getid()) {
                    cout << "(" << memories[i].getyear() - posts[j].getyear()
                        << " years ago)" << endl;
                    user* temp = searchuser(posts[j].getowner(), users, totalusers);
                    if (temp != nullptr) {
                        cout << temp->getName();
                        posts[j].print();

                        for (int k = 0; k < totalcomments; k++) {
                            if (comments[k].getpostid() == posts[j].getid()) {
                                user* commentOwner =
                                    searchuser(comments[k].getowner(), users, totalusers);
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
    for (int i = 0; i < totalposts; i++) {
        if (posts[i].getowner() == currentuser->getID()) {
            cout << endl;

            user* temp = searchuser(posts[i].getowner(), users, totalusers);
            if (temp != nullptr) {
                cout << temp->getName();
                posts[i].print();

                for (int k = 0; k < totalcomments; k++) {
                    if (comments[k].getpostid() == posts[i].getid()) {
                        user* commentOwner =
                            searchuser(comments[k].getowner(), users, totalusers);
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

void viewfriendlist(user* currentuser, user* users, int totalusers) {
    cout << currentuser->getName() << " - Friend List" << endl << endl;
    for (int i = 0; i < currentuser->getfriendcount(); i++) {
        user* frienduser =
            searchuser(currentuser->getfriendlist(i), users, totalusers);
        if (frienduser != nullptr) {
            cout << frienduser->getID() << " - " << frienduser->getName() << endl;
        }
    }
}
void viewpage(string pageid, page* pages, int totalpages, user* users,
    int totalusers, post* posts, int totalposts,
    commentlist* comments, int totalcomments) {

    for (int i = 0; i < totalposts; i++) {
        if (posts[i].getowner() == pageid) {
            cout << endl;
            page* temp = searchpage(posts[i].getowner(), pages, totalpages);
            if (temp != nullptr) {
                cout << temp->get_title();
                posts[i].print();

                for (int k = 0; k < totalcomments; k++) {
                    if (comments[k].getpostid() == posts[i].getid()) {
                        if (comments[k].getowner() == "p1") {
                            cout << "    " << pages[0].get_title();
                            comments[k].print();
                            continue;
                        }
                        user* commentOwner =
                            searchuser(comments[k].getowner(), users, totalusers);
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

void seeyourmemories(user* currentuser, user* users, int totalusers,
    post* posts, int totalposts, commentlist* comments,
    int totalcomments, int day, int month, int year) {
    for (int i = 0; i < totalposts; i++) {

        if (posts[i].getowner() == currentuser->getID()) {

            if (posts[i].getmonth() == month && posts[i].getday() == day) {

                cout << endl;
                if (year < posts[i].getyear()) {
                    continue;
                }
                cout << "On this day " << endl
                    << year - posts[i].getyear() << " years ago " << endl;
                user* temp = searchuser(posts[i].getowner(), users, totalusers);
                if (temp != nullptr) {
                    cout << temp->getName();
                    ;
                    posts[i].print();

                    for (int k = 0; k < totalcomments; k++) {
                        if (comments[k].getpostid() == posts[i].getid()) {
                            user* commentOwner =
                                searchuser(comments[k].getowner(), users, totalusers);
                            if (commentOwner != nullptr) {
                                cout << "    " << commentOwner->getName();
                                comments[k].print();
                                cout << endl;
                            }
                        }
                    }
                }
            }
        }
    }
}
void sharememory(string postid, string text, post* posts, int totalposts,
    user* currentuser, user* users, int totalusers, page* pages,
    int totalpages, commentlist* comments, int totalcomments,
    memory*& memories, int& totalmemories, int day, int month,
    int year) {

    for (int i = 0; i < totalposts; i++) {
        if (posts[i].getid() == postid) {

            if (posts[i].getowner() == currentuser->getID()) {

                memory* temp = new memory[totalmemories + 1];
                for (int j = 0; j < totalmemories; j++) {
                    temp[j] = memories[j];
                }

                temp[totalmemories].settext(text);
                temp[totalmemories].setowner(currentuser->getID());
                temp[totalmemories].setpostid(postid);
                temp[totalmemories].setday(day);
                temp[totalmemories].setmonth(month);
                temp[totalmemories].setyear(year);
                totalmemories++;

                delete[] memories;
                memories = temp;
                break;
            }
            else {
                cout << "You can only share memories of your own posts." << endl;
                break;
            }
        }
    }
}

int main() {

    int totalpages, totalusers, totalposts, totalcomments;
    ;
    ifstream f1("users.txt");
    f1 >> totalusers;
    f1.close();
    ifstream f2("pages.txt");
    f2 >> totalpages;
    f2.close();
    ifstream f3("posts.txt");
    f3 >> totalposts;
    f3.close();
    ifstream f4("comments.txt");
    f4 >> totalcomments;
    f4.close();

    string commenttext;
    int day, month, year;
    user* users = readuserfile();
    page* pages = readpagefile();
    post* posts = readpostfile();
    commentlist* comments = readcommentfile();
    memory* memories = nullptr;
    int totalmemories = 0;
    for (int i = 0; i < totalpages; i++) {
        for (int j = 0; j < totalusers; j++) {
            if (users[j].checklikes(pages[i].get_id())) {
                pages[i].increment_likes();
            }
        }
    }

    for (int i = 0; i < totalcomments; i++) {
        for (int j = 0; j < totalposts; j++) {
            if (comments[i].getpostid() == posts[j].getid()) {
                posts[j].addcomment(comments[i].getcomment());
            }
        }
    }
    cout << "Commands~          "
        << "(X means number)" << endl
        << endl;
    cout << "set current date" << endl;
    cout << "set current user uX" << endl;
    cout << "view home" << endl;
    cout << "like post postX" << endl;
    cout << "view likedlist postX" << endl;
    cout << "post comment postX" << endl;
    cout << "view post postX" << endl;
    cout << "view profile" << endl;
    cout << "view friend list" << endl;
    cout << "view page pX" << endl;
    cout << "see your memories" << endl;
    cout << "share memory" << endl;

    string number;
    string command;
    user* currentuser = nullptr;

    while (lowerto(command) != "exit") {
        cout << "------------------------------------------------------------------"
            "-------------------------------------------"
            << endl;
        cout << "command: ";
        getline(cin, command);
        if (lowerto(command) == "set current date") {
            cout << "Enter date: ";
            cin >> day >> month >> year;
            cin.ignore();
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1) {
                cout << "Invalid date" << endl;
                continue;
            }
            continue;
        }
        else if (lowerto(command) == "set current user u1") {
            currentuser = setcurrentuser(users, totalusers, "u1");

            continue;
        }
        else if (lowerto(command) == "set current user u2") {
            currentuser = setcurrentuser(users, totalusers, "u2");
            continue;
        }
        else if (lowerto(command) == "set current user u3") {
            currentuser = setcurrentuser(users, totalusers, "u3");
            continue;
        }
        else if (lowerto(command) == "set current user u4") {
            currentuser = setcurrentuser(users, totalusers, "u4");
            continue;
        }
        else if (lowerto(command) == "set current user u5") {
            currentuser = setcurrentuser(users, totalusers, "u5");
            continue;
        }
        else if (lowerto(command) == "set current user u6") {
            currentuser = setcurrentuser(users, totalusers, "u6");
            continue;
        }
        else if (lowerto(command) == "set current user u7") {
            currentuser = setcurrentuser(users, totalusers, "u7");
            continue;
        }
        else if (lowerto(command) == "set current user u8") {
            currentuser = setcurrentuser(users, totalusers, "u8");
            continue;
        }
        else if (lowerto(command) == "set current user u9") {
            currentuser = setcurrentuser(users, totalusers, "u9");
            continue;
        }
        else if (lowerto(command) == "set current user u10") {
            currentuser = setcurrentuser(users, totalusers, "u10");
            continue;
        }
        else if (lowerto(command) == "set current user u11") {
            currentuser = setcurrentuser(users, totalusers, "u11");
            continue;
        }
        else if (lowerto(command) == "set current user u12") {
            currentuser = setcurrentuser(users, totalusers, "u12");
            continue;
        }
        else if (lowerto(command) == "set current user u13") {
            currentuser = setcurrentuser(users, totalusers, "u13");
            continue;
        }
        else if (lowerto(command) == "set current user u14") {
            currentuser = setcurrentuser(users, totalusers, "u14");
            continue;
        }
        else if (lowerto(command) == "set current user u15") {
            currentuser = setcurrentuser(users, totalusers, "u15");
            continue;
        }
        else if (lowerto(command) == "set current user u16") {
            currentuser = setcurrentuser(users, totalusers, "u16");
            continue;
        }
        else if (lowerto(command) == "set current user u17") {
            currentuser = setcurrentuser(users, totalusers, "u17");
            continue;
        }
        else if (lowerto(command) == "set current user u18") {
            currentuser = setcurrentuser(users, totalusers, "u18");
            continue;
        }
        else if (lowerto(command) == "set current user u19") {
            currentuser = setcurrentuser(users, totalusers, "u19");
            continue;
        }
        else if (lowerto(command) == "set current user u20") {
            currentuser = setcurrentuser(users, totalusers, "u20");

            continue;
        }
        else if (lowerto(command) == "set current user u20") {
            currentuser = setcurrentuser(users, totalusers, "u20");
            continue;
        }
        if (currentuser != nullptr) {
            if (lowerto(command) == "view home") {
                viewhome(users, totalusers, pages, totalpages, posts, totalposts,
                    comments, totalcomments, currentuser, day, month, year);
                continue;
            }
            else if (lowerto(command) == "like post post1") {
                likethepost("post1", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post2") {
                likethepost("post2", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post3") {
                likethepost("post3", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post4") {
                likethepost("post4", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post5") {
                likethepost("post5", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post6") {
                likethepost("post6", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post7") {
                likethepost("post7", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post8") {
                likethepost("post8", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post9") {
                likethepost("post9", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post10") {
                likethepost("post10", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post11") {
                likethepost("post11", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "like post post12") {
                likethepost("post12", posts, totalposts, currentuser);
                continue;
            }
            else if (lowerto(command) == "view likedlist post1") {
                viewlikelistofpost("post1", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post2") {
                viewlikelistofpost("post2", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post3") {
                viewlikelistofpost("post3", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post4") {
                viewlikelistofpost("post4", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post5") {
                viewlikelistofpost("post5", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post6") {
                viewlikelistofpost("post6", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post7") {
                viewlikelistofpost("post7", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post8") {
                viewlikelistofpost("post8", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post9") {
                viewlikelistofpost("post9", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post10") {
                viewlikelistofpost("post10", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post11") {
                viewlikelistofpost("post11", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view likedlist post12") {
                viewlikelistofpost("post12", posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "post comment post1") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post1", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post2") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post2", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post3") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post3", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post4") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post4", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post5") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post5", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post6") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post6", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post7") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post7", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post8") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post8", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post9") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post9", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post10") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post10", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post11") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post11", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "post comment post12") {
                cout << endl << "Enter the comment: ";
                getline(cin, commenttext);
                postcomment("post12", commenttext, comments, totalcomments, currentuser,
                    posts, totalposts);
                continue;
            }
            else if (lowerto(command) == "view post post1") {
                viewpost("post1", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post2") {
                viewpost("post2", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post3") {
                viewpost("post3", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post4") {
                viewpost("post4", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post5") {
                viewpost("post5", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post6") {
                viewpost("post6", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post7") {
                viewpost("post7", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post8") {
                viewpost("post8", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post9") {
                viewpost("post9", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post10") {
                viewpost("post10", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post11") {
                viewpost("post11", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view post post12") {
                viewpost("post12", posts, totalposts, comments, totalcomments, users,
                    totalusers, pages, totalpages);
                continue;
            }
            else if (lowerto(command) == "view profile") {
                viewprofile(currentuser, users, totalusers, posts, totalposts, comments,
                    totalcomments, memories, totalmemories);
                continue;
            }
            else if (lowerto(command) == "view friend list") {
                viewfriendlist(currentuser, users, totalusers);
                continue;
            }
            else if (lowerto(command) == "view page p1") {
                viewpage("p1", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p2") {
                viewpage("p2", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p3") {
                viewpage("p3", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p4") {
                viewpage("p4", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p5") {
                viewpage("p5", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p6") {
                viewpage("p6", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p7") {
                viewpage("p7", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p8") {
                viewpage("p8", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p9") {
                viewpage("p9", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p10") {
                viewpage("p10", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p11") {
                viewpage("p11", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "view page p12") {
                viewpage("p12", pages, totalpages, users, totalusers, posts, totalposts,
                    comments, totalcomments);
            }
            else if (lowerto(command) == "see your memories") {
                seeyourmemories(currentuser, users, totalusers, posts, totalposts,
                    comments, totalcomments, day, month, year);
            }
            else if (lowerto(command) == "share memory") {
                cout << "Enter the post number: ";
                cin >> number;
                cin.ignore();
                cout << "Enter capion: ";
                getline(cin, commenttext);
                cin.ignore();
                sharememory(number, commenttext, posts, totalposts, currentuser, users,
                    totalusers, pages, totalpages, comments, totalcomments,
                    memories, totalmemories, day, month, year);
            }
        }

        continue;
    }
    delete[] users;
    users = nullptr;
    delete[] posts;
    posts = nullptr;
    delete[] pages;
    pages = nullptr;
    delete[] comments;
    comments = nullptr;
    delete[] memories;
    memories = nullptr;


    return 0;
}
