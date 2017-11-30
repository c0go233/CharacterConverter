# CharacterConverter
CharacterConverter is a C++ application that converts English into "Euro-English" 

# Program Action
1. This program takes an argument at the command line. Syntax is `main filein`.

>Arg 1. The name of text file to be read in

2. It will read the file and convert each character based on following rules.
- Replace all ‘c’ with ‘s’ if followed by the characters ‘e’, ‘i’ or ‘y’, otherwise replace with ‘k’.
- Replace all instances of ‘w’ with ‘v’.
- Replace all instances of “ph” with the character ‘f’.
- Replace all double characters with a single instance of the character.
- If a word is more than 3 characters long and ends with an ‘e’ then it can be removed.
- Replace all instances of “th” with ‘z’.
- Replace all instances of “ou” with ‘u’.
- Replace all instances of “ea” with ‘e’.
- If a word ends with “ed” then replace it with ‘d’.

3. It will print the original text read in and then the text after it has been converted to
euro English. It will also print a hash of each piece of text.
