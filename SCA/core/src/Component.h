#ifndef COMPONENT
#define COMPONENT

#include "SCA.h"
#include "Tree.h"

using namespace std;

class Component 
{
private:
	Node* treeRootNode;
	Node* componentRootNode;

	int statementTypeint;
	string statementType;
	Node* startOfStatement;
	string componentType;
	vector<Node*> statementInstances;
	vector<int> startLine;
	int startLineCount;
	vector<int> endLine;
	int endLineCount;
	bool correctComponent;
public:
	// Default Constructor
	Component();
	// Contructor with component root node
	Component(Node* compRtPtr);
	// Constructor with component root node and tree root node
	Component(Node* compRtPtr, Node* treeRtPtr);
	//Pass in 0 for 'iterationStatement' and 1 for 'selectionStatement'.
	void setStatementType(int type);

	//returns statementType in string form.
	string getStatementType();

	//Uses filltokenNodeVector() and statementType to set the start of this component. Also sets componentType off first child node.
	void setStartOfStatement(Node* rt);

	//returns the Node which its data contains the statementType, so the start of the component.
	Node* getStartOfStatement();

	//returns vector of pointers to all nodes in the statement.
	vector<Node*> getStatementInstances();

	//goes to the bottom right node start from start node* and sets endLine.
	void addAnEndLine(Node* start);

	//returns endLine.
	vector<int> getEndLine();

	//returns amount of endLines.
	int getEndLineCount();

	//sets startLine as int start.
	void addAnStartLine(int start);

	//returns startLine.
	vector<int> getStartLine();

	//returns amount of startLines.
	int getStartLineCount();

	//sets if the component is correct or not.
	void setCorrectComponent(bool correct);

	//returns if component is correct or not.
	bool getCorrectComponent();

	//searches from start node to find data, returns first node with the same data in it.
	Node* findNode(string data, Node* start);

	//getComponent => will be overridden in our component classes, returns a string in html format
	string getComponent();

	// accessor Methods
	Node* getTreeRootNode();
	Node* getComponentRootNode();
};

Component::Component() {
	componentRootNode = nullptr;
	treeRootNode = nullptr;
}

Component::Component(Node* compRtPtr) {
	componentRootNode = compRtPtr;
	treeRootNode = nullptr;
}

Component::Component(Node* compRtPtr, Node* treeRtPtr) {
	componentRootNode = compRtPtr;
	treeRootNode = treeRtPtr;
}

Node* Component::getTreeRootNode() {
	return treeRootNode;
}

Node* Component::getComponentRootNode() {
	return componentRootNode;
}

void Component::setStatementType(int type){
	statementTypeint = type;

	if (type == 0)
		statementType = "iterationStatement";
	else if (type == 1)
		statementType = "selectionStatement";
	else
		statementType = "Incorrect input for setStatementType()";
}

string Component::getStatementType() {
	return statementType;
}

void Component::setStartOfStatement(Node* rt)
{
	startOfStatement = rt;

	componentType = startOfStatement->getChild(0)->getData();
}

Node* Component::getStartOfStatement(){
	return startOfStatement;
}

vector<Node*> Component::getStatementInstances() {
	return statementInstances;
}

void Component::addAnEndLine(Node* start)
{
	Node* nodeIter = start;

	while (nodeIter->getChildCount() != 0)
		nodeIter = nodeIter->getChild(nodeIter->getChildCount() - 1);

	endLine[endLineCount] = nodeIter->getLineNum();
	endLineCount++;
}

vector<int> Component::getEndLine() {
	return endLine;
}

int Component::getEndLineCount() {
	return endLineCount;
}

void Component::addAnStartLine(int start) {
	startLine[startLineCount] = start;
	startLineCount++;
}

vector<int> Component::getStartLine() {
	return startLine;
}

int Component::getStartLineCount() {
	return startLineCount;
}

void Component::setCorrectComponent(bool correct) {
	correctComponent = correct;
}

bool Component::getCorrectComponent() {
	return correctComponent;
}

Node* Component::findNode(string data, Node* start)
{
	Node* nodeIter = start;

	if (nodeIter->getData() == data){
		return nodeIter;
	}
	
	if (nodeIter->getChildCount() == 0)
		//no further child nodes
		return nullptr;
	else{
		//more child nodes
		int totalChildren = nodeIter->getChildCount();
	
		for (int i = 0; i < totalChildren; i++) {
			findNode(data, nodeIter->getChild(i));
		}
	}
	
	return nullptr;
}

string Component::getComponent() {
	// override this function
	// will return a string formatted for html
	// use <br /> for line breaks instead of endl or \n
	// Base function returns an empty string
	return "";
}

#endif // !COMPONENT
