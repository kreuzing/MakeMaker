#ifndef PROGRAMTREE_H
#define PROGRAMTREE_H

#include "ProgramClass.h"
#include <fstream>

class ProgramTree {
    private:
        string programName;
        ProgramClass* main;
        vector<ProgramClass*> allClasses;
    public:
        ProgramTree();
        ~ProgramTree();
        bool IsInTree(string name);
        void AddDependents(ProgramClass* cC);
        ProgramClass* GetNode(string name);
        void PrintTree();
        void MakeMakefile();
        void MakeMakefileNode(ProgramClass* node, ofstream& fout);
        void MakeMakefileDependencies(ProgramClass* node, ofstream& fout);
};


#endif