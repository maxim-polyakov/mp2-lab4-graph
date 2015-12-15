#include "Calculate.h"


using namespace std;



string note(string exp){

	Stack<char> opStack;
	Stack<char> trackStack;

map <char, int> op;
op['*'] = 3;
op['/'] = 3;
op['+'] = 2;
op['-'] = 2;
op['('] = 1;
op['='] = 0;

char buff;

for (int i = 0; i < exp.length(); i++){
	buff = exp[i];
	if (op.count(buff)) {			
		if ((!opStack.IsEmpty()) && (op[buff] <= op[opStack.Peek()]) && (buff != '('))
			while ((!opStack.IsEmpty()) && (op[buff] <= op[opStack.Peek()]))
				trackStack.Push(opStack.Put());
		

		opStack.Push(buff);
		continue;
	}

	if (((buff >= 0x41) && (buff <= 0x5A))							
		|| ((buff >= 0x61) && (buff <= 0x7A)))	{						
		trackStack.Push(buff);
		continue;
	}

	if (buff == ')') {																					
		while ((!opStack.IsEmpty()) && (opStack.Peek() != '('))
			trackStack.Push(opStack.Put());
		if (opStack.IsEmpty())										
			throw "не правильно расставлены скобки";
		opStack.Put();
		continue;
	}
	throw "недопустимый символ";
}
while (!opStack.IsEmpty()){
	if (opStack.Peek() == '(')
		throw "не правильно расставлены скобки";
	trackStack.Push(opStack.Put());
}

if (trackStack.IsEmpty())
throw "нет данных";

string result;
string tmp;

while (!trackStack.IsEmpty()) {
	tmp = trackStack.Put();
	result.insert(0, tmp);
}
return result;
}

double Calculate(string exp)
{
	if (exp == "")
		throw "нет данных";
	Stack<float> trackStack;
	char buff;
	double leftOperand;
	double rightOperand;

	map<char, double> val;

	for (int i = 0; i < exp.length(); i++){
		buff = exp[i];
		if (((buff >= 0x42) && (buff <= 0x6A))
			|| ((buff >= 0x62) && (buff <= 0x6A))){
			if (!val.count(buff)){
				cout << '\t' << buff << " = ";
				cin >> val[buff];
			}
			trackStack.Push(val[buff]);
			continue;
		}

		if (trackStack.IsEmpty())
			throw "нет совпадения с числом операндов";
		rightOperand = trackStack.Put();
		if (trackStack.IsEmpty())
			throw "нет совпадения с числом операндов";
		leftOperand = trackStack.Put();

		switch (buff){
		case '+':{trackStack.Push(leftOperand + rightOperand); break; }
		case '-':{trackStack.Push(leftOperand - rightOperand); break; }
		case '*':{trackStack.Push(leftOperand * rightOperand); break; }
		case '/':{trackStack.Push(leftOperand / rightOperand); break; }
		}
	}

	float result = trackStack.Put();
	if (!trackStack.IsEmpty())
		throw "Стэк переполнен";
	return result;
}