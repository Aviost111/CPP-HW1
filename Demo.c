#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdio.h>

int main() {
    // Create some book objects
    pbook b1 = creat_book("Harry Potter",12345) ;
    pbook b2 = creat_book("C intro", 45678) ;
    pbook b3 = creat_book("The Lord of the Rings", 91011);

    // Create an AdptArray of books
    PAdptArray mybooks = CreateAdptArray(copy_book, delete_book, print_book);
    SetAdptArrayAt(mybooks, 0, b1);
    SetAdptArrayAt(mybooks, 1, b2);
    SetAdptArrayAt(mybooks, 3, b3);

    // Print the size of the AdptArray
    printf("The size of mybooks is %d\n", GetAdptArraySize(mybooks));

    // Print the entire AdptArray
    printf("Printing mybooks:\n");
    PrintDB(mybooks);

    // Get a book object from the AdptArray
    pbook b = GetAdptArrayAt(mybooks, 2);
    if (b != NULL) {
        printf("The book at index 2 is %s\n", b->name);
    } else {
        printf("The book at index 2 is NULL\n");
    }

    // Create some person objects
    pperson p1 = creat_person("Harry","Potter", 934);
    pperson p2 = creat_person("Ron","Weasley", 789);
    pperson p3 = creat_person("Gandalf","the Grey", 121314);

    // Create an AdptArray of persons
    PAdptArray mypeople = CreateAdptArray(copy_person, delete_person, print_person);
    SetAdptArrayAt(mypeople, 0, p1);
    SetAdptArrayAt(mypeople, 1, p2);
    SetAdptArrayAt(mypeople, 4, p3);

    // Print the size of the AdptArray
    printf("The size of mypeople is %d\n", GetAdptArraySize(mypeople));

    // Print the entire AdptArray
    printf("Printing mypeople:\n");
    PrintDB(mypeople);

    // Get a person object from the AdptArray
    pperson p = GetAdptArrayAt(mypeople, 2);
    if (p != NULL) {
        printf("The person at index 2 is %s %s\n", p->first_name, p->last_name);
    } else {
        printf("The person at index 2 is NULL\n");
    }

    // Delete the AdptArrays and all associated objects
    DeleteAdptArray(mybooks);
    DeleteAdptArray(mypeople);
    delete_book(b1);
    delete_book(b2);
    delete_book(b3);
    delete_person(p1);
    delete_person(p2);
    delete_person(p3);

    return 0;
}

