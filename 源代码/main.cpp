#include "processingpng.h"
#include "string"
#include "fstream"
string FileName;

int main()
{
    ifstream fin("list.txt");
    while(getline(fin, FileName))
    {
        string OutputName = FileName + ".txt";
        freopen(OutputName.c_str(), "w", stdout);
        if(PngCheck(FileName.c_str()))
        {
            init();
            MakeArray(FileName.c_str());
            EnterToKeyboard(Height/2, 1);

        }
        fclose(stdout);
    }
    fin.close();
    return 0;
}
