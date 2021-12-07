// Yağız Can Aslan 22001943 CS201-3

#include <iostream>
#include <string>
#include "Chemical.h"
using namespace std;

Chemical::Chemical( int chemID, int cbnID, string* t, string* loc) {
    chemicalID = chemID;
    cabinetID = cbnID;
    type = *t;
    location = *loc;
}

Chemical::Chemical() {
    chemicalID = -1;
    cabinetID = -1;
    type = "+ ";
    location = "00";
}

Chemical::~Chemical() {}

int Chemical::getChemicalID() {
    return chemicalID;
}

int Chemical::getCabinetID() {
    return cabinetID;
}

string Chemical::getType() {
    return type;
}

string Chemical::getLocation() {
    return location;
}

Chemical& Chemical::operator=( const Chemical& right ) {
    if ( &right != this ) { // To avoid self-assignment        
        chemicalID = right.chemicalID;
        cabinetID = right.cabinetID;
        type = right.type;
        location = right.location;
    }
    
    return *this; // To allow cascading
}