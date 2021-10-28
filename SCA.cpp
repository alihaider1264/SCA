#include "SCA.h"

// Constructor
SCA::SCA(): ast(nullptr), templateTableFile(""), cppFilePath("") {};

// Constructor with parameter for cppFilePath
SCA::SCA(const string& pathToCppFile) {
	cppFilePath = pathToCppFile;
	ast = nullptr;
	templateTableFile = "";
}

SCA::SCA(const string& pathToCppFile, const string& pathToTemplateTable) {
	cppFilePath = pathToCppFile;
	ast = nullptr;
	templateTableFile = pathToTemplateTable;
}

// Undefined Function
bool SCA::existsFile(string filePath) const {
	return true;
}

// Undefined Function
bool SCA::loadTemplateTable(string templateTableFile) {
	TemplateTable* tempTableLoader = new TemplateTable();
	if (tempTableLoader->loadTemplateTable(templateTableFile))
		return true;
	else
		return false;
}

// Undefined Function
string SCA::loadSourceCode(string filePath) {
	return "";
}

bool SCA::serveCodeToANTLR(string& treeTxtFilePath, string& errorTxtFilePath) {
	ANTLR_Server* toAntlr = new ANTLR_Server(cppFilePath);

	if (toAntlr->serveCode(treeTxtFilePath, errorTxtFilePath))
		return true;
	else
		return false;

}

// Undefined Function
Node* SCA::readANTLROutputTree(string& treeTxtFilePath) {
	AST_Parser* ast_parser = new AST_Parser(treeTxtFilePath, cppFilePath);
	Node* rootPtr = nullptr;
	if (ast_parser->testFileExists(treeTxtFilePath)) {
		ast_parser->parseTree();
		rootPtr = ast_parser->getTreeRoot();
		ast_parser->condenseTree(rootPtr);
		ast_parser->getNodeLineNums();

		ast = ast_parser->getTree();
	}
	return rootPtr;
}

// Undefined Function
bool SCA::readANTLROutputErrors(string& errorTxtFilePath) {
	return true;
}

// Undefined Function
string SCA::matchTemplateWithTree() const {
	Template_Matcher templateMatcher;

	TemplateTable* tempTableLoader = new TemplateTable();
	tempTableLoader->loadTemplateTable(templateTableFile);
	
	templateMatcher.setTemplateTable(tempTableLoader->getTemplateTable());
	templateMatcher.setRulesArraySize();
	templateMatcher.checkTreeForErrors(ast->getRoot());

	return templateMatcher.outputSuggestions();
}

// Undefined Function
string SCA::createHTMLFile() {
	return "";
}