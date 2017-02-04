#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
	int unmatchedPosition = 0;
	bool isCloseBracket = false;
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        if (next == '(' || next == '[' || next == '{') {
			opening_brackets_stack.push(Bracket(next, position));
        }
        if (next == ')' || next == ']' || next == '}') {
			if(opening_brackets_stack.empty()){
				unmatchedPosition = position+1;
				break;
			}
			else
			{
				if(opening_brackets_stack.top().Matchc(next)){
					opening_brackets_stack.pop();
				}
				else
				{
					isCloseBracket = true;
					unmatchedPosition = position+1;
					break;
				}
			}
        }
    }
	if(!opening_brackets_stack.empty()){
		if(isCloseBracket)
			std::cout<<unmatchedPosition<<std::endl;
		else
			std::cout<<opening_brackets_stack.top().position+1<<std::endl;
	}
	else{
		if(unmatchedPosition == 0)
			std::cout<<"Success"<<std::endl;
		else
			std::cout<<unmatchedPosition<<std::endl;
	}
		
    return 0;
}
