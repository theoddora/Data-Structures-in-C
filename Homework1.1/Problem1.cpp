#include <iostream>
#include <stack>

bool isCorrect(char*);

int main()
{
	char input[200];
	std::cout << "enter an expression: ";
	std::cin.getline(input, sizeof(input));
	std::cout << std::endl << "you entered \"" << input << "\"" << std::endl;

	std::cout << "is it correct?: " << std::boolalpha << isCorrect(input) << std::endl;
	return 0;
}

bool isCorrect(char* input)
{
	std::stack<char> parenthesis;
	while (*input)
	{
		char currentCharacter = *input++;
		if (currentCharacter == '(' || currentCharacter == '[' || currentCharacter == '{')
		{
			parenthesis.push(currentCharacter);
			continue;
		}
		if (currentCharacter == '=' && !parenthesis.empty())
		{
			return false;
		}
		if ((currentCharacter == ')' || currentCharacter == ']' || currentCharacter == '}') && parenthesis.empty())
		{
			return false;
		}
		switch (currentCharacter)
		{
		case ')':
			if (parenthesis.top() != '(')
			{
				return false;
			}
			parenthesis.pop();
			break;
		case ']':
			if (parenthesis.top() != '[')
			{
				return false;
			}
			parenthesis.pop();
			break;
		case '}':
			if (parenthesis.top() != '{')
			{
				return false;
			}
			parenthesis.pop();
			break;
		}
	}
	return parenthesis.empty();
}