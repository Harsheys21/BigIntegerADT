/********************************************************************************* 
* Harsh Jha, hjha
* 2023 Winter CSE101 PA6
* List.cpp
* List c++ file for List ADT 
*********************************************************************************/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates a new Queue in the empty state.
List::List(){
    frontDummy = new Node(-21); 
    backDummy = new Node(-21);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
   // make this an empty Queue
    frontDummy = new Node(-21);
    backDummy = new Node(-21);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    num_elements = 0;
    pos_cursor = num_elements;

   // load elements of Q into this Queue
    Node* N = L.frontDummy->next;
    while( N!= L.backDummy ){
        this->insertBefore(N->data);
        N = N->next;
    }
    this->moveFront();
}

// Destructor
List::~List(){
    if(num_elements>0 ){
        this->clear();
    }
    num_elements = 0;
    delete frontDummy;
    delete backDummy;
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if(num_elements == 0){
        throw std::length_error("List: front(): empty List");
    }

    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(num_elements == 0){
        throw std::length_error("List: back(): empty List");
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
    if(pos_cursor >= num_elements){
        throw std::range_error("List: peekNext(): cursor is not less than length");
    }

    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if(pos_cursor <= 0){
        throw std::range_error("List: peekPrev(): cursor is not greater than 0");
    }

    return beforeCursor->data;
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    std::string s = this->to_string();
    this->moveFront();
    while(num_elements != 0){
        this->eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if(pos_cursor >= num_elements){
        throw std::range_error("List: moveNext(): cursor is greater than or equal to length of elements");
    }

    pos_cursor++;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;

    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if(pos_cursor <= 0){
        throw std::range_error("List: moveNext(): cursor is greater than or equal to length of elements");
    }

    pos_cursor--;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;

    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* N = new Node(x);
    if(pos_cursor == 0){
        frontDummy->next = N;
        N->prev = frontDummy;
    } else {
        beforeCursor->next = N;
        N->prev = beforeCursor;
    }

    if(pos_cursor == num_elements){
        backDummy->prev = N;
        N->next = backDummy;
    } else {
        afterCursor->prev = N;
        N->next = afterCursor;
    }
    afterCursor = N;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* N = new Node(x);
    if(pos_cursor == 0){
        frontDummy->next = N;
        N->prev = frontDummy;
    } else {
        beforeCursor->next = N;
        N->prev = beforeCursor;
    }
    beforeCursor = N;

    if(pos_cursor == num_elements){
        backDummy->prev = N;
        N->next = backDummy;
    } else {
        afterCursor->prev = N;
        N->next = afterCursor;
    }
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if(pos_cursor >= num_elements){
        throw std::range_error("List: setAfter(): cursor is greater than or equal to length of elements");
    }

    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(pos_cursor <= 0){
        throw std::range_error("List: setBefore: cursor is less than or equal to 0");
    }

    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if(pos_cursor >= num_elements){
        throw std::range_error("List: eraseAfter(): cursor is greater than or equal to length of elements");
    }

    Node* N = afterCursor->next;
    
    // back nodes
    beforeCursor->next = N;
    N->prev = beforeCursor;

    Node* A = afterCursor;
    delete A;
    afterCursor = N;
    num_elements--;    
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(pos_cursor <= 0){
        throw std::range_error("List: eraseBefore: cursor is less than or equal to 0");
    }
    Node* N = beforeCursor->prev;
    // back nodes
    afterCursor->prev = N;
    N->next = afterCursor;
    delete beforeCursor;
    beforeCursor = N;
    pos_cursor--;
    num_elements--;  
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    while(pos_cursor < num_elements){
        if(afterCursor->data == x){
            this->moveNext();
            return pos_cursor;
        }
        this->moveNext();
    }

    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    while(pos_cursor > 0){
        if(beforeCursor->data == x){
            this->movePrev();
            return pos_cursor;
        }
        this->movePrev();
    }

    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    List C;
    Node* N = this->frontDummy->next;
    int n = 0;
    while(N != this->backDummy){
        ListElement cursor  = N->data;
        C.moveFront();
        int option = 0;
        while(C.position() < C.length()){
            ListElement c = C.peekNext();
            if(c == cursor){
                option = 1;
                Node* after = N->next;
                Node * pre = N->prev;
                after->prev = pre;
                pre->next = after;

                if(n < pos_cursor){
                    pos_cursor--;
                }
                if(beforeCursor == N){
                    beforeCursor = pre;
                } 

                if(afterCursor == N){
                    afterCursor = after;
                }
                delete N;
                N = after;
                num_elements--;
                break;
            }
            C.moveNext();
        }
        if(option == 0){
            C.insertBefore(cursor);
            N = N->next;
            n++;
        }
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List Q;
    Node* N = this->frontDummy->next;
    while( N!= this->backDummy ){
        Q.insertBefore(N->data);
        N = N->next;
    }

    N = L.frontDummy->next;
    while( N!= L.backDummy){
        Q.insertBefore(N->data);
        N = N->next;
    }

    Q.moveFront();
    return Q;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "(";

    if(num_elements != 0){
        N = frontDummy->next;
        while(N != backDummy){
            s += std::to_string(N->data);
            
            if(N->next != backDummy){
                s += ", ";
            }
            N = N->next;
        }
    }

    s += ")";

    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    if(this->length() != R.length()){
        return false;
    }

    Node* N = this->frontDummy->next;
    Node* B = R.frontDummy->next;
    while( N!=nullptr ){
        ListElement a = N->data;
        ListElement b = B->data;

        if(a != b){
            return false;
        }
        
        B = B->next;
        N = N->next;
    }

    return true;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if( this != &L ){ // not self assignment
        // make a copy of L
        List temp = L;

        // then swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
    }

    // return this with the new data installed
    return *this;

    // the copy, if there is one, is deleted upon return
}