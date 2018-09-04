//
// Created by cuizhou on 18-9-3.
//

#include <iostream>
#include <mysql_helper.h>

using namespace std;

class item {
public:
    item(string n){
        name = new string(n);
    };
    void release(){
        cout << "release" << endl;
    }
    string* get(){
        return name;
    }
    string *name;
};

void clear(item *it){
    cout << "clear:" <<*(it->get()) << endl;
}


void test_mysql(){
    MySqlHelper mySqlHelper = MySqlHelper();
    mySqlHelper.Connect(Ip("127.0.0.1"), Port("3306"), Usr("root"), Password("cuizhou"));

    mySqlHelper.ExcuteCommand("CREATE DATABASE test;");
    mySqlHelper.EnterDatabse(DbName("test"));
}

void test_shared_ptr(){
    item *it = new item("aaa");
    shared_ptr<item> pt0(it);
    shared_ptr<item> pt00(it);
    cout << "pt0" << pt0.use_count() << endl;
//    delete it;
    cout << "pt0" << pt0.use_count() << endl;

//    shared_ptr<item> pt1 = make_shared<item>(item("abc"), clear);
    shared_ptr<item> pt1(new item("abc"), clear);
    cout << "pt1" << pt1.use_count() << endl;
    shared_ptr<item> pt2(pt1);
    cout << "pt1" << pt1.use_count() << endl;
    shared_ptr<item> pt3(pt2);
    cout << "pt1" << pt1.use_count() << endl;
    pt3.reset(it);
    cout << "pt0" << pt0.use_count() << endl;
    cout << "pt1" << pt1.use_count() << endl;

}

int main(){
    test_shared_ptr();
//    test_mysql();
}


