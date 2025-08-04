/**
 * Represents a Label (Program Counter location)
 *
 * When no value is yet available:
 * - the label value is set to 0
 * - the _label_valid =0
 *
 * Each time we encounter a label, grab the PC value.
 * - set the location
 * - set _label_valid to 1
 *
 * If we encounter a request to use a label and we don't
 * have the label address, we save the location of the
 * PC and back fill it at the end.
 *
 * (C) Sid Young 2025
 * Free for non-commercial use.
 */

#include <string>
#include "Label.h"


Label::Label()
{
        this->_label_location = 0;
        this->_label_valid = false;
        this->_label_name="undefined";
}

Label::Label( std::string n, unsigned loc)
{
        this->_label_location = loc;
        this->_label_valid = true;
        this->_label_name=n;
}


/**
 *------------------------------------------------------------
 * Has the location value been set yet?
 *
 * 0=not valid
 */
bool Label::isDefined()
{
        return this->_label_valid;
}



/**
 *------------------------------------------------------------
 * Label name accessor/mutator
 *
 */
std::string Label::getName()
{
        return this->_label_name;
}

void Label::setName(std::string n)
{
        this->_label_name=n;
}


/**
 *------------------------------------------------------------
 * Label memory location accessor/mutator
 *
 */
unsigned Label::getLocation() const
{
        return this->_label_location;
}


void Label::setLocation(unsigned loc)
{
        this->_label_location = loc;
        this->_label_valid = true;
}
/* End of file */
