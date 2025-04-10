#include "ProgramClass.h"
#include "ProgramTree.h"

int main() {
    ProgramTree* pT = new ProgramTree();
    pT->PrintTree();
    delete pT;
}