// Yağız Can Aslan 22001943 CS201-3

#include <iostream>
#include <string>
#include "Cabinet.h"
#include "Chemical.h"
#include "Drawer.h"
using namespace std;

Drawer::Drawer( int r, int c) {
    chemical = new Chemical();
    hasChemical = false;
    row = r;
    col = c;
    initialState = true;
}

Drawer::Drawer() {
    chemical = new Chemical();
    hasChemical = false;
    row = 0;
    col = 0;
    initialState = true;
}

Drawer::~Drawer() {
    delete chemical;
}

bool Drawer::addChemicalToDrawer( Chemical*& chem) {
    if ( !hasChemical && !initialState ) {
        if ( chemical ) {
            delete chemical;
        }
        
        chemical = chem;
        hasChemical = true;
        return true;
    }
    else if ( !hasChemical && initialState ) {
        if ( chemical ) {
            delete chemical;
        }
        
        chemical = chem;
        hasChemical = true;
        initialState = false;
        return true;
    }
    return false;
}

bool Drawer::removeChemFromDrawer() {
    if ( hasChemical ) {
        delete chemical;

        chemical = new Chemical();
        hasChemical = false;
        return true;
    }

    return false;
}

Chemical* Drawer::getChemical() {
    return chemical;
}

int Drawer::getRow() {
    return row;
}

int Drawer::getColumn() {
    return col;
}

bool Drawer::getHasChemical() {
    return hasChemical;
}

Drawer& Drawer::operator=( const Drawer& right ) {
    if ( &right != this ) { // To avoid self-assignment
        if ( hasChemical ) {
            delete chemical;
        }

        hasChemical = right.hasChemical;
        row = right.row;
        col = right.col;
        initialState = right.initialState;
        *chemical = *right.chemical;
    }

    return *this; // To allow cascading
}