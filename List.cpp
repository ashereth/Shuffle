/***
* Asher Etherington
* List.cpp
* Implimentation of an object oriented doubly linked list ADT
***/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


// constructor for node
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

//constructor for List
List::List(){
    //create front dummy and back dummy nodes and make them point to eachother
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    //set pos of curser to 0 and number of elements to 0
    pos_cursor = 0;
    num_elements = 0;
    //set before and after curser to be null pointers
    beforeCursor = frontDummy;
    afterCursor = backDummy;
}

// Copy constructor.
List::List(const List& L){
    
    //create front dummy and back dummy nodes and make them point to eachother
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    //set pos of curser to 0 and number of elements to 0
    pos_cursor = 0;
    num_elements = 0;
    //set before and after curser to be null pointers
    beforeCursor = frontDummy;
    afterCursor = backDummy;

    Node* temp = L.frontDummy->next;
    //set temp to be first node
    // and walk down until you reach backdummy
    while(temp!=L.backDummy){
        //add temp data to newList
        this->insertBefore(temp->data);
        //increment temp
        temp = temp->next;
        //increment cursor of newList
    }
    //return cursor to start of newlist
    this->moveFront();
}

// Destructor
List::~List(){
    //iterate through List deleting every node inside
    while (frontDummy->next != backDummy) {
        Node* temp = frontDummy->next;
        frontDummy->next = temp->next;
        delete temp;
    }
    //delete the back node and front node
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    //if length is less that or equal to 0 throw error
    if(num_elements<=0){
        throw std::length_error("List: front(): empty list");
    }
    //return data at front
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(num_elements<=0){
        throw std::length_error("List: Back(): empty list");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if(pos_cursor>=num_elements){
        throw std::length_error("List: peekNext(): curser is at end of list");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if(pos_cursor<=0){
        throw std::length_error("List: peekPrev(): curser is at start of list");
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    //iterate through List deleting every node inside
    while (frontDummy->next != backDummy) {
        Node* temp = frontDummy->next;
        frontDummy->next = temp->next;
        delete temp;
    }
    pos_cursor = 0;
    num_elements = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    //if number of elements is 0 afterCurser should be set to null too
    if(num_elements==0){
        afterCursor = backDummy;
    }else{
        afterCursor = frontDummy->next;
    }
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor = num_elements;
    afterCursor = backDummy;
    //if number of elements is 0 beforeCurser should be set to null too
    if(num_elements==0){
        beforeCursor = frontDummy;
    }else{
        beforeCursor = backDummy->prev;
    }
}

// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length()
ListElement List::moveNext(){
    if(pos_cursor>=num_elements){
        throw std::length_error("List: moveNext(): curser is at end of list");
    }
    //set temp to be the node we are returning
    Node* temp = afterCursor;
    //move beforeCurser and afterCurser forward one
    beforeCursor = temp;
    afterCursor = temp->next;

    //increment position
    pos_cursor++;
    return temp->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if(pos_cursor<=0){
        throw std::length_error("List: movePrev(): curser is at start of list");
    }
    //set temp to be the node we are returning
    Node* temp = beforeCursor;
    //move beforeCurser and afterCurser forward one
    afterCursor = temp;
    beforeCursor = temp->prev;

    //increment position
    pos_cursor--;
    return temp->data;
}

void List::insertAfter(ListElement x){
    //create a new node to be added
    Node* newNode = new Node(x);
    //if length is 0 add node inbetween front and back
    if(num_elements==0){
        frontDummy->next = newNode;
        backDummy->prev = newNode;
        newNode->next = backDummy;
        newNode->prev = frontDummy;
        afterCursor=newNode;
        num_elements = 1;
        return;
    }
    //otherwise add element after curser
    num_elements++;
    beforeCursor->next=newNode;
    afterCursor->prev=newNode;
    newNode->next=afterCursor;
    newNode->prev=beforeCursor;
    afterCursor = newNode;
}

void List::insertBefore(ListElement x){
    Node* newNode = new Node(x);
    //if length is 0 add node inbetween front and back
    if(num_elements==0){
        frontDummy->next = newNode;
        backDummy->prev = newNode;
        newNode->next = backDummy;
        newNode->prev = frontDummy;
        beforeCursor=newNode;
        num_elements = 1;
        //increment curser position
        pos_cursor++;
        return;
    }
    //otherwise add element before curser
    num_elements++;
    newNode->next=afterCursor;
    newNode->prev=beforeCursor;
    beforeCursor->next=newNode;
    afterCursor->prev=newNode;
    beforeCursor=newNode;
    //increment position of curser 
    // since we are adding before the location of the curser
    pos_cursor++;
}


// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if(pos_cursor>=num_elements){
        throw std::length_error("List: setAfter(): curser is at end of list");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(pos_cursor<=0){
        throw std::length_error("List: setBefore(): curser is at start of list");
    }
    beforeCursor->data = x;
}

//eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if(num_elements==0 || pos_cursor>=num_elements){
        throw std::length_error("List: eraseAfter(): curser is at end of list");
    }
    Node* temp = afterCursor;
    afterCursor = temp->next;
    afterCursor->prev=beforeCursor;
    beforeCursor->next=afterCursor;
    num_elements--;
    delete temp;
}

//eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(num_elements==0 || pos_cursor<=0){
        throw std::length_error("List: eraseAfter(): curser is at start of list");
    }
    Node* temp = beforeCursor;
    beforeCursor= temp->prev;
    afterCursor->prev=beforeCursor;
    beforeCursor->next=afterCursor;
    pos_cursor--;
    num_elements--;
    delete temp;
}



// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    if(pos_cursor==num_elements){
        return -1;
    }
    //check element after cursor
    int current = moveNext();
    while(current!=x && pos_cursor<num_elements){
        current = moveNext();
    }
    //if curser is at the end of the list return -1
    if(pos_cursor==num_elements && current!=x){
        return -1;
    }
    //if element was found return position of curser
    return pos_cursor;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    if(pos_cursor==0){
        return -1;
    }
    //check element after cursor
    int current = movePrev();
    while(current!=x && pos_cursor>0){
        current = movePrev();
    }
    //if curser is at the end of the list return -1
    if(pos_cursor==0 && current!=x){
        return -1;
    }
    //if element was found return position of curser
    return pos_cursor;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    if(num_elements<=1){
        return;
    }
    //keep track of original cursor position
    int position = pos_cursor;
    //get first node and keep track of its index
    Node* forward =  frontDummy->next;
    //walk forward with forward node
    while(forward!=backDummy->prev){
        moveBack();
        //back last node and keep track of its index
        Node* backward = backDummy->prev;
        int backward_index = num_elements-1;
        while(forward!=backward){
            if(backward->data==forward->data){
                //if the element we are deleting comes before the curser
                // decrement position
                if(position>backward_index){
                    //decriment original position
                    position--;
                }
                //delete backward node
                backward=backward->prev;
                //decriment backward index again because we are shortening the list
                backward_index--;
                eraseBefore();
            }else{
                movePrev();
                backward = backward->prev;
                backward_index--;
            }
        }
        //increment forward
        forward = forward->next;
    }
    //set curser back to original position
    moveFront();
    for(int i=0; i<position; i++){
        moveNext();
    }
}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List newlist = *this;
    //walk down L
    Node* temp = L.frontDummy->next;
    //move cursor to the back in order to add to the back
    newlist.moveBack();
    while(temp!=L.backDummy){
        newlist.insertAfter(temp->data);
        temp = temp->next;
        newlist.moveNext();
    }
    //move cursor to the front of newlist
    newlist.moveFront();
    return newlist;
} 

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    std::string result = "(";

    if (num_elements == 0) {
        return result + ")";
    }

    Node* temp = frontDummy->next;

    while (temp != backDummy) {
        result += std::to_string(temp->data);
        if (temp->next != backDummy) {
            result += ", ";
        }
        temp = temp->next;
    }

    result += ")";

    return result;
}


// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    //if the lengths are not the same return false
    if(num_elements!=R.num_elements){
        return false;
    }
    //start at the beginning of each list and walk down comparing the elements
    Node* Ltemp = frontDummy->next;
    Node* Rtemp = R.frontDummy->next;
    while(Ltemp!=backDummy){
        //make sure Rtemp doesnt reach the end
        if(Rtemp==R.backDummy){
            return false;
        }
        if(Ltemp->data!=Rtemp->data){
            return false;
        }
        Ltemp = Ltemp->next;
        Rtemp = Rtemp->next;
    }
    //if Ltemp has reached the end but Rtemp hasnt return false
    if(Rtemp!=R.backDummy){
        return false;
    }
    return true;
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    stream << L.to_string(); // Use the to_string function to convert the list to a string
    return stream;
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    if(A.equals(B)){
        return true;
    }
    return false;
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if (this != &L) { // Check for self-assignment
        // Clear the current list
        while (frontDummy->next != backDummy) {
            Node* temp = frontDummy->next;
            frontDummy->next = temp->next;
            delete temp;
        }

        // Reset cursor and other members
        pos_cursor = 0;
        num_elements = 0;
        beforeCursor = frontDummy;
        afterCursor = backDummy;

        // Copy elements from L to the current list
        Node* temp = L.frontDummy->next;
        while (temp != L.backDummy) {
            this->insertAfter(temp->data);
            temp = temp->next;
            this->moveNext();
        }
        //move cursor to the front might need to move cursor to location of L
        this->moveFront();
    }
    return *this;
}