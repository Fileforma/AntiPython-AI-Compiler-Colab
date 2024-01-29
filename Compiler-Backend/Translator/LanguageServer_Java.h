#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "../TreeSitterLibrary/lib/include/tree_sitter/api.h"
#define BRANCH_IDENTIFIER 0
#define LEAF_IDENTIFIER   1
uint32_t leafStateTracker = 0;
uint32_t branchStateTracker = 0; 
uint32_t nodeStateTracker = 0;
//Escape these : https://stackoverflow.com/questions/983451/where-can-i-find-a-list-of-escape-characters-required-for-my-json-ajax-return-ty/1021976#1021976
//Uncomment the following line to enable the printf function.
//#define ENABLE_PRINTF
#ifdef ENABLE_PRINTF
    #define    debug_printf(f,...)    printf(f,##__VA_ARGS__)
#else
    #define    debug_printf(f,...)
#endif

char *pythonString;
size_t maxPythonStringLength = 100000;
size_t currentPythonStringLength = 0;


enum JAVA_STATE_MACHINE
{
	AS_KEYWORD,
	BRANCH_NODE,
	CLASS,
	CLASS_BODY,
	CLASS_DECLARATION,
	DECIMAL_INTEGER_LITERAL,
	DOT,
	ERROR,
	FIELD_DECLARATION,
	FROM_KEYWORD,
	IDENTIFIER,
	IMPORT,
	IMPORT_DECLARATION,
	INTEGRAL_TYPE,
	LEAF_NODE,
	LEFT_CURLY_BRACKET,
	LOCAL_VARIABLE_DECLARATION,
	NEW_LINE,
	PROGRAM,
	RIGHT_CURLY_BRACKET,
	SCOPED_IDENTIFIER,
	SCOPED_TYPE_IDENTIFIER,
	SEMICOLON,
	IGNORE_LEAF,
	TYPE_IDENTIFIER,
	VARIABLE_DECLARATOR,
	
	
	STATE_LENGTH
}; 

void AddStateToTracker(uint8_t state, int identifier)
{
	nodeStateTracker <<= 8;
	if(identifier == LEAF_IDENTIFIER)
	{
		leafStateTracker <<= 8;
		leafStateTracker += state;
		nodeStateTracker += LEAF_NODE;
	}
	else if(identifier == BRANCH_IDENTIFIER)
	{
		branchStateTracker <<= 8;
		branchStateTracker += state;
		nodeStateTracker += BRANCH_NODE;
	}
	else{printf("Unknown Identifier\n"); }
}

TSLanguage *tree_sitter_java();
TSParser *javaParser;
TSTree *syntaxTree;
void PrintNode(TSNode node,char *sourceCode)
{
	uint32_t startByte = ts_node_start_byte(node);
	uint32_t endByte   = ts_node_end_byte(node);
	printf("\nNode : %s %u %u\n", ts_node_type(node),startByte,endByte);
	for(int i = startByte; i < endByte; i++)
	{
		printf("%c", sourceCode[i]);
	}
}

void ProcessBranchNode(TSNode node,char *sourceCode)
{
	uint32_t startByte = ts_node_start_byte(node);
	uint32_t endByte   = ts_node_end_byte(node);
	debug_printf("\nBranch Node : %s %u %u\n", ts_node_type(node),startByte,endByte);
	if(strcmp(ts_node_type(node), "ERROR") == 0){return;}
	else if(strcmp(ts_node_type(node), "import_declaration") == 0){AddStateToTracker(IMPORT_DECLARATION,BRANCH_IDENTIFIER);}
	else if(strcmp(ts_node_type(node), "local_variable_declaration") == 0){AddStateToTracker(LOCAL_VARIABLE_DECLARATION,BRANCH_IDENTIFIER);}
	else if(strcmp(ts_node_type(node), "program") == 0){AddStateToTracker(PROGRAM,BRANCH_IDENTIFIER);}
	else if(strcmp(ts_node_type(node), "scoped_identifier") == 0){AddStateToTracker(SCOPED_IDENTIFIER,BRANCH_IDENTIFIER);}

	for(int i = startByte; i < endByte; i++)
	{
		debug_printf("%c", sourceCode[i]);
	}
}

void ProcessLeafNode(TSNode node,char *sourceCode)
{
	uint32_t startByte = ts_node_start_byte(node);
	uint32_t endByte   = ts_node_end_byte(node);
	
	debug_printf("\n\nLeaf Node : %s %u %u\n", ts_node_type(node),startByte,endByte);

	uint8_t previousNode   = (nodeStateTracker >> (8*0)) & 255;
	uint8_t previousLeaf   = (leafStateTracker >> (8*0)) & 255;
	uint8_t previousLeaf1  = (leafStateTracker >> (8*1)) & 255;
	uint8_t previousBranch = (branchStateTracker >> (8*0)) & 255;
	uint8_t previousBranch1= (branchStateTracker >> (8*1)) & 255;
	if(strcmp(ts_node_type(node), "ERROR") == 0){return;}
	else if(strcmp(ts_node_type(node), "import") == 0)
	{
		if(previousBranch1 == FROM_KEYWORD)
		{
			printf(" ");
			pythonString[currentPythonStringLength] = ' ';
			currentPythonStringLength += 1; 
		}
		printf("import ");	
		pythonString[currentPythonStringLength+0] = 'i';
		pythonString[currentPythonStringLength+1] = 'm';
		pythonString[currentPythonStringLength+2] = 'p';
		pythonString[currentPythonStringLength+3] = 'o';
		pythonString[currentPythonStringLength+4] = 'r';
		pythonString[currentPythonStringLength+5] = 't';
		pythonString[currentPythonStringLength+6] = ' ';
		currentPythonStringLength += 7; 			
		AddStateToTracker(IMPORT,LEAF_IDENTIFIER);
	}
	else if(strcmp(ts_node_type(node), "identifier") == 0)
	{	
		AddStateToTracker(IDENTIFIER,LEAF_IDENTIFIER);
		if(previousBranch == IMPORT_DECLARATION && previousLeaf == IMPORT)
		{
			for(int i = startByte; i < endByte; i++)
			{
				printf("%c", sourceCode[i]);
				pythonString[currentPythonStringLength] = sourceCode[i];
				currentPythonStringLength += 1;
			} 
			printf(" ");
			pythonString[currentPythonStringLength] = ' ';
			currentPythonStringLength += 1;
		}
		else if(previousBranch == SCOPED_IDENTIFIER)
		{
			if(endByte - startByte == 3 && sourceCode[startByte+0]=='c' && sourceCode[startByte+1]=='o' && sourceCode[startByte+2]=='m')
			{
				AddStateToTracker(IGNORE_LEAF,LEAF_IDENTIFIER);	
			} 
			else if(endByte - startByte == 9 && sourceCode[startByte+0]=='f' && sourceCode[startByte+1]=='i' && sourceCode[startByte+2]=='l' && sourceCode[startByte+3]=='e' && sourceCode[startByte+4]=='f' && sourceCode[startByte+5]=='o' && sourceCode[startByte+6]=='r' && sourceCode[startByte+7]=='m' && sourceCode[startByte+8]=='a')
			{
				AddStateToTracker(IGNORE_LEAF,LEAF_IDENTIFIER);
			}
			else if(endByte - startByte == 2 && sourceCode[startByte+0]=='a' && sourceCode[startByte+1]=='s')
			{
				AddStateToTracker(AS_KEYWORD,LEAF_IDENTIFIER);
				pythonString[currentPythonStringLength] = ' ';
				currentPythonStringLength += 1;
				printf(" "); for(int i = startByte; i < endByte; i++)
				{
					printf("%c", sourceCode[i]);
					pythonString[currentPythonStringLength] = sourceCode[i];
					currentPythonStringLength += 1;
				
				} printf(" ");
				pythonString[currentPythonStringLength] = ' ';
				currentPythonStringLength += 1;
			}
			else
			{
				for(int i = startByte; i < endByte; i++)
				{
					printf("%c", sourceCode[i]);
					pythonString[currentPythonStringLength] = sourceCode[i];
					currentPythonStringLength += 1;
				}
				if(previousBranch1 == FROM_KEYWORD)
				{
					printf(" ");
					pythonString[currentPythonStringLength] = ' ';
					currentPythonStringLength += 1;
				}
			}
		}
	}
	else if(strcmp(ts_node_type(node), "type_identifier") == 0)
	{
		if(endByte - startByte == 4 && sourceCode[startByte+0]=='f' && sourceCode[startByte+1]=='r' && sourceCode[startByte+2]=='o' && sourceCode[startByte+3]=='m')
		{
			AddStateToTracker(FROM_KEYWORD,BRANCH_IDENTIFIER);
			AddStateToTracker(SCOPED_IDENTIFIER,BRANCH_IDENTIFIER);
			printf("from ");
			pythonString[currentPythonStringLength+0] = 'f';
			pythonString[currentPythonStringLength+1] = 'r';
			pythonString[currentPythonStringLength+2] = 'o';
			pythonString[currentPythonStringLength+3] = 'm';
			pythonString[currentPythonStringLength+4] = ' ';
			currentPythonStringLength += 5; 
		}
	}
	else if(strcmp(ts_node_type(node), ";") == 0)
	{	
		AddStateToTracker(SEMICOLON,LEAF_IDENTIFIER);
		printf("\n");	
		pythonString[currentPythonStringLength+0] = '\n';
		currentPythonStringLength += 1; 
	}
	else if(strcmp(ts_node_type(node), ".") == 0)
	{	
		if(previousLeaf == IGNORE_LEAF){}
		else
		{
			AddStateToTracker(DOT,LEAF_IDENTIFIER);
			printf(".");	
			pythonString[currentPythonStringLength+0] = '.';
			currentPythonStringLength += 1; 
		}

	}
	else
	{
		debug_printf("Unhandled Leaf\n");
	}
	
	for(int i = startByte; i < endByte; i++){debug_printf("%c", sourceCode[i]);}
	debug_printf(" Prev (%d %d) (%d %d)\n",previousBranch,previousBranch1,previousLeaf,previousLeaf1);	
}

void TraverseTree(TSTreeCursor *cursor, char *sourceCode)
{
	TSNode node = ts_tree_cursor_current_node(cursor);
	int childrenCount = ts_node_child_count(node);
	if(childrenCount == 0)
	{
		ProcessLeafNode(node,sourceCode);
	}
	else
	{
		ProcessBranchNode(node,sourceCode);
	}
	if(ts_tree_cursor_goto_first_child(cursor))
	{
		do
		{
			TraverseTree(cursor,sourceCode);
		}while(ts_tree_cursor_goto_next_sibling(cursor));
		ts_tree_cursor_goto_parent(cursor);
	}
}

void ParseCode(size_t sourceLength, char *sourceCode)
{
	if(sourceLength > 0 && sourceCode != NULL)
	{
		assert(javaParser != NULL);
		TSTree *syntaxTree = ts_parser_parse_string(javaParser,NULL,sourceCode,sourceLength);assert(syntaxTree != NULL);
		
		TSNode rootNode = ts_tree_root_node(syntaxTree);
		TSTreeCursor treeCursor = ts_tree_cursor_new(rootNode);
		
		TraverseTree(&treeCursor,sourceCode);
		
		ts_tree_delete(syntaxTree);
		ts_tree_cursor_delete(&treeCursor);
	}
}

