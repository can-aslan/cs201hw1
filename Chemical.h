// Yağız Can Aslan 22001943 CS201-3

#ifndef _CHEMICAL
#define _CHEMICAL

#include <string>
using namespace std;

class Chemical {
    public:
        Chemical( int chemID, int cbnID, string* t, string* loc);
        Chemical();
        ~Chemical();
        int getChemicalID();
        int getCabinetID();
        string getType();
        string getLocation();
        Chemical& operator=( const Chemical& right);
    private:
        int chemicalID;
        int cabinetID;
        string type;
        string location;        
};
#endif // _CHEMICAL