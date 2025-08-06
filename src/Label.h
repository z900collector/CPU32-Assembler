/**
 * Define a "label" used in the .asm file. 
 * Labels have a name and a location. 
 *
 * Label objects will be stored in a STL vector.
 *
 * If we hit a label reference in the file before the label 
 * we keep track of the label and the PC it was requested for
 * then back fill at the end. If we never envounter the label
 * definition, then we flag an error.
 *
 *
 * (C) Sid Young
 * Free for non-commercial use.
 */
#ifndef	Label_class
#define	Label_class

#include <string>

class Label
{
private:
unsigned int _label_location;
std::string  _label_name = "";
bool         _label_valid = false;

public:
Label();
Label( std::string n, unsigned loc);


bool isDefined();
std::string getName();
void setName(std::string n);
unsigned getLocation() const;
void setLocation(unsigned loc);
};

#endif
