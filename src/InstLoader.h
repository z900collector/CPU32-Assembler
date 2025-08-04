/**
 * Load our instructions.
 * Unfortunately there is no Java/PHP Class Introspection available.
 * So do it manually!
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#ifndef InstLoader_Header
#define InstLoader_Header

#include <vector>

// Our Supported Instructions

#include "LDInst.h"
#include "HALTInst.h"
#include "INCDECInst.h"
#include "XORInst.h"
#include "NOPInst.h"

using namespace std;


class InstLoader
{
protected:
        std::vector<Instruction *> *pISet = new std::vector<Instruction *>();           // The list of Instructions we can decode


public:
InstLoader() {}

/**
 *----------------------------------------
 *
 *
 *
 */
vector<Instruction *> * load()
{
        this->pISet->push_back(new HALTInst);
        this->pISet->push_back(new LDInst);
        this->pISet->push_back(new INCDECInst);
        this->pISet->push_back(new NOPInst);
        this->pISet->push_back(new XORInst);
        return this->pISet;
}
};
#endif
