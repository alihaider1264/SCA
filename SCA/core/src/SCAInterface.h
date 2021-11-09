/*
* This interface defines the functionality 
* for a static code analysis tool.
*/

#ifndef SCA_INTERFACE_
#define SCA_INTERFACE_

#include <string>
#include "Node.h"

class SCAInterface{

/** Sees whether file exists on the provided path exists.
    @return True if exists; otherwise returns false. */
   virtual bool existsFile(std::string filePath) const = 0;


/** Loads the template table from templateTableFile into memory.
    @pre  templateTable file exists at the file path.
    @post  a table like data structure is created. std::vector<pair<std::string, std::string>>>
    @param filePath  Path to the TemplateTable file.
    @return  True if data structure created successfully. */
virtual bool loadTemplateTable(std::string templateTableFile) = 0;

/** Loads the source code to be analyzed to the memory. Checks if the source code is a function. If so, attaches a driver to the code that calls the function. Driver only has one function call. Loaded function and driver will be in the same .cpp file which this function returns.
    @pre  source code file exists at the file path.
    @post  None.
    @param filePath  Path to the source code file.
    @return  newly created .cpp file if source code is only a function, otherwise returns the original file. */
virtual std::string loadSourceCode(std::string filePath) = 0;

/** Sends the code to ANTLR and generates two text files. 1) tree 2) errors. Paths to the two text files are stored in the byRef (by reference) inputs.
    @pre  C++ source code file exists.
    @post  a datastructure is created to store the tree generated by ANTLR.
    @param filePath Path to treeTextFile.
    @return  True if read, false otherwise. */
virtual bool serveCodeToANTLR(std::string &treeTxtFilePath, std::string &errorTxtFilePath) = 0;

/** Reads the ANTLR output treeTextFile into memory. Creates a tree in memory. 
    @pre  treeTextFile exists.
    @post  a datastructure is created to store the tree generated by ANTLR.
    @param filePath Path to treeTextFile.
    @return  True if read, false otherwise. */
virtual Node* readANTLROutputTree(std::string &treeTxtFilePath) = 0;

/** Reads the ANTLR output errorTextFile into memory. 
    @pre  errorTextFile exists.
    @post  a datastructure is created to store the errors and warnings read by ANTLR.
    @param filePath Path to errorTextFile.
    @return  True if read, false otherwise. */
virtual bool readANTLROutputErrors(std::string &errorTxtFilePath) = 0;

/** Matches the ANTLR output tree with template table and stores the matches and suggestions (directions) from template table in a text file. 
    @pre  template table & tree exists.
    @post  a text file is created and path to the file returned.
    @param None.
    @return  Path to newly created outputTextFile */
virtual std::string matchTemplateWithTree() const = 0;

/** Create an HTML file from the text file created by matchTemplateWithTree() and store in the same folder.
    @pre  Text file generated by matchTemplateWithTree() exists.
    @post  An HTML file is created and stored in the same folder.
    @param None.
    @return  Path to newly created HTML file */
virtual string createHTMLFile() = 0;
};

#endif