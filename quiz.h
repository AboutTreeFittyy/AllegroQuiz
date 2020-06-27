#ifndef _QUIZ_H
#define _QUIZ_H
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Chapter.h"

#include "allegro.h"



//defines
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 1100
#define HEIGHT 900
#define RED makecol(255,0,0)
#define BLUE makecol(0,153,255)
#define YELLOW makecol(255,255,0)
#define GREEN makecol(0,153,51)
#define WHITE makecol(255,255,255)
#define BLACK makecol(0,0,0)

//Global variables
Chapter chapters[22];
SAMPLE *sounds[3];
int volume = 128;
int pan = 128;
int pitch = 1000;
int gameover = 0;
int gameon = 0;
int nextQ = 0;
int randomize = 0;
int selectAll = 0;
int mx,my,mb;
int rx1, rx2, ry1, ry2;
int bx1, bx2, by1, by2;
int yx1, yx2, yy1, yy2;
int gx1, gx2, gy1, gy2;
int correctTotal, questionTotal;
std::string currentAnswer;
std::vector<std::string> question;
std::vector<std::string> a;
std::vector<std::string> b;
std::vector<std::string> c;
std::vector<std::string> d;
std::vector<std::string> answer;

//Strings of the names of the chapters image files
std::string chapNums[22] = {	"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22"};

//functions
void getinput();
void initializeScreen();
void checkAnswer(std::string selected);
void loadChapters();
void mouseClick();
void startQuiz();
void startGame();
void endGame();
void displayUpdate();

#endif


