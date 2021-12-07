// Yağız Can Aslan 22001943 CS201-3

#include <iostream>
#include <string>
#include <cmath>
#include "Cabinet.h"
#include "Chemical.h"
using namespace std;

Cabinet::Cabinet( int r, int c, int idNum) {
    rowNameCharacters = "ABCDEFGHI";
    colNameCharacters = "123456789";

    rowNames = new char[r];
    for ( int rw = 0; rw < r; rw++ ) {
        rowNames[rw] = rowNameCharacters[rw];
    }

    colNames = new char[c];
    for ( int cl = 0; cl < c; cl++ ) {
        colNames[cl] = colNameCharacters[cl];
    }

    id = idNum;
    numOfRows = r;
    numOfCols = c;
    numOfEmptySlots = numOfCols * numOfRows;

    drawers = new Drawer* [numOfRows];
    for ( int i = 0; i < numOfRows; i++ ) {
        drawers[i] = new Drawer[numOfCols];
    }

    for ( int i = 0; i < numOfRows; i++ ) {
        for ( int j = 0; j < numOfCols; j++ ) {
            Drawer* tempDrawer = new Drawer( i, j);
            drawers[i][j] = *tempDrawer;
            delete tempDrawer;
        }
    }
}

Cabinet::Cabinet() {
    rowNameCharacters = "ABCDEFGHI";
    colNameCharacters = "123456789";

    rowNames = new char[0];
    colNames = new char[0];

    id = 0;
    numOfRows = 0;
    numOfCols = 0;
    numOfEmptySlots = 0;
    
    drawers = new Drawer* [numOfRows];
    for ( int i = 0; i < numOfRows; i++ ) {
        drawers[i] = new Drawer[numOfCols];
    }

    for ( int i = 0; i < numOfRows; i++ ) {
        for ( int j = 0; j < numOfCols; j++ ) {
            Drawer* tempDrawer = new Drawer( i, j);
            drawers[i][j] = *tempDrawer;
            delete tempDrawer;
        }
    }
}

Cabinet::~Cabinet() {
    for ( int i = 0; i < numOfRows; i++ ) {
        delete [] drawers[i];
    }

    delete [] drawers;
    delete [] rowNames;
    delete [] colNames;
}

bool Cabinet::removeChemical( int id) {
    for ( int i = 0; i < numOfRows; i++ ) {
        for ( int j = 0; j < numOfCols; j++ ) {
            if ( hasChemical(i, j) && drawers[i][j].getChemical()->getChemicalID() == id ) {
                cout << "Chemical " << drawers[i][j].getChemical()->getChemicalID() << " removed from cabinet " << drawers[i][j].getChemical()->getCabinetID() << "." << endl;
                drawers[i][j].removeChemFromDrawer();
                numOfEmptySlots++;

                return true;
            }
        }
    }

    return false;
}

int Cabinet::getID() {
    return id;
}

int Cabinet::getEmptySlots() {
    return numOfEmptySlots;
}

void Cabinet::setEmptySlots( int newSlots) {
    numOfEmptySlots = newSlots;
}

int Cabinet::findDistance( int x0, int y0, int x1, int y1) {
    /* IMPORTANT EXPLANATION
        This algorithm finds the closest distance mathematically to the given two "shelves"
        in the cabinet by taking them as points on the x-y coordinate plane.

        Here, it is considered that;
            x0 = Row Index of first point
            y0 = Column Index of first point

            x1 = Row Index of second point
            y1 = Column Index of second point.
        
        If the points are on either the same column or the same row,
        the distance between them is the absolute of the subtraction
        of their row indexes or column indexes respectively. Since
        both the rows and columns of both points are integers, the result
        of these cases are 100% integers, therefore the value obtained can
        be returned directly.

        However, if the points are not on the same column or row, then,
        Pythagoras' Theorem is used to calculate the distance;
                c^2      =    a^2    +   b^2
            (distance)^2 = (x1-x0)^2 + (y1-y0)^2
            distance = (sqrt)((x1-x0)^2 + (y1-y0)^2).

        Since the obtained result in this case is the square root of an integer,
        the result is not guaranteed to be an integer and therefore the result
        needs to be rounded to the closest whole number to return the distance as
        an integer.

        In the sample output given in the homework PDF file, there is the following line;
            "Location A3 in cabinet 102 is not suitable for a combustive chemical. Nearest possible locations for this chemical: D1, D2, D3"
        Where the Cabinet 102 looks like the following;
              1 2 3
            A + + +
            B + c +
            C + + r
            D + + +
            E + + +
        If we calculate the distance of D1, D2 and D3 to A3 mathematically, we find the following (Row D Index = 3, Column Index = Column Name - 1):
        Distance of A3 to D3: (abs)(y1-y0) = (abs)(3-0) = 3,
        Distance of A3 to D2: (sqrt)((1-2)^2 + (3-0)^2) = (sqrt)((-1)^2 + (3)^2) = (sqrt)(1 + 9) = (sqrt)(10) = 3.162... which is then rounded to 3,
        Distance of A3 to D1: (sqrt)((0-2)^2 + (3-0)^2) = (sqrt)((-2)^2 + (3)^2) = (sqrt)(4 + 9) = (sqrt)(13) = 3.605... which is then rounded to 4. <----!!!!!!!!!!!!!

        It can be calculated that the relations between rounded distances of D1, D2 and D3 to A3 is as the following;
            D1 > D2 = D1.
            4  >  3 =  3.

        Hence, the mathematical output of the program should be: 
            "Location A3 in cabinet 102 is not suitable for a combustive chemical. Nearest possible locations for this chemical: D2, D3".
    END OF IMPORTANT EXPLANATION */
    if ( x0 == x1 ) { // Points on the same column
        return abs( y0 - y1);
    }
    else if ( y0 == y1 ) { // Points on the same row
        return abs( x0 - x1);
    }
    else {
        double result;
        int x2, y2;
        x2 = (x1 - x0) * (x1 - x0);
        y2 = (y1 - y0) * (y1 - y0);

        result = x2 + y2;
        result = sqrt(result);

        return round(result);
    }
}

bool Cabinet::hasChemical(int r, int c) {
    return drawers[r][c].getHasChemical();
}

void Cabinet::findClosestLocations( Chemical*& chem, const int r, const int c) {
    if ( chem->getType() == "combustive" ) { // Combustive Chemical
        // Find closest chem
        int minDistance = 15; // Since maximum cabinet size is 10x10, the maximum actual distance is 10sqrt(2) = 14.
        int minDistanceCount = 0;
        int possiblePlaces = 0;
        for ( int i = 0; i < numOfRows; i++ ) {
            for ( int j = 0; j < numOfCols; j++ ) {
                if ( i != r || j != c ) {
                    int tempDistance = findDistance(r, c, i, j);
                    if ( tempDistance < minDistance && !hasChemical(i, j) && checkForCombustiveChemical( i, j) ) {
                        minDistance = tempDistance;
                        minDistanceCount = 1;
                    }
                    else if ( tempDistance == minDistance ) {
                        minDistanceCount++;
                    }
                }
            }
        }

        string* minDistanceLocations = new string[minDistanceCount];
        string tempLocation = "";
        int locationAdded = 0;
        for ( int i = 0; i < numOfRows; i++ ) {
            for ( int j = 0; j < numOfCols; j++ ) {
                if ( i != r || j != c ) {
                    int tempDistance = findDistance(r, c, i, j);
                    if ( (tempDistance == minDistance) && !hasChemical(i, j) && checkForCombustiveChemical( i, j) ) {
                        tempLocation.append(1, rowNames[i]).append(1, colNames[j]);
                        minDistanceLocations[ locationAdded] = tempLocation;
                        locationAdded++;
                        possiblePlaces++;
                        tempLocation = "";
                    }
                }
            }
        }

        string message = "";
        cout << "Location " << message.append(1, rowNames[r]).append(1, colNames[c]) << " not suitable for a " << chem->getType() << " chemical." << endl;
        if ( possiblePlaces ) {
            cout << "Nearest possible locations for this chemical: ";

            for ( int index = 0; index < possiblePlaces - 1; index++ ) {
                cout << minDistanceLocations[index] << ", ";
            }
            cout << minDistanceLocations[possiblePlaces - 1] << ".";

            cout << endl;
        }

        delete [] minDistanceLocations;
    }
    else { // Retardant Chemical
        // Find closest chem
        int minDistance = 15; // Since maximum cabinet size is 10x10, the maximum actual distance is 10sqrt(2) = 14.
        int minDistanceCount = 0;
        int possiblePlaces = 0;
        for ( int i = 0; i < numOfRows; i++ ) {
            for ( int j = 0; j < numOfCols; j++ ) {
                if ( i != r || j != c ) {
                    int tempDistance = findDistance(r, c, i, j);
                    if ( tempDistance < minDistance && !hasChemical(i, j) ) {
                        minDistance = tempDistance;
                        minDistanceCount = 1;
                    }
                    else if ( tempDistance == minDistance ) {
                        minDistanceCount++;
                    }
                }
            }
        }

        string* minDistanceLocations = new string[minDistanceCount];
        string tempLocation = "";
        int locationAdded = 0;
        for ( int i = 0; i < numOfRows; i++ ) {
            for ( int j = 0; j < numOfCols; j++ ) {
                if ( i != r || j != c ) {
                    int tempDistance = findDistance(r, c, i, j);
                    if ( (tempDistance == minDistance) && !hasChemical(i, j) ) {
                        tempLocation.append(1, rowNames[i]).append(1, colNames[j]);
                        minDistanceLocations[ locationAdded] = tempLocation;
                        locationAdded++;
                        possiblePlaces++;
                        tempLocation = "";
                    }
                }
            }
        }

        string message = "";
        cout << "Location " << message.append(1, rowNames[r]).append(1, colNames[c]) << " not suitable for a " << chem->getType() << " chemical." << endl;
        if ( possiblePlaces ) {
            cout << "Nearest possible locations for this chemical: ";

            for ( int index = 0; index < possiblePlaces - 1; index++ ) {
                cout << minDistanceLocations[index] << ", ";
            }
            cout << minDistanceLocations[possiblePlaces - 1] << ".";

            cout << endl;
        }

        delete [] minDistanceLocations;
    }
}

bool Cabinet::addChemicalToCabinet( Chemical*& chem, const int r, const int c) {
    if ( drawers[r][c].getHasChemical() ) {
        cout << "Could not place chemical with ID " << chem->getChemicalID() << ". The location is already occupied." << endl;
        findClosestLocations( chem, r, c);
        return false;
    }

    string locationOfChem = "";
    locationOfChem = locationOfChem.append(1, rowNames[r]).append(1, colNames[c]);
    
    if ( chem->getType() == "combustive" ) { // Combustive chemical
        if ( checkForCombustiveChemical( r, c) ) {
            // Add Chem
            if ( drawers[r][c].addChemicalToDrawer( chem) ) {
                cout << "Chemical (" << chem->getType() << ") with ID " << chem->getChemicalID() << " has been placed at location " << locationOfChem << " in cabinet " << id << "." << endl;
                numOfEmptySlots--;
                return true;
            }
        }
        else {
            findClosestLocations( chem, r, c);
            return false;
        }
    }
    else { // Retardant chemical
        // Add Chem
        if ( drawers[r][c].addChemicalToDrawer( chem) ) {
            cout << "Chemical (" << chem->getType() << ") with ID " << chem->getChemicalID() << " has been placed at location " << locationOfChem << " in cabinet " << id << "." << endl;
            numOfEmptySlots--;
            return true;
        }
        else {
            findClosestLocations( chem, r, c);
            return false;
        }
    }

    if ( chem->getChemicalID() != -1 ) {
        std::cout << "Chemical could not be added to the cabinet." << endl;
    }
    return false;
}

bool Cabinet::checkForCombustiveChemical( int r, int c) {
    // If in the middle of shelf (not edges)
    if ( r > 0 && r < (numOfRows-1) && c > 0 && c < (numOfCols-1) ) {
        for ( int i = r - 1; i <= r + 1; i++ ) {
            for ( int j = c - 1; j <= c + 1; j++ ) {
                if ( drawers[i][j].getChemical() != NULL ) {
                    string tempType = drawers[i][j].getChemical()->getType().substr(0,1);
                    if ( tempType == "c" ) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    if ( r == 0 ) {
        if ( c == 0 ) { // Top left
            for ( int i = r; i <= r + 1; i++ ) {
                for ( int j = c; j <= c + 1; j++ ) {
                    if ( drawers[i][j].getChemical() != NULL ) {
                        string tempType = drawers[i][j].getChemical()->getType().substr(0,1);
                        if ( tempType == "c" ) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
        else if ( c == (numOfCols-1) ) { // Bottom left
            for ( int i = r; i <= r + 1; i++ ) {
                for ( int j = c - 1; j <= c; j++ ) {
                    if ( drawers[i][j].getChemical() != NULL ) {
                        string tempType = drawers[i][j].getChemical()->getType().substr(0,1);
                        if ( tempType == "c" ) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
        else { // Left middle
            for ( int i = r; i <= r + 1; i++ ) {
                for ( int j = c - 1; j <= c + 1; j++ ) {
                    if ( drawers[i][j].getChemical() != NULL ) {
                        string tempType = drawers[i][j].getChemical()->getType().substr(0,1);
                        if ( tempType == "c" ) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
    }

    if ( r == (numOfRows-1) ) {
        if ( c == 0 ) { // Top right
            for ( int i = r - 1; i <= r; i++ ) {
                for ( int j = c; j <= c + 1; j++ ) {
                    if ( drawers[i][j].getChemical() != NULL ) {
                        string tempType = drawers[i][j].getChemical()->getType().substr(0,1);
                        if ( tempType == "c" ) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
        else if ( c == (numOfCols-1) ) { // Bottom right
            for ( int i = r - 1; i <= r; i++ ) {
                for ( int j = c - 1; j <= c; j++ ) {
                    if ( drawers[i][j].getChemical() != NULL ) {
                        string tempType = drawers[i][j].getChemical()->getType().substr(0,1);
                        if ( tempType == "c" ) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
        else { // Right middle
            for ( int i = r - 1; i <= r; i++ ) {
                for ( int j = c - 1; j <= c + 1; j++ ) {
                    if ( drawers[i][j].getChemical() != NULL ) {
                        string tempType = drawers[i][j].getChemical()->getType().substr(0,1);
                        if ( tempType == "c" ) {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
    }

    if ( c == 0 ) { // Top middle
        for ( int i = r - 1; i <= r + 1; i++ ) {
            for ( int j = c; j <= c + 1; j++ ) {
                if ( drawers[i][j].getChemical() != NULL ) {
                    string tempType = drawers[i][j].getChemical()->getType().substr(0,1);
                    if ( tempType == "c" ) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
    else if ( c == (numOfCols-1) ) { // Bottom middle
        for ( int i = r - 1; i <= r + 1; i++ ) {
            for ( int j = c - 1; j <= c; j++ ) {
                if ( drawers[i][j].getChemical() != NULL ) {
                    string tempType = drawers[i][j].getChemical()->getType().substr(0,1);
                    if ( tempType == "c" ) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    return true;
}

int Cabinet::getNumOfRows() {
    return numOfRows;
}

int Cabinet::getNumOfColumns() {
    return numOfCols;
}

char* Cabinet::getColNames() {
    return colNames;
}

char* Cabinet::getRowNames() {
    return rowNames;
}

Drawer** Cabinet::getDrawers() {
    return drawers;
}

Cabinet& Cabinet::operator=( const Cabinet& right ) {
    if ( &right != this ) { // To avoid self-assignment
        for ( int i = 0; i < numOfRows; i++ ) {
            if ( drawers[i] ) {
                delete [] drawers[i];
            }
        }

        if ( drawers ) {
            delete [] drawers;
        }
        
        if ( rowNames ) {
            delete [] rowNames;
        }
        
        if ( colNames ) {
            delete [] colNames;
        }

        numOfEmptySlots = right.numOfEmptySlots;
        id = right.id;
        numOfRows = right.numOfRows;
        numOfCols = right.numOfCols;
        rowNameCharacters = right.rowNameCharacters;
        colNameCharacters = right.colNameCharacters;

        rowNames = new char[ numOfRows];
        for ( int i = 0; i < numOfRows; i++ ) {
            rowNames[i] = right.rowNames[i];
        }

        colNames = new char[ numOfCols];
        for ( int j = 0; j < numOfCols; j++ ) {
            colNames[j] = right.colNames[j];
        }

        drawers = new Drawer* [numOfRows];
        for ( int i = 0; i < numOfRows; i++ ) {
            drawers[i] = new Drawer[numOfCols];
        }

        for ( int i = 0; i < numOfRows; i++ ) {
            for ( int j = 0; j < numOfCols; j++ ) {
                drawers[i][j] = right.drawers[i][j];
            }
        }
    }
    
    return *this; // To allow cascading
}

ostream& operator<<( ostream& out, Cabinet& cabinet ) {
    out << "  ";

    for ( int i = 0; i <= cabinet.getNumOfRows(); i++ ) {
        for ( int j = 0; j < cabinet.getNumOfColumns(); j++ ) {
            if ( i >= 1 ) {
                if ( j == 0 ) {
                    out << cabinet.getRowNames()[i - 1] << " ";
                }
                
                Chemical* tempChem = cabinet.getDrawers()[i-1][j].getChemical();

                if ( tempChem != NULL && cabinet.getDrawers()[i-1][j].getHasChemical()) {
                    out << tempChem->getType().substr(0,1) << " ";
                }
                else {
                    out << "+ ";
                }
            }
            else {
                out << cabinet.getColNames()[j] << " ";
            }
        }

        out << endl;
    }

    out << endl;
    return out;
}