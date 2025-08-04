#ifndef GlobalParameters_Header
#define GlobalParameters_Header

#include <string>

using namespace std;

class GlobalParameters
{
private:
    GlobalParameters() {}
    GlobalParameters(const GlobalParameters&) = delete;
    GlobalParameters& operator=(const GlobalParameters&) = delete;

    static GlobalParameters* instance;

/* These are our "Global" parameters used in all other classes */

        bool _dump_labels = false;
        bool _print_line_numbers=false;
        string _source_file;
        string _output_file;
public:

static GlobalParameters* getInstance();
void setDumpFlag(bool f);
bool getDumpFlag();
void setLineNumberFlag( bool f);
bool getLineNumberFlag();

void setInputFile(string f);
string getInputFile();

void setOutputFile(string f);
string getOutputFile();
};
#endif
