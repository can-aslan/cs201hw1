// Yağız Can Aslan 22001943 CS201-3

#ifndef _DRAWER
#define _DRAWER

#include "Chemical.h"
#include <string>
using namespace std;

class Drawer{
    public:
        Drawer(int r, int c);
        Drawer();
        ~Drawer();
        int getRow();
        int getColumn();
        bool addChemicalToDrawer( Chemical*& chem);
        bool getHasChemical();
        bool removeChemFromDrawer();
        Chemical* getChemical();
        Drawer& operator=( const Drawer& right );
    private:
        int row;
        int col;
        bool hasChemical;
        bool initialState;
        Chemical* chemical;
};
#endif // _DRAWER