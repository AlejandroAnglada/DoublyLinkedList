#include <iostream>

#include "../include/DoublyLinkedList.h"
#include <random>

using namespace std;

int main(int argc, char** argv) {

    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, 100);
    DoublyLinkedList<int> lista;

    for (int i = 0; i < 20; i++)
        lista.push_back(distribution(generator));

    for (auto elem = lista.begin(); elem != lista.end(); elem = lista.next())
        cout << elem << " ";

}