#include <iostream>
#include <fstream>
#include <iterator>
#include <ctype.h>
#include "converter.h"

using namespace std;

const char ruleOneCompareChars[] = {'E', 'I', 'Y', '\0'};

void processExtraction(ifstream &fin, list<char> &myList);
bool extractLetter(const char *fileName, list<char> &myList, string &finalMessage);
void putMessage (list<char> &myList);
void displayConvertResult(list<char> &myList);
bool gnrlCon(char base, char comCh, char conCh, list<char>::iterator &itr, list<char> &myList);
void processConversion(list<char> &myList);
void convertRuleOne(list<char>::iterator &itr);
bool isThisChar(list<char>::iterator &itr, char compareChar);
void convertCharTo(list<char>::iterator &itr, const char convertChar);
void removeNextNode(list<char>::iterator &itr, list<char> &myList);
bool convertRuleFour(list<char>::iterator &itr, list<char> &myList);
bool isFollowedBy(list<char>::iterator &itr, const char *characters);
bool convertRuleFive(list<char>::iterator &itr, list<char> &myList, char compareChar);
void getToLastWord (list<char>::iterator &itr);
int getWordCount(list<char>::iterator &itr, list<char> &myList);
unsigned short getHash(const list<char> &charList);
void convertChar(list<char>::iterator itr, list<char> &myList);
bool ruleNineCon(list<char>::iterator itr, list<char> &myList, char secComCh, char lastComCh);
bool checkRuleNineWords(char secComCh, char lastComCh, list<char>::iterator itr);

converter::converter() {}

void putMessage (list<char> &myList)
{
   list<char>::const_iterator itr;
   cout << '\n';
   for (itr = myList.begin(); itr != myList.end(); itr++ ) {
   cout << *itr;
   }
   cout << '\n';
   cout << "Hash = "<< getHash(myList) << endl;
}

string converter::convert(const char *fileName)
{
   string errorMsg = "";
   bool extractFlag = extractLetter(fileName, myList, errorMsg);
   if (!extractFlag)
   {
      return errorMsg;
   }
   displayConvertResult(myList);
   return errorMsg;
}

void displayConvertResult(list<char> &myList)
{
   putMessage(myList);
   processConversion(myList);
   putMessage(myList);
}

void processConversion(list<char> &myList)
{
   list<char>::iterator itr;
   for (itr = myList.begin(); itr != myList.end(); ++itr)
   {
      convertChar(itr, myList);
   }
}

void convertChar(list<char>::iterator itr, list<char> &myList)
{
   bool finishedFlag = false;
   while(!finishedFlag)
   {
      if(isThisChar(itr, 'c')) convertRuleOne(itr);
      else if(isThisChar(itr, 'w')) convertCharTo(itr, 'v');
      else if(gnrlCon('p', 'h', 'f', itr, myList)) {}
      else if(convertRuleFour(itr, myList)) {}
      else if(convertRuleFive(itr, myList, 'e')) {}
      else if(gnrlCon('t', 'h', 'z', itr, myList)) {}
      else if(gnrlCon('o', 'u', 'u', itr, myList)) {}
      else if(gnrlCon('e', 'a', 'e', itr, myList)) {}
      else if(ruleNineCon(itr, myList, 'e', 'd')) {}
      else finishedFlag = true;
   }
}

void convertRuleOne(list<char>::iterator &itr)
{
   bool nextCharFlag = isFollowedBy(itr, ruleOneCompareChars);
   char convertChar = 'k';
   if (nextCharFlag)
   {
      convertChar = 's';
   }
   convertCharTo(itr, convertChar);
}

bool isFollowedBy(list<char>::iterator &itr, const char *compareChars)
{
   char tempNextChar = *(++itr);
   char upperNextChar = toupper(tempNextChar);
   --itr;
   for(int i = 0; compareChars[i] != '\0'; i++)
   {
      if(tempNextChar == compareChars[i])
      {
         return true;
      }
   }
   return false;
}

bool ruleNineCon(list<char>::iterator itr, list<char> &myList, char secComCh, char lastComCh)
{
   list<char>::iterator tempItr = itr;
   bool wordsFlag = checkRuleNineWords(secComCh, lastComCh, tempItr);
   if(wordsFlag)
   {
      *itr = *(++tempItr);
      myList.erase(tempItr);
      return true;
   }
   return false;
}

bool checkRuleNineWords(char secComCh, char lastComCh, list<char>::iterator itr)
{
   list<char>::iterator originalItr = itr;
   bool secCompareFlag = isThisChar(originalItr, secComCh);
   ++originalItr;
   bool lastCompareFlag = isThisChar(originalItr, lastComCh);
   char nextToLastWord = *(++originalItr);
   bool nextToLastWordFlag = false;
   if(isspace(nextToLastWord) || ispunct(nextToLastWord))
   {
      nextToLastWordFlag = true;
   }
   if(secCompareFlag && lastCompareFlag && nextToLastWordFlag)
   {
      return true;
   }
   return false;
}

bool convertRuleFour(list<char>::iterator &itr, list<char> &myList)
{
   char firstChar = *itr;
   char nextChar;
   bool nextCharFlag = false;
   if(isalpha(firstChar))
   {
      nextChar = *(++itr);
      --itr;
      nextCharFlag = isThisChar(itr, nextChar);
   }
   if(nextCharFlag)
   {
      removeNextNode(itr, myList);
      return true;
   }
   return false;
}

void getToLastWord (list<char>::iterator &itr)
{
   while(isalpha(*itr))
   {
      ++itr;
   }
   --itr;
}

bool convertRuleFive(list<char>::iterator &itr, list<char> &myList, char compareChar)
{
   list<char>::iterator originalItr = itr;
   getToLastWord(itr);
   bool charFlag = isThisChar(itr, compareChar);
   int wordCount = 0;
   if(charFlag)
   {
      wordCount = getWordCount(itr, myList);
   }
   if (wordCount > 3)
   {
      myList.erase(itr);
      itr = originalItr;
      return true;
   }
   itr = originalItr;
   return false;
}

int getWordCount(list<char>::iterator &itr, list<char> &myList)
{
   list<char>::iterator originalItr = itr;
   list<char>::iterator start = myList.begin();
   int count = 0;
   do
   {
      if(isalnum(*itr))
      {
         count++;
      }
      --itr;
   }
   while(itr != start && !isspace(*itr));
   if(itr == start && !isspace(*itr))
   {
      count++;
   }
   itr = originalItr;
   return count;
}

bool isThisChar(list<char>::iterator &itr, char compareChar)
{
   char tempChar = *itr;
   char upperChar = toupper(tempChar);
   char upperCompareChar = toupper(compareChar);
   return upperChar == upperCompareChar;
}

bool gnrlCon(char base, char comp, char conCh, list<char>::iterator &itr, list<char> &myList)
{
   bool baseCharFlag = isThisChar(itr, base);
   list<char>::iterator tempNextItr = ++itr;
   bool nextCharFlag = isThisChar(tempNextItr, comp);
   --itr;
   if (baseCharFlag && nextCharFlag)
   {
      convertCharTo(itr, conCh);
      removeNextNode(itr, myList);
      return true;
   }
   return false;
}

void removeNextNode(list<char>::iterator &itr, list<char> &myList)
{
   list<char>::iterator originalItr = itr;
   ++itr;
   itr = myList.erase(itr);
   itr = originalItr;
}

void convertCharTo(list<char>::iterator &itr, char convertChar)
{
   bool caseFlag = isupper(*itr);
   if(caseFlag)
   {
      convertChar = toupper(convertChar);
   }
   *itr = convertChar;
}

bool extractLetter(const char *fileName, list<char> &myList, string &errorMsg)
{
   std::ifstream fin(fileName);
   if (!fin)
   {
      errorMsg = "Can't open file Error";
      return false;
   }
   processExtraction(fin, myList);
   return true;
}

void processExtraction(ifstream &fin, list<char> &myList)
{
   char tempLetter;
   while(fin.get(tempLetter))
   {
      if(fin.good())
      {
         myList.push_back(tempLetter);
      }
   }
}

unsigned short getHash(const list<char> &charList)
{
   unsigned short shift, hash = 0;
   list<char>::const_iterator itr;
   
   for (itr = charList.begin(); itr != charList.end(); itr++)
   {
      hash ^= *itr;
      shift = (hash & 15);
      hash = (hash << shift) | (hash >> (16 - shift));
   }
   return hash;
}

converter::~converter()
{
   myList.clear();
}









