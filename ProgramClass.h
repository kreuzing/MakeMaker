#ifndef PROGRAMCLASS_H
#define PROGRAMCLASS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ProgramClass {
    private:
        string className;
        bool isMain; //special case
        vector<ProgramClass*> includedClasses;
    public:
        ProgramClass(string name);
        vector<ProgramClass*> GetDependencies() {return includedClasses;};
        int GetDependencyCount() {return includedClasses.size();}
        bool GetIsMain() {return isMain;};
        bool GetHasDependencies() {return !includedClasses.empty();};
        void AddDependency(ProgramClass* newClass);
        string GetName() {return className;};
        void PrintNode();
        bool HasDependency(ProgramClass* node);
};

#endif