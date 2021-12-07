// Yağız Can Aslan 22001943 CS201-3

#ifndef _LAB_ORGANIZER
#define _LAB_ORGANIZER

#include "Chemical.h"
#include "Cabinet.h"
#include <string>
using namespace std;

class LabOrganizer{
    public:
        LabOrganizer();
        ~LabOrganizer();

        void addCabinet(int id, int rows, int columns);
        void removeCabinet(int id);
        void listCabinets();
        void cabinetContents(int id);
        void placeChemical(int cabinetId, string location, string chemType, int chemID);
        void findChemical(int id);
        void removeChemical(int id);
        // ...
        //you may define additional member functions and data members, if necessary
        void displayAllChemicalID();
        void addChemical(int id, int* arrSize, int cabinetID, string* type, string* location );
        bool chemicalExists(int id);
        bool cabinetExists(int id);
        bool removeChemFromLab(int id);
    private:
        int cabinetCount;
        int chemCount;
        int* allCabinetID;
        int* allChemID;
        Chemical* chemicals;
        Cabinet* cabinets;
        static string rowNameCharacters;
        static string colNameCharacters;
};
#endif // _LAB_ORGANIZER