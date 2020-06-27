#include "quiz.h"

//Exits game when ESC key pressed
void getinput(){
    //quit game
    if (key[KEY_ESC]){
        gameover = 1;
    }
}

//Initializes the main screen to its original state
void initializeScreen(){
    //Set up answer box vectors
	rx1 = 50;
	rx2 = SCREEN_W-1;
	ry1 = (SCREEN_H/2)+SCREEN_H/8;
	ry2 = SCREEN_H/2;
	bx1 = 50;
	bx2 = SCREEN_W-1;
	by1 = (SCREEN_H/2)+SCREEN_H/8*2;
	by2 = (SCREEN_H/2)+SCREEN_H/8+4;
	yx1 = 50;
	yx2 = SCREEN_W-1;
	yy1 = (SCREEN_H/2)+SCREEN_H/8*3;
	yy2 = (SCREEN_H/2)+SCREEN_H/8*2+4;
	gx1 = 50;
	gx2 = SCREEN_W-1;
	gy1 = (SCREEN_H/2)+SCREEN_H/8*4-2;
	gy2 = (SCREEN_H/2)+SCREEN_H/8*3+4;
	//draw borders for questions  	     
    rect(screen, rx1, ry1, rx2, ry2, RED);//A    
    rect(screen, bx1, by1, bx2, by2, BLUE);//B    
    rect(screen, yx1, yy1, yx2, yy2, YELLOW);//C   
    rect(screen, gx1, gy1, gx2, gy2, GREEN);//D
    //Make top section have a white background
    rectfill(screen, 0, 0, SCREEN_W, 300, WHITE);
    //Add text for Start Button
    textprintf_ex(screen, font, SCREEN_W/2-50, 350, RED, 0, "START QUIZ");
    rect(screen, SCREEN_W/2-75, 345, SCREEN_W/2+50, 365, GREEN);
	//Add text for randomize Button
    textprintf_ex(screen, font, SCREEN_W - 250, 51, BLUE, 0, "RANDOMIZE SELECTION");
    rect(screen, SCREEN_W - 252, 49, SCREEN_W - 99, 60, RED);
    //Add text for select all Button
    textprintf_ex(screen, font, SCREEN_W - 250, 75, BLUE, 0, "SELECT ALL CHAPTERS");
    rect(screen, SCREEN_W - 252, 74, SCREEN_W - 99, 83, RED);
	//set up bitmaps
	const char *filename = "images/title.pcx"; 
	BITMAP *image;
	image = load_bitmap(filename, NULL); 
	if (!image) {
		allegro_message("Error loading %s", filename); 
	}
	//display the image 
	blit(image, screen, 0, 0, SCREEN_W/2-SCREEN_W/4, 0, SCREEN_W, SCREEN_H);	
	//display the chapter images
	for(int i = 0; i < 22; i++){
		std::string buf("images/");
		buf.append(chapNums[i].c_str());
		buf.append(".pcx");	
		char *filename = strdup(buf.c_str());
		BITMAP *image;
		image = load_bitmap(filename, NULL); 
		if (!image) {
			allegro_message("Error loading %s", filename); 
		}
		//display the image 
		if(i<11){
			blit(image, screen, 0, 0, 0+(i*100), 100, SCREEN_W, SCREEN_H);
		}else{
			blit(image, screen, 0, 0, 0+((i-11)*100), 200, SCREEN_W, SCREEN_H);
		}
		//destroy bitmap
		destroy_bitmap(image); 
	}	
	//destroy bitmap
	destroy_bitmap(image); 
}

//Loads the chapter files into the games memory and tells when game it is loaded to press any key to continue (or click)
void loadChapters(){
	std::string line, question, a, b, c ,d, answer, chap, subs, progress;	
	int i;
	
	//Load all the chapter csvs into the chapters array
	for(int k = 1; k < 23; k++){
		std::ostringstream s;
		s << k;
		i=0;
		chap = ("csvs/chapter"+s.str()+".csv"); //make the file name for the current chapter being imported
		std::ifstream myfile (chap.c_str());
		//open the current file for scanning
		if (myfile.is_open()){
			while (getline (myfile, line)){
				//create string stream for the line being read
				std::stringstream s_stream(line);
				//Read in and save the question, answers, and correct answer by comma delimiter
				getline(s_stream, subs, ',');
				question = subs;
				getline(s_stream, subs, ',');
				a = subs;
				getline(s_stream, subs, ',');
				b = subs;
				getline(s_stream, subs, ',');
				c = subs;
				getline(s_stream, subs, ',');
				d = subs;
				getline(s_stream, subs, ',');
				answer = subs;
				chapters[k-1].setQuestion(question, a, b, c, d, answer);//Save the question details to the chapter
				progress = "Loading assets: "+s.str()+" / 22";
				textprintf_ex(screen, font, SCREEN_W/2-100, 600, RED, 0, progress.c_str());//display progress loading
				i++;
			}
			myfile.close();
		}else{
			allegro_message("Failed to open chapter: %s", chap.c_str());
		}
	}
	progress = "ALL ASSETS LOADED. PRESS ANYKEY TO CONTINUE.";
	textprintf_ex(screen, font, SCREEN_W/2-150, 600, RED, 0, progress.c_str());//display progress complete
}

//Checks all mouse click actions to perform correct action based on its input detected from the user
void mouseClick(){
	mx = mouse_x;
	my = mouse_y;
	//treat actions for game selection 
	if(gameon == 0){
		//Check if selected randomize Button
		if(mx < (SCREEN_W-99) && mx > (SCREEN_W-252) && my > 49 && my < 60){
			if(randomize == 0){
				textprintf_ex(screen, font, SCREEN_W - 250, 51, YELLOW, 0, "RANDOMIZE SELECTION");
	    		rect(screen, SCREEN_W - 252, 49, SCREEN_W - 99, 60, GREEN);
	    		randomize = 1;
			}else{
				textprintf_ex(screen, font, SCREEN_W - 250, 51, BLUE, 0, "RANDOMIZE SELECTION");
	    		rect(screen, SCREEN_W - 252, 49, SCREEN_W - 99, 60, RED);
	    		randomize = 0;
			}			
		}
		//check if selected the select all Button
	    if(mx < (SCREEN_W-99) && mx > (SCREEN_W-252) && my > 74 && my < 83){
	    	if(selectAll == 0){
	    		textprintf_ex(screen, font, SCREEN_W - 250, 75, YELLOW, 0, "SELECT ALL CHAPTERS");
	    		rect(screen, SCREEN_W - 252, 74, SCREEN_W - 99, 83, GREEN);
	    		selectAll = 1;
			}else{
				textprintf_ex(screen, font, SCREEN_W - 250, 75, BLUE, 0, "SELECT ALL CHAPTERS");
	    		rect(screen, SCREEN_W - 252, 74, SCREEN_W - 99, 83, RED);
	    		selectAll = 0;
			}			
		}			    
		//do quick check to see if this click is for chapter selection between 1 and 11
		if(my < 200 && my > 100){
			//Now figure out which one was clicked		
			int i = 0; 
			int found = 0;
			while(found==0 && i < 11){
				if(mx < 100 + (100*i)){
					//found chapter picked
					found = 1;
					//check if on or off
					if(chapters[i].on==true){
						rect(screen, i*100, 100, 100 +(i*100), 200, WHITE);//was on so turn off
						chapters[i].on=false;
					}else{
						rect(screen, i*100, 100, 100 +(i*100), 200, RED);//was off so turn on
						chapters[i].on=true;
					}
				}
				i++;
			}
		}
		//do quick check to see if this click is for chapter selection between 12 and 22
		if(my < 300 && my > 200){
			//Now figure out which one was clicked		
			int i = 0; 
			int found = 0;
			while(found==0 && i < 11){
				if(mx < 100 + (100*i)){
					//found chapter picked
					found = 1;
					//check if on or off
					if(chapters[i+11].on==true){
						rect(screen, i*100, 200, 100 +(i*100), 300, WHITE);//was on so turn off
						chapters[i+11].on=false;
					}else{
						rect(screen, i*100, 200, 100 +(i*100), 300, RED);//was off so turn on
						chapters[i+11].on=true;
					}
				}
				i++;
			}
		}
		//Check if start button clicked
		if(my < 365 && my > 345 && mx < SCREEN_W/2+50 && mx > SCREEN_W/2-75){
    		//do stuff to begin game	
    		startQuiz();    		
		}		
	}else{//treat actions for mid quiz
		//Check if quit button clicked
		if(my < 365 && my > 345 && mx < SCREEN_W/2+50 && mx > SCREEN_W/2-75){
    		//end game reset all global variables
			endGame();
		}
		//Check if answer buttons are selected and which one it is
		if(my > ry2 && my < ry1 && mx > 100){//A
			checkAnswer(" A");
		}else if(my > by2 && my < by1 && mx > 100){//B
			checkAnswer(" B");
		}else if(my > yy2 && my < yy1 && mx > 100){//C
			checkAnswer(" C");
		}else if(my > gy2 && my < gy1 && mx > 100){//D
			checkAnswer(" D");
		}
		//Check for end of quiz
		if(question.empty() && nextQ == 1){
			//Handle end of quiz
			std::ostringstream s, t;
			s << correctTotal;
			t << questionTotal;
			std::string msg = "QUIZ DONE! You Scored: "+s.str()+" out of "+t.str();
			endGame();
			textprintf_ex(screen, font, SCREEN_W/2-150, 400, RED, 0, msg.c_str());//Print score after end so it isn't blacked out by clean up			
		}		
	}
	mouse_b = -1;
	rest(750);//wait a bit so it doesn't log multiple clicks, will still cycle on/off if held though
}

//Used to compare selected answer with the correct answer and to then update the quiz accordingly to progress further
void checkAnswer(std::string selected){
	//There's a space because that's just how they are in my csv files
	if(currentAnswer.compare(selected) == 0){//Correct
		correctTotal++; //Increment running correct score
		play_sample(sounds[0], volume, pan, pitch, FALSE); //Play correct answer sound effect
	}else{//incorrect sound
		play_sample(sounds[1], volume, pan, pitch, FALSE);
	}
	questionTotal++;
	displayUpdate();
	nextQ=1;
}

//Performs all of the necessary functions to end the current quiz so a new one can be chosen
void endGame(){
	//end game reset all global variables
	nextQ = 0;
	gameon = 0;
	correctTotal = 0;
	questionTotal = 0;
	randomize = 0;
	selectAll = 0;
	//deselect previously selected chapters		
	for(int i =0; i < 22; i++){
		if(chapters[i].on == true){
			chapters[i].on = false;
		}
	}
	//Clean screen off
	rectfill(screen, 0, 0, SCREEN_W, SCREEN_H, BLACK);
	initializeScreen();
}

//Initializes the quiz to begin based off of the users selections
void startQuiz(){	
	//Clear contents of vectors of any previous quiz data
	question.clear();
	a.clear();
	b.clear();
	c.clear();
	d.clear();
	answer.clear();
	//Check if select all function is enabled
	if(selectAll == 1){
		//select all function enabled, add all chapters to quiz
		for(int i = 0; i < 22; i++){
			for(int j = 0; j < 10; j++){
				question.push_back(chapters[i].question[j][0]);
				a.push_back(chapters[i].question[j][1]);
				b.push_back(chapters[i].question[j][2]);
				c.push_back(chapters[i].question[j][3]);
				d.push_back(chapters[i].question[j][4]);
				answer.push_back(chapters[i].question[j][5]);
			}
		}
	}else{
		//count number of selected chapters
		for(int i = 0; i < 22; i++){
			if(chapters[i].on == true){
				for(int j = 0; j < 10; j++){
					question.push_back(chapters[i].question[j][0]);
					a.push_back(chapters[i].question[j][1]);
					b.push_back(chapters[i].question[j][2]);
					c.push_back(chapters[i].question[j][3]);
					d.push_back(chapters[i].question[j][4]);
					answer.push_back(chapters[i].question[j][5]);
				}
			}
		}
	}
	//init seed
	srand (time(NULL));
	//display first question as long as the game can start
	if(!question.empty()){
		nextQ = 1;
		textprintf_ex(screen, font, SCREEN_W/2-50, 350, GREEN, 0, "QUIT  QUIZ");
		rect(screen, SCREEN_W/2-75, 345, SCREEN_W/2+50, 365, RED);
		gameon = 1;
		//Initialize score
		correctTotal = 0;
		questionTotal = 0;
		displayUpdate();
	}
}

//Updates the score and clears the contents of any previous questions
void displayUpdate(){
	std::ostringstream s, t;
	s << correctTotal;
	t << questionTotal;
	std::string display  = ("SCORE: "+s.str()+" OF "+t.str()); //Create string for score
	//print score to screen with box outline
	textprintf_ex(screen, font, SCREEN_W/2+275, 320, GREEN, 0, display.c_str());
	rect(screen, SCREEN_W/2+250, 315, SCREEN_W/2+400, 335, RED);
	//Clean off previous question
	rectfill(screen, 0, 370, SCREEN_W, SCREEN_H, BLACK);
	//redraw borders for questions  
	//A     
    rect(screen, rx1, ry1, rx2, ry2, RED);
    //B
    rect(screen, bx1, by1, bx2, by2, BLUE);
    //C
    rect(screen, yx1, yy1, yx2, yy2, YELLOW);
    //D
    rect(screen, gx1, gy1, gx2, gy2, GREEN);
}

//Begins the application start up with a splash screen and waits for user input once loaded
void startGame(){
	int i = 1;
	//set video mode    
    int ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
    if (ret != 0) {
        allegro_message(allegro_error);
        return;
    }
	//display splash image
	const char *filename = "images/splash.pcx"; 
	BITMAP *image;
	image = load_bitmap(filename, NULL); 
	if (!image) {
		allegro_message("Error loading %s", filename); 
	}
	//display the image 
	blit(image, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	//Display instructions on start up
	rectfill(screen, 295, 545, SCREEN_W-245, 710, BLACK);
	textprintf_ex(screen, font, 300, 650, GREEN, 0, "Pressing the ESC key exits the game.");
	textprintf_ex(screen, font, 300, 660, GREEN, 0, "Click the numbers to select chapters for quiz.");
	textprintf_ex(screen, font, 300, 670, GREEN, 0, "Alternatively, add all chapters by clicking 'Select All Chpaters'.");
	textprintf_ex(screen, font, 300, 680, GREEN, 0, "Click 'Randomize' to order the quiz questions randomly.");
	textprintf_ex(screen, font, 300, 690, GREEN, 0, "Click 'Start' when ready to begin.");
	textprintf_ex(screen, font, 300, 700, GREEN, 0, "Click in the box of the answer you would like to choose to select it.");
	//load chapters and display progress from within function
	loadChapters();
	//after chapters loaded wait for user input to move onto next screen
	while(i){        
        //check for escape to quit
        if (keypressed()){
        	i=0;
		}
		//check for mouse click and hitboxes
		mb = (mouse_b & 1);
		if(mb){
			i=0;
		}
    }
    //clear screen
    rectfill(screen, 0, 0, SCREEN_W, SCREEN_H, BLACK);
	destroy_bitmap(image); 
}

//The main application, does startup routines then uses a while loop to read inputs and perform actions until 
//the ESC key is pressed and it quits. After quitting the game it destroys its working memory.
int main(void){
	//initialize everything
    allegro_init(); 
    set_color_depth(16);
    install_keyboard(); 
    install_mouse();
    install_timer();
    srand(time(NULL));   	
	startGame();//LOADS THE GAME and waits for user input while showing splash screen
	initializeScreen();
	show_mouse(screen);
    //install sound
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0){
        allegro_message("Error initializing sound system");
        return 1;
    }
    //load sounds
    sounds[0] = load_sample("sounds/right.wav");
    sounds[1] = load_sample("sounds/wrong.wav");
    sounds[2] = load_sample("sounds/music.wav");
    //play background music
    play_sample(sounds[2], volume, pan, pitch, TRUE);
    //game loop after splash screen
    while(!gameover){        
        //check for escape to quit
        if (keypressed()){
        	getinput();
		}            		
		//check for mouse click and hitboxes
		mb = (mouse_b & 1);
		if(mb){
			mouseClick();
		}
		//Process the next quiz question if the game is on and the game needs to move on to the next question		
		if(gameon == 1 && nextQ == 1){
			int nextNum;
			//if randomize selected get random number within range of vector size
			if(randomize == 1){
				nextNum = rand() % question.size();
			}else{//otherwise just go with the item at the front of the vectors
				nextNum = 0;
			}			
			//display question and save answer
			//Check if question too long to display in one line (all answers are so dont worry about them)
			if(question[nextNum].length() > 120){
				textprintf_ex(screen, font, 30, 400, GREEN, 0, question[nextNum].substr(0, 119).c_str());
				textprintf_ex(screen, font, 35, 410, GREEN, 0, question[nextNum].substr(119, question[nextNum].length()).c_str());
			}else{
				textprintf_ex(screen, font, 30, 400, GREEN, 0, question[nextNum].c_str());
			}			
			textprintf_ex(screen, font, 30, 500, GREEN, 0, a[nextNum].c_str());			
			textprintf_ex(screen, font, 30, 620, GREEN, 0, b[nextNum].c_str());
			textprintf_ex(screen, font, 30, 730, GREEN, 0, c[nextNum].c_str());
			textprintf_ex(screen, font, 30, 840, GREEN, 0, d[nextNum].c_str());
			currentAnswer = answer[nextNum].c_str();
			//remove that question entirely from lists so it isn't repeated
			question.erase(question.begin() + nextNum);
			a.erase(a.begin() + nextNum);
			b.erase(b.begin() + nextNum);
			c.erase(c.begin() + nextNum);
			d.erase(d.begin() + nextNum);
			answer.erase(answer.begin() + nextNum);
			//Turn off so it doesn't just run through the whole list without waiting for answers
			nextQ = 0;			
		}
    }
    //end program
    for (int n=0; n<3; n++){
    	destroy_sample(sounds[n]);
	}
    remove_sound();
    allegro_exit();
    return 0;
}

END_OF_MAIN()
