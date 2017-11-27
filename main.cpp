#include <iostream>
#include "converter.h"
#include <stdexcept>

using namespace std;

const int FILENAME = 1;

int main(int argc, char* argv[])
{
   if(argc != 2)
   {
      cout << "argc != 2 error" << endl;
      return 1;
   }
   try
   {
      converter myConverter;
      string errorMsg = myConverter.convert(argv[FILENAME]);
      if(!errorMsg.empty())
      {
         cout << "error: " << errorMsg << endl;        
      }
   }
   catch (exception ex)
   {
      cout << "Error: " << ex.what() << endl;
   }
   return 0;
}


