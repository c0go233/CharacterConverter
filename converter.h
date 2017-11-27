#ifndef CONVERTER_H
#define CONVERTER_H
#include <string>
#include <list>

class converter
{
   private:
   std::list<char> myList;
   public:
   converter();
   std::string convert(const char *fileName);
   ~converter();
};

#endif // CONVERTER_H
