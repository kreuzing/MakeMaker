#include "ProgramTree.h"

ProgramTree::ProgramTree() {
    ProgramClass* currentClass;
    cout << "Enter program name:" << endl;
    getline(cin, programName);
    main = new ProgramClass("main");
    allClasses.push_back(main);
    AddDependents(main);
    for (int i = 1; i < allClasses.size(); i++) {
        AddDependents(allClasses.at(i));
    }
    MakeMakefile();
}

ProgramTree::~ProgramTree() {
    while (!allClasses.empty()) {
        delete allClasses.back();
        allClasses.pop_back();
    }
}

bool ProgramTree::IsInTree(string name) {
    for (int i = 0; i < allClasses.size(); i++) {
        if (name == allClasses.at(i)->GetName()) {
            return true;
        }
    }
    return false;
}

ProgramClass* ProgramTree::GetNode(string name) {
    for (int i = 0; i < allClasses.size(); i++) {
        if (name == allClasses.at(i)->GetName()) {
            return allClasses.at(i);
        }
    }
    return nullptr;
}

void ProgramTree::AddDependents(ProgramClass* cC) {
    ProgramClass* currentClass;
    string userIn;
    cout << "Class " << cC->GetName() << endl;
    cout << "Enter dependent classes, -1 when finished:" << endl;
    getline(cin, userIn);
    while (userIn != "-1") {
        if (!IsInTree(userIn)) {
            currentClass = new ProgramClass(userIn);
            allClasses.push_back(currentClass);
        }
        else {
            currentClass = GetNode(userIn);
        }
        cC->AddDependency(currentClass);
        getline(cin, userIn);
    }
}


void ProgramTree::PrintTree() {
    for (int i = 0; i < allClasses.size(); i++) {
        allClasses.at(i)->PrintNode();
    }
}

void ProgramTree::MakeMakefile() {
    int i;
    int j = 0;
    vector<ProgramClass*> listedNodes;
    ofstream fout("MakefileOut"); //rename
    if (!fout.is_open()) {
        return;
    }
    fout << "CC = g++" << endl << endl;
    fout << "CFLAGS = -Wall" << endl << endl;
    fout << "OBJECTS = ";
    for (i = 0; i < allClasses.size(); i++) {
        fout << allClasses.at(i)->GetName() << ".o ";
        j++;
        if (j == 3 && i != allClasses.size() - 1) {
            fout << "\\" << endl << "\t\t";
            j = 0;
        }
    }
    fout << endl << endl;
    fout << programName << " :  $(OBJECTS)" << endl;
    fout << "\t$(CC) $(CFLAGS) -o " << programName << " $(OBJECTS)" << endl << endl;
    for (i = 0; i < allClasses.size(); i++) {
        MakeMakefileNode(allClasses.at(i), fout);
    }
    fout << ".PHONY : clean" << endl;
    fout << "clean :" << endl;
    fout << "\trm " << programName << " $(OBJECTS)";
    fout.close();
}

void ProgramTree::MakeMakefileNode(ProgramClass* node, ofstream& fout) {
    int i;
    fout << node->GetName() << ".o : ";
    if (node->GetIsMain()) {
        fout << "main.cpp ";
    }
    else {
        fout << node->GetName() << ".h ";
    }
    if (node->GetHasDependencies()) {
        MakeMakefileDependencies(node, fout);
    }
    fout << endl;
    if (node->GetIsMain()) {
        fout << "\t$(CC) $(CFLAGS) -c main.cpp" << endl;
    }
    fout << endl;
}

void ProgramTree::MakeMakefileDependencies(ProgramClass* node, ofstream& fout) {
    if (!node->GetHasDependencies()) {
        return;
    }
    vector<ProgramClass*> nodeDependencies = node->GetDependencies();
    for (int i = 0; i < nodeDependencies.size(); i++) {
        fout << nodeDependencies.at(i)->GetName() << ".h ";
    }
}