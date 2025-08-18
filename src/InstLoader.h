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
#include "Logger.h"

// Our Supported Instructions

#include "LDInst.h"
#include "HALTInst.h"
#include "INCDECInst.h"
#include "XORInst.h"
#include "NOPInst.h"
#include "PUSHInst.h"
#include "POPInst.h"
#include "BSETInst.h"
#include "BCLRInst.h"
#include "BTSTInst.h"
#include "CALLInst.h"
#include "RETInst.h"
#include "RSPInst.h"
//NEXT_ENTRY

using namespace std;


class InstLoader
{
protected:
//
//The list of Instructions we can decode
//
std::vector<Instruction *> *pISet = new std::vector<Instruction *>();
Logger *pLog;


public:
InstLoader()
{
	this->pLog = Logger::getInstance();
	this->pLog->LogMsg("InstLoader() Constructor");
}

/**
 *----------------------------------------
 *
 *
 *
 */
vector<Instruction *> * load()
{
	this->pLog->LogFunction("InstLoader::load()");
	this->pISet->push_back(new NOPInst);
	this->pISet->push_back(new LDInst);
//NEXT_PUSH_BACK
	this->pISet->push_back(new RSPInst);
	this->pISet->push_back(new PUSHInst);
	this->pISet->push_back(new POPInst);
	this->pISet->push_back(new RETInst);
	this->pISet->push_back(new CALLInst);
	this->pISet->push_back(new INCDECInst);
	this->pISet->push_back(new XORInst);
	this->pISet->push_back(new BSETInst);
	this->pISet->push_back(new BCLRInst);
	this->pISet->push_back(new BTSTInst);
	this->pISet->push_back(new HALTInst);
	this->pLog->LogMsg("Load Complete - return ISet object");
	return this->pISet;
}
};
#endif
