#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <string>

#define STACK_IMPLEMENTATION
#include "stack.h"

#define printp(x) std::cout<<x
#define println(x) std::cout<<x<<std::endl
#define printerr(x) std::cerr<<x<<std::endl

enum OP_CODE {
	PLUS,
	MINUS,
	DIVIDE,
	MUL,
	PRINT
};

OP tokenize(std::string token){
	int tokenValue;
	OP_TYPE type = COMMAND;
	      if (token == "+"){
		tokenValue = PLUS;
	}else if (token == "-"){
		tokenValue = MINUS;
	}else if (token == "*"){
		tokenValue = MUL;
	}else if (token == "/"){
		tokenValue = DIVIDE;
	}else if (token == "."){
		tokenValue = PRINT;
	}else{
		tokenValue = std::stoi(token);
		type  = LITERAL;
	}
	OP op{
		.type = type,
		.value = tokenValue
	};

	return op;
}

std::vector<OP> lexLine(std::string line){
	std::vector<OP> tokens;
	std::string token;
	line+= " ";
	for (char t: line){
		if (t == 32 || t == '\t' || t == ',' || t == '(' || t == ')'){
			if (!token.size() > 0){
				continue;
			}
			tokens.push_back(tokenize(token));
			token = "";
			continue;
		}
		token += t;
	}
	return tokens;
}

void execute(Stack program){
	Stack exect;
	for(int i=0; i < program.count; i++){
		if (program.ops[i].type == LITERAL){;
			exect.push(program.ops[i]);
		}
		if (program.ops[i].type == COMMAND){
			switch(program.ops[i].value){
				case PLUS:
					{
						int a = (exect.pop()).value;
						int b = (exect.pop()).value;
						OP op{
							.type =LITERAL,	
							.value = a+b	
						};
						exect.push(op);
						break;
					}
				case MINUS:
					{
						int a = (exect.pop()).value;
						int b = (exect.pop()).value;
						OP op{
							.type =LITERAL,	
							.value = a-b	
						};
						exect.push(op);
						break;
					}
				case DIVIDE:
					{
						int a = (exect.pop()).value;
						int b = (exect.pop()).value;
						OP op{
							.type =LITERAL,	
							.value = b/a	
						};
						exect.push(op);
						break;
					}
				case MUL:
					{
						int a = (exect.pop()).value;
						int b = (exect.pop()).value;
						OP op{
							.type =LITERAL,	
							.value = a*b	
						};
						exect.push(op);
						break;
					}
				case PRINT:
					{
						int a = (exect.pop()).value;
						println(a);
						break;
					}
				
				default:
					printp("Invalid Command");
					exit(1);
					break;
			}	
		}
	}
}

int main(int argc, char* argv[]){
	
	assert( argc >= 2 );
	std::string filename = argv[1];
	Stack program;
	
	std::ifstream file(filename);
	if (!file.is_open()) { 
		printerr("Could not open file: " << filename); 
		return 1; 
	} 

	std::string line;
	while(getline(file, line)){
		std::vector<OP> tokens = lexLine(line);
		for(OP token : tokens){
			program.push(token);
		}
	}
	execute(program);
}

