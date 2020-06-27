#include "Chapter.h"

Chapter::Chapter(){
	total = 0;
	on = false;
}

void Chapter::setQuestion(std::string ques, std::string a, std::string b, std::string c, std::string d, std::string answ){
	question[total][0] = ques;
	question[total][1] = a;
	question[total][2] = b;
	question[total][3] = c;
	question[total][4] = d;
	question[total][5] = answ;
	total++;
}
