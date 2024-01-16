#include<iostream>
#include<cstdlib>
#include "../include/Error.h"

void fatalError(std::string errorMessage){
    std::cout<<"Error:: " + errorMessage + "\n";
    std::cin.get();
    exit(EXIT_FAILURE);
}