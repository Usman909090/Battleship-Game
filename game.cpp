//============================================================================
// Name        : .cpp
// Author      : Usman Randhawa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Battleship.
//============================================================================

#ifndef Battleship_CPP_
#define Battleship_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include<fstream>//for using in leader board work
#include<ctime>   //for using rand() function in auto placing ships mode

using namespace std;

//Global variables for storing co-ordinates
int cord_x = 0, cord_y = 0; 
int pressed_x = 0, pressed_y = 0;
char userinput[] = { "" };
int bombers = 0, submarines = 0, mines = 0; // For option purpose
int ship_clicked = 0;        // FOr cheaking which ship is clicked
bool drop;
int box_x = 0, box_y = 0, mouse_x = 0, mouse_y = 0, mouse_x2 = 0, mouse_y2 = 0;
int cheak = 0, cheak1 = 0, cheak3 = 0;// For cheaking in auto placing of computer and user grid
int hitter = -1;
int hitter2 = -1;
int game_turn_setter = 0;
int player_score = 0;         //   For score purpose





// The folowing array play an important role in placing ships like if the ship is placed at wrong side it will help to print ship in its previous location 
int prev_ship_location[10][4] = { {672,444,132,38}, {705,362,99,38}, {573,362,99,38} , {738,280,66,38} , {639,280,66,38} , {540,280,66,38} , {771,198,33,38} , {705,198,33,38} , {639,198,33,38} , {573,198,33,38} };
// the folowing array is for storing copmuter grid's ships values, these values are just given for filling the place furturemore these will be randomize
int prev_ship_location_comp[10][4] = { {0,9,132,38}, {1,8,99,38}, {2,7,99,38} , {3,6,66,38} , {4,5,66,38} , {5,4,66,38} , {6,3,33,38} , {7,2,33,38} , {8,1,33,38} , {9,0,33,38} };

// For restoring the screen of new_game
int copyof_prev_ship_location[10][4] = { {672,444,132,38}, {705,362,99,38}, {573,362,99,38} , {738,280,66,38} , {639,280,66,38} , {540,280,66,38} , {771,198,33,38} , {705,198,33,38} , {639,198,33,38} , {573,198,33,38} };



//Stored the starting location of the boxes from bottom right corner
int first_grid[11][11] = { {11175,14475,17775,21075,24375,27675,30975,34275,37575,40875,44175},{111116,144116,177116,210116,243116,276116,309116,342116,375116,408116,441116},{111157,144157,177157,210157,243157,276157,309157,342157,375157,408157,441157},{111198,144198,177198,210198,243198,276198,309198,342198,375198,408198,441198},{111239,144239,177239,210239,243239,276239,309239,342239,375239,408239,441239}, {111280,144280,177280,210280,243280,276280,309280,342280,375280,408280,441280}, {111321,144321,177321,210321,243321,276321,309321,342321,375321,408321,441321}, {111362,144362,177362,210362,243362,276362,309362,342362,375362,408362,441362}, {111403,144403,177403,210403,243403,276403,309403,342403,375403,408403,441403}, {111444,144444,177444,210444,243444,276444,309444,342444,375444,408444,441444}, {111485,144485,177485,210485,243485,276485,309485,342485,375485,408485,441485} };
int second_grid[11][12] = { {47475,50775,54075,57375,60675,63975,67275,70575,73875,77175,80475,83775}, {474116,507116,540116,573116,606116,639116,672116,705116,738116,771116,804116,837116} ,{474157,507157,540157,573157,606157,639157,672157,705157,738157,771157,804157,837157} ,{474198,507198,540198,573198,606198,639198,672198,705198,738198,771198,804198,837198} ,{474239,507239,540239,573239,606239,639239,672239,705239,738239,771239,804239,837239} ,{474280,507280,540280,573280,606280,639280,672280,705280,738280,771280,804280,837280} ,{474321,507321,540321,573321,606321,639321,672321,705321,738321,771321,804321,837321} ,{474362,507362,540362,573362,606362,639362,672362,705362,738362,771362,804362,837362} ,{474403,507403,540403,573403,606403,639403,672403,705403,738403,771403,804403,837403} ,{474444,507444,540444,573444,606444,639444,672444,705444,738444,771444,804444,837444} ,{474485,507485,540485,573485,606485,639485,672485,705485,738485,771485,804485,837485} };

//For cheaking mouse co-ordinates locations
int mouse_grid[12][12] = { {140650,181650,222650,263650,304650,345650,386650,427650,468650,509650,550650,591650},{140618,181618,222618,263618,304618,345618,386618,427618,468618,509618,550618,591618},{140586,181586,222586,263586,304586,345586,386586,427586,468586,509586,550586,591586}, {140552,181552,222552,263552,304552,345552,386552,427552,468552,509552,550552,591552},{140514,181514,222514,263514,304514,345514,386514,427514,468514,509514,550514,591514},{140482,181482,222482,263482,304482,345482,386482,427482,468482,509482,550482,591482},{140448,181448,222448,263448,304448,345448,386448,427448,468448,509448,550448,591448},{140414,181414,222414,263414,304414,345414,386414,427414,468414,509414,550414,591414},{140378,181378,222378,263378,304378,345378,386378,427378,468378,509378,550378,591378},{140342,181342,222342,263342,304342,345342,386342,427342,468342,509342,550342,591342},{140306,181306,222306,263306,304306,345306,386306,427306,468306,509306,550306,591306},{140272,181272,222272,263272,304272,345272,386272,427272,468272,509272,550272,591272 } };
int mouse_grid2[12][13] = { {587650,637650,678650,719650,760650,801650,842650,883650,924650,965650,1006650,1047650,1088650},{587618,637618,678618,719618,760618,801618,842618,883618,924618,965618,1006618,1047618,1088618},{587586,637586,678586,719586,760586,801586,842586,883586,924586,965586,1006586,1047586,1088586},{587552,637552,678552,719552,760552,801552,842552,883552,924552,965552,1006552,1047552,1088552},{587514,637514,678514,719514,760514,801514,842514,883514,924514,965514,1006514,1047514,1088514},{587482,637482,678482,719482,760482,801482,842482,883482,924482,965482,1006482,1047482,1088482},{587448,637448,678448,719448,760448,801448,842448,883448,924448,965448,1006448,1047448,1088448},{587414,637414,678414,719414,760414,801414,842414,883414,924414,965414,1006414,1047414,1088414},{587378,637378,678378,719378,760378,801378,842378,883378,924378,965378,1006378,1047378,1088378},{587342,637342,678342,719342,760342,801342,842342,883342,924342,965342,1006342,1047342,1088342},{587306,637306,678306,719306,760306,801306,842306,883306,924306,965306,1006306,1047306,1088306},{587272,637272,678272,719272,760272,801272,842272,883272,924272,965272,1006272,1047272,1088272} };


int hitted_ships[2];             // For storing value of x an  y cordinate for drawing string
int hitted_ships_permanent[5003][3];       // For permanentaly storing hitted ship value in array
int hitted_ships2_permanent[5003][3];       // For permanentaly storing hitted ship value in array


//declaring functionsa

void menu();
void newgame();
void auto_place_ships_user();    // for automatically placing ships in our grid
void auto_place_ships_comp();     // for automatically placing ships in computer grid
void move_ship(int, int, int);// For moving battle ships for placing  and this parameter for telling which ship_is it and which are the initial cordinates
int over_lapping_cheaker(int, int, int, char, char);  // For cheaking either the ships that ara being placed are not overlapping anf the return command will be used in Auto placing functions
void battle_round();
void start_battle();
void inputnameandcolor();
void leaderboard();
void balance();
void option();



void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}









void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}

	
		
	glutPostRedisplay();
}






void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;

		pressed_x = x, pressed_y = y;      //  For moving ships
	
		
	
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}


void MouseClicked(int button, int state, int x, int y) {
	
	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		glutMotionFunc(MousePressedAndMoved); // Mouse
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
	
		cord_x = x;              // If mouse will be pressed it will assign its co-ordinates to the specifies variables
		cord_y = y;
		
		
		
	}
		else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;
			

	}
	


	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Battleship Game"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	glutFullScreen();






	
	
	// Now lets move to menu
	glutDisplayFunc(menu);

	







	


	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	
	
	
	glutMouseFunc(MouseClicked);
	
	
	glutPassiveMotionFunc(MouseMoved); // Mouse

	glutMainLoop();
	return 1;
}




void menu()
{
	
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	//Drawing interface
	DrawRoundRect(335, 690, 290, 35, colors[YELLOW]);
	DrawString(335, 700, "Welcome to the Battle Fields", colors[WHITE]);
	DrawString(0, 600, "_______________________________________________________________________________________________________________________", colors[WHITE]);
	DrawRoundRect(450, 540, 65, 35, colors[BROWN]);
	DrawString(450, 550, "Menu", colors[WHITE]);
	DrawString(0, 545, "_______________________________________________________________________________________________________________________", colors[WHITE]);
	DrawRoundRect(350, 490, 250, 35, colors[BLUE]);
	DrawString(407, 500, "Start New Game", colors[WHITE]);
	DrawRoundRect(350, 440, 250, 35, colors[GREEN]);
	DrawString(380, 450, "View The Leader Board", colors[WHITE]);
	DrawRoundRect(350, 390, 250, 35, colors[RED]);
	DrawString(420, 400, "View Balance", colors[WHITE]);
	DrawRoundRect(350, 340, 250, 35, colors[LIME_GREEN]);
	DrawString(440, 350, "Options", colors[WHITE]);
	DrawRoundRect(350, 290, 250, 35, colors[SADDLE_BROWN]);
	DrawString(455, 300, "Exit", colors[WHITE]);
	DrawString(0, 250, "_______________________________________________________________________________________________________________________", colors[WHITE]);

	


	// Making the buttons for different options in menu

	
	if ((cord_x >= 445 && cord_x <= 750) && (cord_y >= 273 && cord_y <= 295))//For New Game buttun
	{
		for (int i = 0; i < 10; i++)          // For assigning ships location to an array
		{
			for (int j = 0; j < 4; j++)
				prev_ship_location[i][j] = copyof_prev_ship_location[i][j];
		}
		glutDisplayFunc(newgame);
	}
	else if ((cord_x >= 445 && cord_x <= 750) && (cord_y >= 313 && cord_y <= 335))//For Leader board buttun
	{
		
		
		glutDisplayFunc(leaderboard);

	}
	else if ((cord_x >= 445 && cord_x <= 750) && (cord_y >= 353 && cord_y <= 375))//For  Balance buttun
	{
		
		glutDisplayFunc(balance);
	}
	else if ((cord_x >= 445 && cord_x <= 750) && (cord_y >= 393 && cord_y <= 415))//For Options buttun
	{
		
		glutDisplayFunc(option);
	}
	else if ((cord_x >= 445 && cord_x <= 750) && (cord_y >= 433 && cord_y <= 465))//For exit buttun
	{
		exit(1);
	}
	



	
	glutSwapBuffers();
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void newgame()
{
	//glutDisplayFunc(inputnameandcolor);
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	
	
	
	DrawSquare(0, 0, 1500, colors[LIGHT_BLUE]);
	cheak = 0;

	DrawRoundRect(850, 800, 250, 35, colors[DARK_BLUE]);
	DrawString(850, 810, "Back to menu", colors[WHITE]);

	if ((cord_x >= 1069 && cord_x <= 1279) && (cord_y >= 3 && cord_y <= 31))// For back button
	{
		glutDisplayFunc(menu);
		cheak1 = 0;
	}



	






	
	//For printing grid of 12 by 24
	float x1 = 110, y1 = 73, y2 = 524, x2 = 475;
	float new_x = x1;
	for (int i = 1; i <= 12; i++, x1 += 33)           // For printing vertical lines
	{
		if (i == 12 || i == 1 || i == 2)
		{
			DrawLine(x1, y1, x1, y2, 4, colors[WHITE]);
		}
		else
		DrawLine(x1, y1, x1, y2, 1, colors[WHITE]);
	}

	for (int i = 1; i <= 12; i++, y1 += 41)            // For printing horizontal lines
	{
		if (i == 1 || i == 12 || i == 11)
		{
			DrawLine(new_x, y1, x2, y1, 4, colors[WHITE]);
		}
		else
		DrawLine(new_x, y1, x2, y1, 1, colors[WHITE]);
	}
	
	// Printing some initial values like co-ordinates like A1,B2 etc.

	DrawString(123, 452, "A", colors[WHITE]);
	DrawString(123, 411, "B", colors[WHITE]);
	DrawString(123, 370, "C", colors[WHITE]);
	DrawString(123, 329, "D", colors[WHITE]);
	DrawString(123, 288, "E", colors[WHITE]);
	DrawString(123, 247, "F", colors[WHITE]);
	DrawString(122, 207, "G", colors[WHITE]);
	DrawString(121,167 , "H", colors[WHITE]);
	DrawString(125,127 , "I", colors[WHITE]);
	DrawString(123,87 , "J", colors[WHITE]);
	
	DrawString(156, 493, "1", colors[WHITE]);
	DrawString(189, 493, "2", colors[WHITE]);
	DrawString(222, 493, "3", colors[WHITE]);
	DrawString(255, 493, "4", colors[WHITE]);
	DrawString(288, 493, "5", colors[WHITE]);
	DrawString(321, 493, "6", colors[WHITE]);
	DrawString(354, 493, "7", colors[WHITE]);
	DrawString(387, 493, "8", colors[WHITE]);
	DrawString(420, 493, "9", colors[WHITE]);
	DrawString(448, 493, "10", colors[WHITE]);











//__done printing initial grid_________________________________________________________________________________________________________________________________________________________________________________



	DrawRectangle(900, 30, 55, 40, colors[BROWN]);
	DrawString(900, 35, "Auto", colors[WHITE]);

	DrawRectangle(650, 30, 215, 40, colors[BROWN]);
	DrawString(650, 35, "Let's move to Battleground", colors[WHITE]);



	DrawRectangle(900, 145, 70, 40, colors[GREEN]);
	DrawString(900, 150, "Options", colors[WHITE]);
	
	if ((cord_x >= 1130 && cord_x <= 1215 && cord_y >= 560 && cord_y <= 593))
	{

		glutDisplayFunc(option);


	}





	DrawRoundRect(prev_ship_location[0][0], prev_ship_location[0][1], prev_ship_location[0][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[1][0], prev_ship_location[1][1], prev_ship_location[1][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[2][0], prev_ship_location[2][1], prev_ship_location[2][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[3][0], prev_ship_location[3][1], prev_ship_location[3][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[4][0], prev_ship_location[4][1], prev_ship_location[4][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[5][0], prev_ship_location[5][1], prev_ship_location[5][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[6][0], prev_ship_location[6][1], prev_ship_location[6][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[7][0], prev_ship_location[7][1], prev_ship_location[7][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[8][0], prev_ship_location[8][1], prev_ship_location[8][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[9][0], prev_ship_location[9][1], prev_ship_location[9][2], prev_ship_location[0][3], colors[BLACK], 30);










	
	
	if (cord_x >= 1130 && cord_x <= 1197 && cord_y >= 661 && cord_y <= 690 && cheak1 == 0)           // Button for automatic placing ships in the grid
	{
	
			auto_place_ships_user();
			
			cheak1 = 1;
	}



	//size 4 ship
	if ((cord_x >= 843 && cord_x <= 1005 && cord_y >= 306 && cord_y <= 337))
	{
			
		move_ship(0, 672, 444);


	}


	// FOr size 3 ships
	if ((cord_x >= 885 && cord_x <= 1005 && cord_y >= 377 && cord_y <= 407))
	{
		move_ship(1, 705, 362);
	}
	if ((cord_x >= 753 && cord_x <= 873 && cord_y >= 377 && cord_y <= 407))
	{
		move_ship(2, 573, 362);
	}


	//For size 2 ships
	if ((cord_x >= 927 && cord_x <= 1005 && cord_y >= 447 && cord_y <= 477))
	{
		move_ship(3, 738, 280);
	}
	if ((cord_x >= 802 && cord_x <= 881 && cord_y >= 447 && cord_y <= 477))
	{
		move_ship(4,639,280);
	}
	if ((cord_x >= 678 && cord_x <= 757 && cord_y >= 447 && cord_y <= 477))
	{
		move_ship(5,540,280);
	}


	// FOr size 1 ships
	if ((cord_x >= 969 && cord_x <= 1005 && cord_y >= 518 && cord_y <= 548))
	{
		move_ship(6,771,198);
	}
	if ((cord_x >= 885 && cord_x <= 922 && cord_y >= 518 && cord_y <= 548))
	{
		move_ship(7,705,198);
	}
	if ((cord_x >= 801 && cord_x <= 838 && cord_y >= 518 && cord_y <= 548))
	{
		move_ship(8,639,198);
	}
	if ((cord_x >= 717 && cord_x <= 754 && cord_y >= 518 && cord_y <= 548))
	{
		move_ship(9,573,198);
	}





	// For Move to battleground button

	if ((cord_x >= 815 && cord_x <= 1083 && cord_y >= 661 && cord_y <= 690))
	{
		glutDisplayFunc(battle_round);
	}
	

	glutSwapBuffers();
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void auto_place_ships_user()                   // This function will automatically place ships in the grid
{
	
	int ship_placed = 0;
	
	for (int ship_number = 0; ship_number < 10; ship_number++)
	{
		if (ship_placed == 10)
		{
			cord_x = 0;
			cord_y = 0;
			break;
		}
		


		srand(time(NULL));          // for most random value


		int x = 0;
		int y = 0;

		//DrawSquare(first_grid[5][0] / 1000, first_grid[5][0] % 1000, 30, colors[BLACK]);

	


		do       // For cheaking the rand is between grid limit
		{
			x = (rand() % 11);
			y = (rand() % 11);
		} while (x == 0 || y == 10);
		




		int placing_x = 0;
		int placing_y = 0;

		if (y == 0)
		{
			placing_x = first_grid[y][x] / 100;
			placing_y = first_grid[y][x] % 100;
		}
		else
		{
			placing_x = first_grid[y][x] / 1000;
			placing_y = first_grid[y][x] % 1000;
		}


		int prev_initial_position_x = prev_ship_location[ship_number][0];
		int prev_initial_position_y = prev_ship_location[ship_number][1];

		
		

		if ((placing_x + prev_ship_location[ship_number][2] - 33) > 441) 
		{
		    
			ship_number -= 1;
			continue;
		}
		else
		{
			prev_ship_location[ship_number][0] = placing_x;
			prev_ship_location[ship_number][1] = placing_y;
			
		}
		
		if (over_lapping_cheaker(ship_number, prev_initial_position_x, prev_initial_position_y, 'A', 'u') == 1)      // For cheaking overlapping of battleships
		{
			ship_number -= 1;
			continue;
		}
		else
			ship_placed++;
		
		if (ship_number == 9)
		{
			cord_x = 0;
			cord_y = 0;
		}
		
	
	}

	

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void auto_place_ships_comp()                   // This function will automatically place ships in the grid for computer
{

	int ship_placed = 0;

	for (int ship_number = 0; ship_number < 10; ship_number++)
	{
		if (ship_placed == 10)
		{
			cord_x = 0;
			cord_y = 0;
			break;
		}



		srand(time(NULL));          // for most random value


		int x = 0;
		int y = 0;

		//DrawSquare(first_grid[5][0] / 1000, first_grid[5][0] % 1000, 30, colors[BLACK]);




		do       // For cheaking the rand is between grid limit
		{
			x = (rand() % 11);
			y = (rand() % 11);
		} while (x == 0 || y == 10 || x==1 );





		int placing_x = 0;
		int placing_y = 0;

		if (y == 0)
		{
			placing_x = second_grid[y][x] / 100;
			placing_y = second_grid[y][x] % 100;
		}
		else
		{
			placing_x = second_grid[y][x] / 1000;
			placing_y = second_grid[y][x] % 1000;
		}


		int prev_initial_position_x = prev_ship_location_comp[ship_number][0];
		int prev_initial_position_y = prev_ship_location_comp[ship_number][1];




		if ((placing_x + prev_ship_location_comp[ship_number][2] - 33) > 837)
		{

			ship_number -= 1;
			continue;
		}
		else
		{
			prev_ship_location_comp[ship_number][0] = placing_x;
			prev_ship_location_comp[ship_number][1] = placing_y;

		}

		if (over_lapping_cheaker(ship_number, prev_initial_position_x, prev_initial_position_y, 'A', 'c') == 1)      // For cheaking overlapping of battleships
		{
			ship_number -= 1;
			continue;
		}
		else
			ship_placed++;

		if (ship_number == 9)
		{
			cord_x = 0;
			cord_y = 0;
		}


	}



}











//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void move_ship(int ship_number,int prev_initial_position_x,int prev_initial_position_y)     // This function is used to alot relative co-ordinates to ship w.r.t. mouse location
{
	if (pressed_x >= 181 && pressed_x <= 592 && pressed_y >= 307 && pressed_y <= 652)
	{

		int i, j;
		for (i = 0; i < 12; i++)
		{
			int loopcheaker = 0;
			for (j = 0; j < 12; j++)
			{
				if (((i == 10) && (j == 1 || j == 2 || j == 3 || j == 4 || j == 5 || j == 6 || j == 7 || j == 8 || j == 9 || j == 10)) || ((j == 0) && (i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10)))
				{
					continue;
				}
				mouse_x = mouse_grid[i][j] / 1000;
				mouse_y = mouse_grid[i][j] % 1000;
				mouse_x2 = mouse_grid[i + 1][j + 1] / 1000;
				mouse_y2 = mouse_grid[i + 1][j + 1] % 1000;
				if ((pressed_x >= mouse_x) && (pressed_x <= mouse_x2) && ((pressed_y <= mouse_y) && (pressed_y >= mouse_y2)))
				{
					loopcheaker = 1;
					break;
				}
			}
			if (loopcheaker == 1)
				break;
		}
		if (i == 0)
		{
			box_x = first_grid[i][j] / 100;
			box_y = first_grid[i][j] % 100;
		}
		else
		{
			box_x = first_grid[i][j] / 1000;
			box_y = first_grid[i][j] % 1000;
		}

		prev_ship_location[ship_number][0] = box_x;
		prev_ship_location[ship_number][1] = box_y;

		// For cheaking either ship is placed inside the grid and not overlapping
		if (ship_number == 0)
		{
			
			if ((box_x + 99) > 441 )              
			{
				prev_ship_location[ship_number][0] = prev_initial_position_x;
				prev_ship_location[ship_number][1] = prev_initial_position_y;
			}
			over_lapping_cheaker(ship_number, prev_initial_position_x, prev_initial_position_y, 'M', 'u');      // For cheaking overlapping of battleships

			
		}

		if (ship_number == 1 || ship_number == 2)
		{

			if ((box_x + 66) > 441)
			{
				prev_ship_location[ship_number][0] = prev_initial_position_x;
				prev_ship_location[ship_number][1] = prev_initial_position_y;
			}
			over_lapping_cheaker(ship_number, prev_initial_position_x, prev_initial_position_y, 'M', 'u');
		}

		if (ship_number == 3 || ship_number == 4 || ship_number == 5)
		{

			if ((box_x + 33) > 441)
			{
				prev_ship_location[ship_number][0] = prev_initial_position_x;
				prev_ship_location[ship_number][1] = prev_initial_position_y;
			}
			over_lapping_cheaker(ship_number, prev_initial_position_x, prev_initial_position_y, 'M', 'u');
		}

		if (ship_number == 6 || ship_number == 7 || ship_number == 8 || ship_number == 9)
		{

			if ((box_x ) > 441)
			{
				prev_ship_location[ship_number][0] = prev_initial_position_x;
				prev_ship_location[ship_number][1] = prev_initial_position_y;
			}
			over_lapping_cheaker(ship_number, prev_initial_position_x, prev_initial_position_y, 'M', 'u');
		}
		

	}
	else if (pressed_x >= 591 && pressed_x <= 1087 && pressed_y >= 273 && pressed_y <= 655)
	{
		int i, j;
		for (i = 0; i < 12; i++)
		{
			int loopcheaker = 0;
			for (j = 0; j < 13; j++)
			{

				mouse_x = mouse_grid2[i][j] / 1000;
				mouse_y = mouse_grid2[i][j] % 1000;
				mouse_x2 = mouse_grid2[i + 1][j + 1] / 1000;
				mouse_y2 = mouse_grid2[i + 1][j + 1] % 1000;
				if ((pressed_x >= mouse_x) && (pressed_x <= mouse_x2) && ((pressed_y <= mouse_y) && (pressed_y >= mouse_y2)))
				{
					loopcheaker = 1;
					break;
				}
			}
			if (loopcheaker == 1)
				break;
		}
		if (i == 0)
		{
			box_x = second_grid[i][j] / 100;
			box_y = second_grid[i][j] % 100;
		}
		else
		{
			box_x = second_grid[i][j] / 1000;
			box_y = second_grid[i][j] % 1000;
		}

		prev_ship_location[ship_number][0] = box_x;
		prev_ship_location[ship_number][1] = box_y;

	}
		
}
////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int over_lapping_cheaker(int ship_number, int prev_initial_position_x, int prev_initial_position_y,char auto_or_manual, char user_or_computer)               // It will cheak overpalling and will not allow to place in adjecant boxes
{
	int loop_breaker = 0;

	for (int i = 0; i < 10; i++)
	{
		if (i == ship_number)
			continue;
		int second_loop_compare_time;
		if (i == 0)        // for 4 size ship
			second_loop_compare_time = 4;
		else if (i == 1 || i == 2)       // for 3 size ship
			second_loop_compare_time = 3;
		else if (i == 3 || i == 4 || i == 5)     // for 2 size ship
			second_loop_compare_time = 2;
		else            // for 1 size ship
			second_loop_compare_time = 1;

		int over_lapping_cheak_x = 0;
		int over_lapping_cheak_y = 0;

		if (user_or_computer == 'u')
		{
			over_lapping_cheak_x = prev_ship_location[i][0];              //cheaking other ships cordnates that they match with it or not for user grid
			over_lapping_cheak_y = prev_ship_location[i][1];
		}
		else if(user_or_computer == 'c')
		{
			over_lapping_cheak_x = prev_ship_location_comp[i][0];              //cheaking other ships cordnates that they match with it or not for computer grid
			over_lapping_cheak_y = prev_ship_location_comp[i][1];
		}


		


		for (int j = 1; j <= second_loop_compare_time; j++)
		{
			
			int cheaker = 0;
			if(user_or_computer=='u')
				cheaker = prev_ship_location[ship_number][0];           // this variable for comparing preesed ship cordinate with others for user
			else
				cheaker = prev_ship_location_comp[ship_number][0];           // this variable for comparing preesed ship cordinate with others for computer


			int iteration;
			if (ship_number == 0)
				iteration = 4;
			else if (ship_number == 1 || ship_number == 2)
				iteration = 3;
			else if (ship_number == 3 || ship_number == 4 || ship_number == 5)
				iteration = 2;
			else
				iteration = 1;
			for (int k = 1; k <= iteration; k++)
			{
				if (user_or_computer == 'u')
				{
					if ((cheaker == over_lapping_cheak_x || cheaker == over_lapping_cheak_x - 33 || cheaker == over_lapping_cheak_x + prev_ship_location[ship_number][2]) && ((prev_ship_location[ship_number][1] == over_lapping_cheak_y) || (prev_ship_location[ship_number][1] == over_lapping_cheak_y + 41) || (prev_ship_location[ship_number][1] == over_lapping_cheak_y - 41)))
					{
						loop_breaker = 1;
						if (auto_or_manual == 'M')
						{
							prev_ship_location[ship_number][0] = prev_initial_position_x;
							prev_ship_location[ship_number][1] = prev_initial_position_y;
						}
						else
							return 1;
						break;
					}
				}

				if (user_or_computer == 'c')
				{
					if ((cheaker == over_lapping_cheak_x || cheaker == over_lapping_cheak_x - 33 || cheaker == over_lapping_cheak_x + prev_ship_location_comp[ship_number][2]) && ((prev_ship_location_comp[ship_number][1] == over_lapping_cheak_y) || (prev_ship_location_comp[ship_number][1] == over_lapping_cheak_y + 41) || (prev_ship_location_comp[ship_number][1] == over_lapping_cheak_y - 41)))
					{
						loop_breaker = 1;
						if (auto_or_manual == 'M')
						{
							prev_ship_location[ship_number][0] = prev_initial_position_x;
							prev_ship_location[ship_number][1] = prev_initial_position_y;
						}
						else
							return 1;
						break;
					}
				}
				
				
			
				cheaker += 33;
			}

			over_lapping_cheak_x += 33;

			if (loop_breaker == 1)
				break;

		}
		if (loop_breaker == 1)
			break;

	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void battle_round()
{

	
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors







	DrawSquare(0, 0, 1500, colors[LIGHT_BLUE]);
	
	


	DrawRoundRect(950, 50, 250, 35, colors[DARK_BLUE]);
	DrawString(965, 53, "Back", colors[WHITE]);

	if ((cord_x >= 1191 && cord_x <= 1279) && (cord_y >= 647 && cord_y <= 675))// For back button
	{
		glutDisplayFunc(newgame);
		
		
	}

	//For printing grid of 12 by 24
	float x1 = 110, y1 = 73, y2 = 524, x2 = 869;
	float new_x = x1;
	for (int i = 1; i <= 24; i++, x1 += 33)           // For printing vertical lines
	{
		if (i == 12 || i == 1 || i == 24 || i == 13 || i == 14 || i == 2)
		{
			DrawLine(x1, y1, x1, y2, 4, colors[WHITE]);
		}
		else
			DrawLine(x1, y1, x1, y2, 1, colors[WHITE]);
	}

	for (int i = 1; i <= 12; i++, y1 += 41)            // For printing horizontal lines
	{
		if (i == 1 || i == 11 || i == 12)
		{
			DrawLine(new_x, y1, x2, y1, 4, colors[WHITE]);
		}
		else
			DrawLine(new_x, y1, x2, y1, 1, colors[WHITE]);
	}




	// Placed user ships

	DrawRoundRect(prev_ship_location[0][0], prev_ship_location[0][1], prev_ship_location[0][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[1][0], prev_ship_location[1][1], prev_ship_location[1][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[2][0], prev_ship_location[2][1], prev_ship_location[2][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[3][0], prev_ship_location[3][1], prev_ship_location[3][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[4][0], prev_ship_location[4][1], prev_ship_location[4][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[5][0], prev_ship_location[5][1], prev_ship_location[5][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[6][0], prev_ship_location[6][1], prev_ship_location[6][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[7][0], prev_ship_location[7][1], prev_ship_location[7][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[8][0], prev_ship_location[8][1], prev_ship_location[8][2], prev_ship_location[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location[9][0], prev_ship_location[9][1], prev_ship_location[9][2], prev_ship_location[0][3], colors[BLACK], 30);




	DrawString(270, 550, "PLAYER1", colors[WHITE]);
	DrawString(660, 550, "COMPUTER", colors[WHITE]);













	

	DrawString(123, 452, "A", colors[WHITE]);
	DrawString(123, 411, "B", colors[WHITE]);
	DrawString(123, 370, "C", colors[WHITE]);
	DrawString(123, 329, "D", colors[WHITE]);
	DrawString(123, 288, "E", colors[WHITE]);
	DrawString(123, 247, "F", colors[WHITE]);
	DrawString(122, 207, "G", colors[WHITE]);
	DrawString(121, 167, "H", colors[WHITE]);
	DrawString(125, 127, "I", colors[WHITE]);
	DrawString(123, 87, "J", colors[WHITE]);

	DrawString(156, 493, "1", colors[WHITE]);
	DrawString(189, 493, "2", colors[WHITE]);
	DrawString(222, 493, "3", colors[WHITE]);
	DrawString(255, 493, "4", colors[WHITE]);
	DrawString(288, 493, "5", colors[WHITE]);
	DrawString(321, 493, "6", colors[WHITE]);
	DrawString(354, 493, "7", colors[WHITE]);
	DrawString(387, 493, "8", colors[WHITE]);
	DrawString(420, 493, "9", colors[WHITE]);
	DrawString(448, 493, "10", colors[WHITE]);



	DrawString(519, 452, "A", colors[WHITE]);
	DrawString(519, 411, "B", colors[WHITE]);
	DrawString(519, 370, "C", colors[WHITE]);
	DrawString(519, 329, "D", colors[WHITE]);
	DrawString(519, 288, "E", colors[WHITE]);
	DrawString(519, 247, "F", colors[WHITE]);
	DrawString(518, 207, "G", colors[WHITE]);
	DrawString(517, 167, "H", colors[WHITE]);
	DrawString(521, 127, "I", colors[WHITE]);
	DrawString(519, 87, "J", colors[WHITE]);

	DrawString(552, 493, "1", colors[WHITE]);
	DrawString(585, 493, "2", colors[WHITE]);
	DrawString(618, 493, "3", colors[WHITE]);
	DrawString(651, 493, "4", colors[WHITE]);
	DrawString(684, 493, "5", colors[WHITE]);
	DrawString(717, 493, "6", colors[WHITE]);
	DrawString(750, 493, "7", colors[WHITE]);
	DrawString(783, 493, "8", colors[WHITE]);
	DrawString(816, 493, "9", colors[WHITE]);
	DrawString(846, 493, "10", colors[WHITE]);
	
	/*
	DrawRoundRect(prev_ship_location_comp[0][0], prev_ship_location_comp[0][1], prev_ship_location_comp[0][2], prev_ship_location_comp[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location_comp[1][0], prev_ship_location_comp[1][1], prev_ship_location_comp[1][2], prev_ship_location_comp[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location_comp[2][0], prev_ship_location_comp[2][1], prev_ship_location_comp[2][2], prev_ship_location_comp[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location_comp[3][0], prev_ship_location_comp[3][1], prev_ship_location_comp[3][2], prev_ship_location_comp[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location_comp[4][0], prev_ship_location_comp[4][1], prev_ship_location_comp[4][2], prev_ship_location_comp[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location_comp[5][0], prev_ship_location_comp[5][1], prev_ship_location_comp[5][2], prev_ship_location_comp[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location_comp[6][0], prev_ship_location_comp[6][1], prev_ship_location_comp[6][2], prev_ship_location_comp[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location_comp[7][0], prev_ship_location_comp[7][1], prev_ship_location_comp[7][2], prev_ship_location_comp[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location_comp[8][0], prev_ship_location_comp[8][1], prev_ship_location_comp[8][2], prev_ship_location_comp[0][3], colors[BLACK], 30);
	DrawRoundRect(prev_ship_location_comp[9][0], prev_ship_location_comp[9][1], prev_ship_location_comp[9][2], prev_ship_location_comp[0][3], colors[BLACK], 30);
	*/







	
	if (cheak == 0)       // For cheaking that it may not run for more than 1 time
	auto_place_ships_comp();
	cheak = 1;

	

		if (game_turn_setter % 2 == 0)
		{


			int i, j;                   // For cheaking which location user has clicked
			int loop_cheaker = 0;
			int x = 0, y = 0;  // For cheaking where the missile hit
			if (cord_x >= 636 && cord_x <= 1091 && cord_y >= 271 && cord_y < 657)
			{
				for (i = 0; i < 11; i++)
				{
					for (j = 2; j < 13; j++)
					{
						if (((cord_x >= (mouse_grid2[i][j]) / 1000)) && (cord_x <= (mouse_grid2[i - 1][j + 1] / 1000)) && (cord_y >= (mouse_grid2[i][j] % 1000)) && (cord_y <= (mouse_grid2[i - 1][j + 1] % 1000)))
						{
							loop_cheaker = 1;
							break;
						}
					}
					if (loop_cheaker == 1)
						break;
				}

				if (i == 1)
				{
					x = second_grid[i - 1][j] / 100;
					y = second_grid[i - 1][j] % 100;
				}
				else
				{
					x = second_grid[i - 1][j] / 1000;
					y = second_grid[i - 1][j] % 1000;
				}


















				int length_increaser = 0;
				int loop_breaker = 0;
				for (int l = 0; l < 10; l++)
				{
					int m_times;
					length_increaser = 0;
					if (l == 0)
						m_times = 4;
					if (l == 1 || l == 2)
						m_times = 3;
					if (l == 3 || l == 4 || l == 5)
						m_times = 2;
					else
						m_times = 1;
					for (int m = 1; m <= m_times; m++)
					{
						if ((x == (prev_ship_location_comp[l][0] + length_increaser)) && (y == (prev_ship_location_comp[l][1])))
						{
							hitted_ships[0] = prev_ship_location_comp[l][0] + 8;
							hitted_ships[1] = prev_ship_location_comp[l][1] + 5;
							hitter += 1;
							player_score += 30;
							loop_breaker = 1;
							break;
						}

						length_increaser += 33;





					}
					if (loop_breaker == 1)
					{
						break;
					}
				}











				hitted_ships_permanent[hitter][0] = hitted_ships[0];
				hitted_ships_permanent[hitter][1] = hitted_ships[1];




				cord_x = 0;
				cord_y = 0;




			}
		}
		else
		{




			srand(time(NULL));
			int x_two = 0;
			int y_two = 0;
			x_two = rand() % 12;
			y_two = rand() % 12;
			if (y_two == 0)
			{
				x_two = first_grid[x_two][y_two] / 100;
				y_two = first_grid[x_two][y_two] % 100;
			}
			else
			{
				x_two = first_grid[x_two][y_two] / 1000;
				y_two = first_grid[x_two][y_two] % 1000;
			}

			int length_increaser2 = 0;
			int loop_breaker2 = 0;
			for (int l = 0; l < 10; l++)
			{
				int m_times;
				length_increaser2 = 0;
				if (l == 0)
					m_times = 4;
				if (l == 1 || l == 2)
					m_times = 3;
				if (l == 3 || l == 4 || l == 5)
					m_times = 2;
				else
					m_times = 1;
				for (int m = 1; m <= m_times; m++)
				{
					if ((x_two == (prev_ship_location[l][0] + length_increaser2)) && (y_two == (prev_ship_location[l][1])))
					{
						hitted_ships[0] = prev_ship_location[l][0] + 8;
						hitted_ships[1] = prev_ship_location[l][1] + 5;
						hitter2 += 1;
						loop_breaker2 = 1;
						break;
					}

					length_increaser2 += 33;





				}
				if (loop_breaker2 == 1)
				{
					break;
				}
			}



			hitted_ships2_permanent[hitter2][0] = hitted_ships[0];
			hitted_ships2_permanent[hitter2][1] = hitted_ships[1];




		}
	


		for (int p = 0; p < 500; p++)
		{
			DrawString(hitted_ships_permanent[p][0], hitted_ships_permanent[p][1], "X", colors[RED]);
			DrawString(hitted_ships2_permanent[p][0], hitted_ships2_permanent[p][1], "X", colors[RED]);
		}
		game_turn_setter += 1;

		

		DrawString(100, 800, "SCORE: ", colors[WHITE]);
		
		DrawString(200, 800, Num2Str(player_score), colors[WHITE]);

	
	
	
	

	glutSwapBuffers();
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



















////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void leaderboard()
{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	
	DrawRoundRect(850, 800, 250, 35, colors[RED]);
	DrawString(850, 810, "Back to menu", colors[WHITE]);
	if ((cord_x >= 1069 && cord_x <= 1279) && (cord_y >= 3 && cord_y <= 31))// For back button
	{
		glutDisplayFunc(menu);
	}
	fstream leaderboard;
	

	DrawString(170, 700, "Highscores", colors[WHITE]);
	DrawString(100, 650, "Names", colors[WHITE]);
	DrawString(300, 650, "Scores", colors[WHITE]);
	
	string username, score;
	int x_leader = 100, y_leader = 600;
	

	leaderboard.open("leadernames.txt", ios::in | ios::app);

	while (1)
	{

		if (leaderboard.eof())
		{
			break;
		}

		getline(leaderboard, username);


		DrawString(x_leader, y_leader, username, colors[WHITE]);


		y_leader -= 50;



	}
	leaderboard.close();
	y_leader = 600;
	leaderboard.open("highscores.txt", ios::in | ios::app);
	
		while (1)
		{

			if (leaderboard.eof())
			{
				break;
			}

			getline(leaderboard, score);

			
			DrawString(x_leader+200, y_leader, score, colors[WHITE]);
			
			
			y_leader -= 50;

			

		}
		
		leaderboard.close();
		
		


	
	
	

	glutSwapBuffers();

}



/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void balance()
{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	DrawRoundRect(850, 800, 250, 35, colors[RED]);
	DrawString(850, 810, "Back to menu", colors[WHITE]);

	if ((cord_x >= 1069 && cord_x <= 1279) && (cord_y >= 3 && cord_y <= 31))// For back button
	{
		glutDisplayFunc(menu);
	}


	fstream leaderboard;


	
	DrawString(300, 650, "CURRENT BALANCE: ", colors[WHITE]);

	string balance;

	leaderboard.open("balance.txt", ios::in | ios::app);
	getline(leaderboard, balance);
	leaderboard.close();
	DrawString(500, 650, balance, colors[WHITE]);







	glutSwapBuffers();

}



/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void option()
{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	DrawRoundRect(850, 800, 250, 35, colors[RED]);
	DrawString(850, 810, "Back to menu", colors[WHITE]);

	if ((cord_x >= 1069 && cord_x <= 1279) && (cord_y >= 3 && cord_y <= 31)) // For back button
	{
		glutDisplayFunc(menu);
	}




	DrawRectangle(200, 400, 150, 50, colors[WHITE]);
	DrawString(210, 410, "Mines", colors[BLACK]);

	DrawRectangle(400, 400, 150, 50, colors[WHITE]);
	DrawString(410, 410, "Bombers", colors[BLACK]);

	DrawRectangle(600, 400, 150, 50, colors[WHITE]);
	DrawString(610, 410, "Sub-marines", colors[BLACK]);












	glutSwapBuffers();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








#endif /* Battleship_CPP_ */



