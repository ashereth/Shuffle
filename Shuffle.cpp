/***
* Asher Etherington
* Shuffle.cpp
* uses List ADT to perform shuffles ona deck(List) of a given size
***/
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include"List.h"

//helper function for shuffle to get the right side of a list
List Right(List& L){
    //get the size divided by 2 and take the larger number if its odd
    int size = std::ceil(static_cast<double>(L.length()) / 2);
    List Right;
    L.moveBack();
    for(int i = 0; i<size; i++){
        Right.insertAfter(L.movePrev());
    }
    return Right;
}

//helper function for shuffle to get the left side of a list
List Left(List& L){
    //get the size divided by 2 and if its odd take smaller number
    int size = std::floor(static_cast<double>(L.length()) / 2);
    List Left;
    L.moveFront();
    for(int i = 0; i<size; i++){
        Left.insertBefore(L.moveNext());
    }
    return Left;
}

void shuffle(List& D){
    //split the deck
    List left = Left(D);
    List right = Right(D);
    //empty the deck
    List empty;
    D = empty;
    //move to the front of the left and right lists
    left.moveFront();
    right.moveFront();
    //walk down left and right lists  inserting their elements into D
    while(left.position()!=left.length()){
        D.insertBefore(right.moveNext());
        D.insertBefore(left.moveNext());
    }
    //if  we didnt finish the right then insert last element from right list
    if(right.position()!=right.length()){
        D.insertBefore(right.moveNext());
    }
}

//makes a deck of size = size
List makeDeck(int size){
    List deck;
    for(int i=0; i<size; i++){
        deck.insertBefore(i);
    }
    return deck;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <size>" << std::endl;
        return EXIT_FAILURE;
    }

    int size = std::atoi(argv[1]);
    
    printf("deck size       shuffle count\n");
    printf("------------------------------\n");
    for(int i = 1; i<= size; i++){
        int sizei = i;
        List deck = makeDeck(sizei);
        List left = Left(deck);
        List right = Right(deck);
        List copy = deck;
        int count = 1;
        shuffle(deck);
        while(!(deck==copy)){
            shuffle(deck);
            count++;
        }
        printf(" %d               %d\n", i, count);
    }
    
    return 0;
}