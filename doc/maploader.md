# Map Loader

## Description

Implement a group of C++ classes that reads and loads a map file in the .maptext file format as found in the “Domination” game source files, available at: http://domination.sourceforge.net/getmaps.shtml. The map loader must be able to read any map file available on the above web page. The map loader should store the map as a graph data structure (see Part 1). The map loader should be able to read any text file (even ones that do not constitute a valid map). All the classes/functions that you implement for this component must all reside in a single .cpp/.hfile duo named MapLoader.cpp/MapLoader.h. You must deliver a file named MapLoaderDriver.cppfile that contains a main function that reads various files and successfully creates a map object for valid map files,and rejects invalid map files of different kinds.

## Requirements

**Part 2 Requirements**
- [ ] Map loader can read any Domination map file.
- [ ] Map loader creates amap object as a graph data structure (see Part 1).
- [ ] Map loader should be ableto read any text file (even invalid ones).
- [ ] Driver reads many different map files, creates a graph object for the valid ones and rejects the invalid ones.

**Project Requirements**
- [ ] All data members of user-defined class type must be of pointer type.
- [ ] All file names and the content of the files must be according to what is given in the description below.
- [ ] All different parts must be implemented in their own separate .cpp/.h file duo. All functions’ implementation must be provided in the .cpp file (i.e. no inline functions are allowed).
- [ ] All classes must implement a correct copy constructor, assignment operator, and stream insertion operator.
- [ ] Memory leaks must be avoided.
- [ ] Code must be documented using comments (user-defined classes, methods, free functions, operators).
- [ ] If you use third-party libraries that are not available in the labs and require setup/installation, you may not assume to have help using them and you are entirely responsible for their proper installation for grading purposes.

---
---

## Valididation Checks
**General**
- [ ] Lines beginning with ';' are ignored
- [ ] File contains '[files]' section
- [ ] File contains '[continents]' section
- [ ] File contains '[countries]' section
- [ ] File contains '[borders]' section
- [ ] Lines beginning with 'test' are in the format 'string' with nothing else on the line
- [ ] Lines beginning with 'name' are in the format 'string string2' with spaces as delimiters, and everything after the first space is string2
- [ ] Lines beginning with 'ver' are in the format 'string int' with spaces as delimiters
- [ ] Lines beginning with 'circle' are in the format 'string int' with spaces as delimiters

**Files Section**
- [ ] Contains exactly one line beginning with 'pic'
- [ ] Contains exactly one line beginning with 'map'
- [ ] Contains exactly one line beginning with 'crd'
- [ ] Contains exactly one line beginning with 'prv'
- [ ] Lines beginning with 'pic' are in the format 'string string' with spaces as delimiters
- [ ] Lines beginning with 'map' are in the format 'string string' with spaces as delimiters
- [ ] Lines beginning with 'crd' are in the format 'string string' with spaces as delimiters
- [ ] Lines beginning with 'prv' are in the format 'string string' with spaces as delimiters

**Continents Section**
- [ ] Each line is in the format "string int string" with spaces as delimters
- [ ] The name of each continent contains no spaces
- [ ] Each continent contains at least 1 country

**Countries Section**
- [ ] Each line is in the format "int string int int" with spaces as delimters
- [ ] Each country belongs to a valid continent
- [ ] The name of each contains contains no spaces

**Borders Section**
- [ ] Each line is in the format "int int int int" with spaces as delimiters
- [ ] The first number in the line is a valid country
- [ ] The remaining numbers are valid countries
- [ ] All countries have at least one country on its borders