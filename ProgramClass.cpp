#include "ProgramClass.h"

ProgramClass::ProgramClass(string name) {
    if (name == "main") {
        isMain = true;
    }
    else {
        isMain = false;
    }
    className = name;
    //todo ?
}


void ProgramClass::AddDependency(ProgramClass* newClass) {
    includedClasses.push_back(newClass);
}

void ProgramClass::PrintNode() {
    cout << "Class " << className << " has " << includedClasses.size() << " dependencies";
    if (includedClasses.size() == 0) {
        cout << "." << endl;
        return;
    }
    cout << ": ";
    for (int i = 0; i < includedClasses.size() - 1; i++) {
        cout << includedClasses.at(i)->GetName() << ", ";
    }
    cout << includedClasses.back()->GetName() << "." << endl;
}

bool ProgramClass::HasDependency(ProgramClass* node) {
    for (int i = 0; i < includedClasses.size(); i++) {
        if (node == includedClasses.at(i)) {
            return true;
        }
    }
    return false;
}
