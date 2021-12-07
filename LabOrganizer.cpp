// Yağız Can Aslan 22001943 CS201-3

#include <iostream>
#include <string>
#include "LabOrganizer.h"
#include "Chemical.h"
#include "Cabinet.h"
using namespace std;

string LabOrganizer::rowNameCharacters = "ABCDEFGHI";
string LabOrganizer::colNameCharacters = "123456789";

LabOrganizer::LabOrganizer() {
    cabinetCount = 0;
    chemCount = 0;

    allChemID = new int[chemCount];
    allCabinetID = new int[cabinetCount];
    chemicals = new Chemical[chemCount];
    cabinets = new Cabinet[cabinetCount];
}

LabOrganizer::~LabOrganizer() {
    delete [] allChemID;
    delete [] allCabinetID;
    delete [] chemicals;
    delete [] cabinets;
}

void LabOrganizer::addCabinet( int id, int rows, int columns) {
    bool cabinetExist = cabinetExists(id);

    if ( rows < 1 || columns < 1 || rows > 9 || columns > 9 ) {
        cout << "Cannot add the cabinet: Dimensions are out of bounds." << endl;
    }
    else if ( cabinetExist ) {
        cout << "Cannot add the cabinet: ID " << id << " already in the system." << endl;
    }
    else if ( !cabinetExist ) {
        int* tempCabinetID = new int[cabinetCount + 1];
        Cabinet* temp = new Cabinet[cabinetCount + 1];
        Cabinet* cabinetToAdd = new Cabinet( rows, columns, id);

        for ( int i = 0; i < cabinetCount; i++) {
            temp[i] = cabinets[i];
            tempCabinetID[i] = allCabinetID[i];
        }
        temp[ cabinetCount] = *cabinetToAdd;
        tempCabinetID[ cabinetCount] = id;

        cabinetCount++;

        delete [] allCabinetID;
        delete [] cabinets;
        
        allCabinetID = tempCabinetID;
        cabinets = temp;

        cout << "Added a cabinet: ID " << id << " and dimensions " << rows << " to " << columns << "." << endl;
        
        delete cabinetToAdd;
    }
}

void LabOrganizer::removeCabinet(int id) {
    if ( cabinetExists(id) ) {
        int desiredCabinetIndex = -1;
        for ( int i = 0; i < cabinetCount; i++ ) {
            if ( allCabinetID[i] == id ) {
                desiredCabinetIndex = i;
            }
        }

        int* tempCabinetID = new int[ cabinetCount - 1];
        Cabinet* tempCabinets = new Cabinet[ cabinetCount - 1];
        int addedSoFar = 0;

        for ( int j = 0; j < cabinetCount; j++ ) {
            if ( j != desiredCabinetIndex ) {
                tempCabinetID[ addedSoFar] = allCabinetID[j];
                tempCabinets[ addedSoFar] = cabinets[j];
                addedSoFar++;
            }
        }
        cabinetCount--;
        
        if ( desiredCabinetIndex != -1 ) {
            for ( int rw = 0; rw < cabinets[desiredCabinetIndex].getNumOfRows(); rw++ ) {
                for ( int cl = 0; cl < cabinets[desiredCabinetIndex].getNumOfColumns(); cl++ ) {
                    if ( cabinets[desiredCabinetIndex].getDrawers()[rw][cl].getHasChemical() ) {
                        int chemIdToRemove = cabinets[desiredCabinetIndex].getDrawers()[rw][cl].getChemical()->getChemicalID();
                        cabinets[desiredCabinetIndex].removeChemical( chemIdToRemove);
                    }
                }
            }
        }

        delete [] allCabinetID;
        delete [] cabinets;

        cabinets = tempCabinets;
        allCabinetID = tempCabinetID;
        
        cout << "Cabinet " << id << " has been removed." << endl;
    }
    else {
        cout << "Cabinet " << id << " does not exist in the system." << endl;
    }
}

void LabOrganizer::listCabinets() {
    for ( int i = 0; i < cabinetCount; i++ ) {
        cout << "ID: " << cabinets[i].getID() << ", Dim: " << cabinets[i].getNumOfRows() << "x" << cabinets[i].getNumOfColumns() << ", Number of empty slots: " << cabinets[i].getEmptySlots() << endl;
    }
}

void LabOrganizer::cabinetContents(int id) {
    if ( cabinetExists(id) ) {
        for ( int i = 0; i < cabinetCount; i++ ) {
            if ( cabinets[i].getID() == id ) {
                int chemicalsInCabinet = (cabinets[i].getNumOfRows() * cabinets[i].getNumOfColumns()) - cabinets[i].getEmptySlots();
                int chemicalsAddedTemp = 0;
                Chemical* chems = new Chemical[ chemicalsInCabinet];

                for ( int j = 0; j < chemCount; j++ ) {
                    if ( chemicals[j].getCabinetID() == id ) {
                        chems[chemicalsAddedTemp] = chemicals[j];
                        chemicalsAddedTemp++;
                    }
                }

                cout << "ID: " << cabinets[i].getID() << ", Dim: "
                    << cabinets[i].getNumOfRows() << "x" << cabinets[i].getNumOfColumns()
                    << ", Number of empty slots: " << cabinets[i].getEmptySlots() << ". Chemicals: ";

                if ( cabinets[i].getEmptySlots() < (cabinets[i].getNumOfRows() * cabinets[i].getNumOfColumns()) ) {
                    for ( int k = 0; k < chemicalsAddedTemp - 1; k++ ) {
                        cout << chems[k].getLocation() << ": " << chems[k].getChemicalID() << ", ";
                    }
                    cout << chems[chemicalsAddedTemp - 1].getLocation() << ": " << chems[chemicalsAddedTemp - 1].getChemicalID() << ".";
                }
                else {
                    cout << "No chemicals present in the cabinet.";
                }
                
                cout << endl;
                cout << cabinets[i];

                delete [] chems;
            }
        }
    }
    else {
        cout << "Cabinet " << id << " does not exist in the system." << endl;
    }
}

void LabOrganizer::placeChemical(int cabinetId, string location, string chemType, int chemID) {
    if ( !chemicalExists( chemID) ) {
        addChemical( chemID, &chemCount, cabinetId, &chemType, &location);
    }
    else {
        cout << "Chemical with ID " << chemID << " already exists in the system." << endl;
    }
}

void LabOrganizer::findChemical(int id) {
    if ( !chemicalExists( id) ) {
        cout << "Chemical with ID " << id << " does not exist in the system." << endl;
    }
    else {
        for ( int i = 0; i < chemCount; i++ ) {
            if ( chemicals[i].getChemicalID() == id ) {
                cout << "Chemical " << id << " is at location " << chemicals[i].getLocation() << " in cabinet " << chemicals[i].getCabinetID() << "." << endl;
            }
        }
    }
}

void LabOrganizer::removeChemical(int id) {
    if ( !removeChemFromLab(id) ) {
        cout << "Chemical with ID " << id << " does not exist in the system." << endl;
    }
}

bool LabOrganizer::chemicalExists(int id) {
    for ( int i = 0; i < chemCount; i++ ) {
        if ( id == allChemID[i] ) {
            return true;
        }
    }
    
    return false;
}

bool LabOrganizer::cabinetExists(int id) {
    for ( int i = 0; i < cabinetCount; i++ ) {
        if ( id == allCabinetID[i] ) {
            return true;
        }
    }
    
    return false;
}

bool LabOrganizer::removeChemFromLab(int id) {
    if ( chemicalExists( id) ) {
        int* tempID = new int[ chemCount - 1];
        Chemical* tempChemicals = new Chemical[ chemCount - 1];

        for ( int i = 0; i < chemCount; i++ ) { // For every chemical
            if ( chemicals[i].getChemicalID() == id ) { // If chemical id is desired id
                for ( int j = 0; j < cabinetCount; j++ ) { // Check every cabinet
                    if ( cabinets[j].getID() == chemicals[i].getCabinetID() ) {
                        cabinets[j].removeChemical( id);
                    }
                }
            }
        }

        int added = 0;
        for ( int j = 0; j < chemCount; j++ ) {
            if ( allChemID[j] != id ) {
                tempID[added] = allChemID[j];
                tempChemicals[added] = chemicals[j];
                added++;
            }
        }
        chemCount = chemCount - 1;

        delete [] allChemID;
        delete [] chemicals;
        
        allChemID = tempID;
        chemicals = tempChemicals;
        
        return true;
    }

    return false;
}

void LabOrganizer::displayAllChemicalID() {
    for ( int i = 0; i < chemCount; i++ ) {
        cout << allChemID[i] << endl;
    }
    cout << endl;
}

void LabOrganizer::addChemical(int id, int* arrSize, int cabinetID, string* type, string* location ) {
    int* tempID = new int[ *arrSize + 1];
    Chemical* tempChemicals = new Chemical[ *arrSize + 1];
    Chemical* chemicalToAdd = new Chemical( id, cabinetID, type, location);

    if ( cabinetExists( cabinetID) ) {
        int locationRow = rowNameCharacters.find( (*location).substr(0,1));
        int locationColumn = colNameCharacters.find( (*location).substr(1));

        for ( int j = 0; j < cabinetCount; j++ ) {
            if ( cabinets[j].getID() == cabinetID ) {
                if ( !cabinets[j].addChemicalToCabinet( chemicalToAdd, locationRow, locationColumn) ) {
                    
                    delete [] tempID;
                    delete [] tempChemicals;
                    delete chemicalToAdd;
                    return;
                }
            }
        }
    }
    else {
        cout << "Could not place chemical with ID " << id << ". Cabinet with ID " << cabinetID << " does not exist in the system." << endl;
        
        delete [] tempID;
        delete [] tempChemicals;
        delete chemicalToAdd;
        return;
    }
    
    for ( int j = 0; j < *arrSize; j++ ) {
        tempID[j] = *(allChemID + j);
        tempChemicals[j] = *(chemicals + j);
    }

    tempID[ *arrSize] = id;
    tempChemicals[ *arrSize] = *chemicalToAdd;
    *arrSize = *arrSize + 1;

    delete [] allChemID;
    delete [] chemicals;

    chemicals = tempChemicals;
    allChemID = tempID;
}