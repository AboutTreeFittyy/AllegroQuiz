#ifndef _CHAPTER_CPP
#define _CHAPTER_CPP
#include <iostream>

class Chapter{
	
	public: 
		void setQuestion(std::string ques, std::string a, std::string b, std::string c, std::string d, std::string answ);
		Chapter();
		std::string question[10][6]; //Each chapter has 10 questions, store them here
		int total;
		bool on;	
};
#endif
