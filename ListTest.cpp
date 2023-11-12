//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
// g++ -std=c++17 -Wall -o test List.cpp ListTest.cpp
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

    List mylist;
    printf("Length after initializing list = %d\n", mylist.length());
    printf("Pos of curser after initializing list = %d\n", mylist.position());
    try {
        printf("Back element = %d\n", mylist.back());
    } catch (const std::length_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    try {
        printf("Front element = %d\n", mylist.front());
    } catch (const std::length_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    //test movefront and moveback on empty list
    mylist.moveBack();
    printf("Pos of curser after moving to front of empty list = %d\n", mylist.position());
    mylist.moveFront();
    printf("Pos of curser after moving to back of empty list = %d\n", mylist.position());

    printf("inserting 1 before curser.\n");
    mylist.insertBefore(1);
    mylist.moveBack();
    printf("Pos of curser = %d\n", mylist.position());

    try {
        printf("Back element = %d\n", mylist.back());
    } catch (const std::length_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    try {
        printf("Front element = %d\n", mylist.front());
    } catch (const std::length_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    mylist.moveFront();
    printf("inserting 2 before curser at the front.\n");
    mylist.insertBefore(2);
    printf("Element at the front = %d\n", mylist.front());
    printf("Element at the back = %d\n", mylist.back());
    printf("Length = %d\n", mylist.length());

    mylist.insertAfter(5);
    mylist.insertAfter(6);
    mylist.insertBefore(3);
    std::string listString = mylist.to_string();

    // Output the list to the console
    std::cout << "\nList Contents: " << listString << std::endl;
    printf("length of list = %d\n\n", mylist.length());


    //iterate forwards through list
    mylist.moveFront();
    while(mylist.position()<mylist.length()){
        printf("index of curser = %d value after curser = %d\n", mylist.position(),  mylist.peekNext());
        mylist.moveNext();
    }

    //iterate backwards through list
    printf("\nnow backwards\n");
    mylist.moveBack();
    while(mylist.position()>0){
        printf("index of curser = %d value before curser = %d\n", mylist.position(),  mylist.peekPrev());
        mylist.movePrev();
    }

    printf("index of curser = %d", mylist.position());
    mylist.setAfter(100);
    listString = mylist.to_string();

    // Output the list to the console
    std::cout << "\nList Contents after setting first to 100: " << listString << std::endl;

    mylist.moveBack();
    mylist.setBefore(27);
    listString = mylist.to_string();

    // Output the list to the console
    std::cout << "\nList Contents after setting last to 27: " << listString << std::endl;
    

    List copy = mylist;
    std::string listcopystring = copy.to_string();

    // Output the list to the console
    std::cout << "\nList copy Contents: " << listcopystring << std::endl;

    copy.moveFront();
    copy.eraseAfter();
    copy.moveNext();
    copy.eraseAfter();
    copy.moveBack();
    copy.eraseBefore();

    listcopystring = copy.to_string();

    // Output the list to the console
    std::cout << "\nList copy Contents after first last and middle elements: " << listcopystring << std::endl;


    listString = mylist.to_string();

    // Output the list to the console
    std::cout << "\nList Contents: " << listString << std::endl;
    printf("length of list = %d\n\n", mylist.length());
    mylist.moveFront();
    printf("findNext position of %d in mylist starting from front = %d\n", 100, mylist.findNext(100));
    printf("index of curser = %d\n", mylist.position());
    mylist.moveBack();
    printf("findPrev position of %d in mylist starting from back = %d\n", 100, mylist.findPrev(100));
    printf("index of curser = %d\n", mylist.position());



    mylist.moveFront();
    mylist.insertAfter(27);
    mylist.moveNext();
    mylist.moveNext();
    mylist.moveNext();
    mylist.insertAfter(27);
    mylist.insertBefore(5);
    mylist.insertBefore(3);
    mylist.moveFront();
    mylist.insertAfter(27);
    mylist.insertBefore(5);
    mylist.insertBefore(3);
    mylist.insertBefore(5);
    mylist.insertBefore(3);
    listString = mylist.to_string();

    // Output the list to the console
    std::cout << "\nList Contents before cleanup: " << listString << std::endl;
    printf("index of curser before cleanup = %d", mylist.position());
    mylist.cleanup();
    listString = mylist.to_string();

    // Output the list to the console
    std::cout << "\nList Contents after cleanup: " << listString << std::endl;
    printf("index of curser affter cleanup = %d", mylist.position());

    listString = copy.to_string();

    // Output the list to the console
    std::cout << "list copy before = assignment: " << listString << std::endl;

    copy=mylist;

    listString = copy.to_string();

    // Output the list to the console
    std::cout << "list copy after = assignment: " << listString << std::endl;

    List concat = mylist.concat(copy);
    listString = concat.to_string();

    // Output the list to the console
    std::cout << "\nContatinated list: " << listString << std::endl;
    printf("index of curser = %d", concat.position());

    listString = copy.to_string();

    // Output the list to the console
    std::cout << "\nlist copy: " << listString << std::endl;

    listString = mylist.to_string();

    // Output the list to the console
    std::cout << "list: " << listString << std::endl;

    if(mylist==copy){
        printf("\ntheyre equal");
    }else{
        printf("\ntheyre not equal");
    }

    if(mylist==concat){
        printf("\ntheyre equal");
    }else{
        printf("\ntheyre not equal");
    }

    printf("\nmylist using overwritten << operator to print: ");
    std::cout << mylist << std::endl;


    printf("\n\ntesting failures of profs tests\n");
    List B;
    List A = B;
   
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(2);
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(1);
    A.findPrev(3);
    printf("curser before cleanup: %d\n", A.position());
    std::cout << A << std::endl;
    A.cleanup();
    printf("curser After cleanup: %d\n", A.position());
    std::cout << A << std::endl;

    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(2);
    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(3);
    B.insertBefore(1);
    B.findPrev(3);
    B.movePrev();
    printf("curser before cleanup: %d\n", B.position());
    std::cout << B << std::endl;
    B.cleanup();
    A.cleanup();
    printf("curser After cleanup: %d\n", B.position());
    std::cout << B << std::endl;

    return 0;
}