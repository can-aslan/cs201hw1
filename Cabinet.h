// Yağız Can Aslan 22001943 CS201-3

#ifndef _CABINET
#define _CABINET

#include "Drawer.h"
#include "Chemical.h"
#include <string>
using namespace std;

class Cabinet{
    friend ostream& operator<<( ostream& , Cabinet& );
    
    public:
        Cabinet(int r, int c, int idNum);
        //Cabinet( const Cabinet&);
        Cabinet();
        ~Cabinet();
        void setEmptySlots(int newSlots);
        void setId(int id);
        void setNumOfRows(int num);
        void setNumOfColumns(int num);
        void findClosestLocations( Chemical*& chemical, const int r, const int c);
        int getID();
        int getEmptySlots();
        int getNumOfRows();
        int getNumOfColumns();
        int findDistance(int x0, int y0, int x1, int y1);
        bool addChemicalToCabinet( Chemical*& chemical, const int r, const int c);
        bool removeChemical(int id);
        bool checkForCombustiveChemical( int r, int c);
        bool hasChemical(int r, int c);
        char* getColNames();
        char* getRowNames();
        Drawer** getDrawers();
        Cabinet& operator=( const Cabinet& right);
    private:
        int numOfEmptySlots;
        int id;
        int numOfRows;
        int numOfCols;
        char* rowNames;
        char* colNames;
        string rowNameCharacters;
        string colNameCharacters;
        Drawer** drawers;
};
#endif // _CABINET