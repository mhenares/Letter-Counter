// Header Files
# include <fstream>
# include "formatted_console_io_v18.h"

using namespace std;

// Global Constants
const int STRING_MAX=80;
const int LEFT_BORDER_X=12, LETTERS_LEFT_BORDER = 9, COUNT_LEFT_BORDER = 11, J_INDEX = 9, S_INDEX = 18;
const int TOP_BORDER_Y=3;
const int MAX_FOR_LINES=1000;
const int LETTER_MAX=26;
const char ENDLINE_CHAR = '\n', NULL_CHAR='\0';

// Function Prototypes

/*
 Name: loadFile
 Process: loads array c-style strings with data from a file
 Function Input Parameters: fin (ifstream), file name (char), line of text array (char)
 Function Output Parameters: none
 Function Output Return: found file (bool)
 Device Input/Keyboard: none
 Device Output/MOnitor: none
 Dependencies: fstream, formatted console
 */
int loadFile( ifstream &fin, char fileName[], char lineString[][STRING_MAX] );

/*
 Name: displayMenu
 Process: displays main menu and returns user input
 Function Input Parameters: found file (bool)
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: none
 Device Output/MOnitor: displayed menu
 Dependencies: formatted console
 */
char displayMenu( bool fileFound );

/*
 Name: enterFileNameModule
 Process: displays module asking user to type file name
 Function Input Parameters: file name (char)
 Function Output Parameters: none
 Function Output Return: if file is found (bool)
 Device Input/Keyboard: none
 Device Output/MOnitor: displayed module
 Dependencies: formatted console
 */
bool enterFileNameModule( char fileName[] );

/*
 Name: showUpperCaseModule
 Process: displays module that shows upper case letters
 Function Input Parameters: number of letters array (int)
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: none
 Device Output/MOnitor: displayed module
 Dependencies: formatted console
 */
void showUpperCaseModule( int upperCaseCount[], char fileName[], char lineString[][STRING_MAX]  );

/*
 Name: showLowerCaseModule
 Process: displays module that shows lower case letters
 Function Input Parameters: number of letters array (int)
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: none
 Device Output/MOnitor: displayed module
 Dependencies: formatted console
 */
void showLowerCaseModule( int lowerCaseCount[], char filename[], char lineString[][STRING_MAX]  );

/*
 Name: countUpperCase
 Process: counts how many times a letter appears and saves the amount into an array
 Function Input Parameters: array of lines (char), array of letter counts (int)
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: none
 Device Output/MOnitor: none
 Dependencies: none
 */
void countUpperCase( char lineString[][STRING_MAX], int upperCaseCount[], int size );

/*
 Name: countLowerCase
 Process: counts how many times a letter appears and saves the amount into an array
 Function Input Parameters: array of lines (char), array of letter counts (int)
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: none
 Device Output/MOnitor: none
 Dependencies: none
 */
void countLowerCase( char lineString[][STRING_MAX], int lowerCaseCount[], int size );

/*
 Name: endProgram
 Process: shuts down curses, quits program
 Function Input Parameters: none
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: none
 Device Output/MOnitor: none
 Dependencies: formatted console
 */
bool goodFile( char fileName[] );


// Main Function

int main ()
{
    // initialize program/function
    
       // initialize variables
       bool fileFound = false;
       char choice, fileName[STRING_MAX], lineString[MAX_FOR_LINES][STRING_MAX];
       int upperCaseCount[LETTER_MAX], lowerCaseCount[LETTER_MAX];
    
       // start curses
          // function: startCurses
       startCurses();
    
       // clear screen
          // function: clearScreen
       clearScreen(SCRN_MIN_X, SCRN_MIN_Y, SCRN_MAX_X, SCRN_MAX_Y);
    
       // set color
          // function: setColor
       setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );
    
       // begin do while menu loop
       do
       {
           // display menu
              // function: displayMenu
             choice = displayMenu( fileFound );
           
           //wait for input
              // function: waitForInput
           waitForInput( FIXED_WAIT );

           // if user selects first option
           if(choice == 'F' || choice == 'f' || choice == '1')
           {
               // display enter file name module
                  // function: enterFileNameModule
               fileFound = enterFileNameModule( fileName );
           }
 
           // if user selects second option and file is found
           if((choice == 'U' || choice == 'u' || choice == '2') && fileFound == true)
           {
               // display show upper case module
                  // function: showUpperCaseModule
               showUpperCaseModule(upperCaseCount, fileName, lineString);
           }
           // if user selects third option and file is found
           if((choice == 'L' || choice == 'l' || choice == '3') && fileFound == true)
           {
               // display show lower case module
                 // function: showLowerCaseModule
               showLowerCaseModule(lowerCaseCount, fileName, lineString);
           }
    
    // loop while user doesnt want to exit
       }
       while(choice != 'A' && choice != 'a' && choice != '4');
    // end loop

    // end program
    
       // if user selects fourth option
       if(choice == 'A' || choice == 'a' || choice == '4')
       {
           // end program
              // function: endProgram
           endCurses();

       }
    
    // return
    return 0;
}

// Supporting Function Implementations

int loadFile( ifstream &fin, char fileName[], char lineString[][STRING_MAX] )
{
    // initialize function/variables
    char tempString[STRING_MAX];
    int columnIndex, rowIndex = 0, length;
    
    // clear and open file
       // function: .clear, .open
    fin.clear();
    fin.open( fileName );
    
    // loop while file is good
    while( fin.good() )
    {
        // load data to temporary array
           // function: fstream >>
        fin.getline( tempString, STRING_MAX, ENDLINE_CHAR );
        length = strlen( tempString );
        
        // reset index
        columnIndex=0;
        
        // load to 2-D array
        while( columnIndex <= length )
        {
            lineString[rowIndex][columnIndex] = tempString[columnIndex];
            
            //index row index
            columnIndex++;
        }
        
        // increment column index
        rowIndex++;
    }
    
    // close file
       // function: .close
    fin.close();
    
    // return
    return rowIndex;
}

char displayMenu( bool fileFound )
{
    // initialize function/variables
    int xPos = LEFT_BORDER_X, yPos = TOP_BORDER_Y;
    char choice;
    
    // clear screen
    // function: clearScreen
    clearScreen(SCRN_MIN_X, SCRN_MIN_Y, SCRN_MAX_X, SCRN_MAX_Y);
    
    // set color
    // function: setColor
    setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );
    
    // display main menu
       // funtion: printStringAt
    printStringAt( xPos, yPos, "TEXT ANALYSIS PROGRAM", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "=====================", "LEFT");
    yPos+=2;
    printStringAt( xPos, yPos, "Analysis Menu", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "-------------", "LEFT");
    yPos+=2;
    printStringAt( xPos, yPos, "1. Set <F>ile name", "LEFT");
    xPos+=19;
    
    if( fileFound == true )
    {
        setColor( COLOR_YELLOW, COLOR_BLUE, SET_BRIGHT);
        printStringAt( xPos, yPos, "<File Name Loaded>", "LEFT");
    }
    
    else
    {
        setColor( COLOR_RED, COLOR_BLUE, SET_BRIGHT);
        printStringAt( xPos, yPos, "<File Name Not Loaded>", "LEFT");
    }

    setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT);
    xPos = LEFT_BORDER_X;
    yPos++;
    printStringAt( xPos, yPos, "2. Show <U>pper case letter fequency", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "3. Show <L>ower case letter fequency", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "2. End <A>nalysis program", "LEFT");
    
    // prompt user
       // function: promptForCharAt
    yPos+=3;
    choice = promptForCharAt( xPos, yPos, "Enter Selection: ");
    
    waitForInput( FIXED_WAIT );
    
    //return
    return choice;
}

bool enterFileNameModule( char fileName[] )
{
    // initialize function/variables
    ifstream fin;
    int xPos, yPos;
    bool fileGood;
    
    // clear screen
       // function: clearScreen
    clearScreen(SCRN_MIN_X, SCRN_MIN_Y, SCRN_MAX_X, SCRN_MAX_Y);
    
    // set color
       // function: setColor
    setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );
    
    // display module
    xPos = LEFT_BORDER_X;
    yPos = TOP_BORDER_Y;
    printStringAt( xPos, yPos, "File Name Loading Module", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "------------------------", "LEFT");
    yPos+=2;
    promptForStringAt( xPos, yPos, "Enter file name: ", fileName);
    
    // check if file is good
       // function: goodFile
    fileGood = goodFile( fileName );
    
    //return
    return fileGood;

}

void showUpperCaseModule( int upperCaseCount[], char fileName[], char lineString[][STRING_MAX] )
{
    // initialize function/variables
    int xPos = LEFT_BORDER_X, yPos=TOP_BORDER_Y, index=0 , size;
    ifstream fin;
    
    // clear screen
       // function: clearScreen
    clearScreen(SCRN_MIN_X, SCRN_MIN_Y, SCRN_MAX_X, SCRN_MAX_Y);
    
    // set color
       // function: setColor
    setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );
    
    // load file
       // function: loadFile
    size = loadFile( fin, fileName, lineString);
        
    // get counts to array
       // function: countUpperCase
    countUpperCase( lineString, upperCaseCount, size );
    
    // display module
       // function: printStringAt
    printStringAt( xPos, yPos, "Upper Case Letter Frequency Module", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "----------------------------------", "LEFT");
    xPos = LETTERS_LEFT_BORDER;
    yPos+=2;
    printStringAt( xPos, yPos, "  A     B     C     D     E     F     G     H     I    ", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "----- ----- ----- ----- ----- ----- ----- ----- -----  ", "LEFT");
    
    xPos = COUNT_LEFT_BORDER;
    yPos++; 
    
    while( index < J_INDEX )
    {
        printIntAt( xPos, yPos, upperCaseCount[index], "CENTER" );
        
        index++;
        
        xPos+=6;
    }
    
    yPos+=3;
    xPos = LETTERS_LEFT_BORDER;
    printStringAt( xPos, yPos, "  J     K     L     M     N     O     P     Q     R    ", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "----- ----- ----- ----- ----- ----- ----- ----- -----  ", "LEFT");
    yPos++;
    xPos = COUNT_LEFT_BORDER;
    
    while( index < S_INDEX )
    {
        printIntAt( xPos, yPos, upperCaseCount[index], "CENTER" );
        
        index++;
        
        xPos+=6;
    }
    
    yPos+=3;
    xPos = LETTERS_LEFT_BORDER;
    printStringAt( xPos, yPos, "  S     T     U     V     W     X     Y     Z   ", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "----- ----- ----- ----- ----- ----- ----- ----- ", "LEFT");
    yPos++;
    xPos = COUNT_LEFT_BORDER;
    
    while( index < LETTER_MAX )
    {
        printIntAt( xPos, yPos, upperCaseCount[index], "CENTER" );
        
        index++;
        
        xPos+=6;
    }
    
    yPos+=3;
    xPos = LEFT_BORDER_X;
    printStringAt( xPos, yPos, "Upper Case letter frequency analysis complete.", "LEFT");
    yPos+=2;
    printStringAt( xPos, yPos, "Press any key to continue . . . ", "LEFT");
    
    // wait for user
       // function: waitForInput
    waitForInput(FIXED_WAIT);
}

void showLowerCaseModule( int lowerCaseCount[], char fileName[], char lineString[][STRING_MAX] )
{
    // initialize function/variables
    int xPos = LEFT_BORDER_X, yPos=TOP_BORDER_Y, index=0 , size;
    ifstream fin;
    
    // clear screen
       // function: clearScreen
    clearScreen(SCRN_MIN_X, SCRN_MIN_Y, SCRN_MAX_X, SCRN_MAX_Y);
    
    // set color
       // function: setColor
    setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );
    
    // load file
       // function: loadFile
    size = loadFile( fin, fileName, lineString);
    
    // get counts to array
       // function: countUpperCase
    countLowerCase( lineString, lowerCaseCount, size );
    
    // display module
       // function: printStringAt, printIntAt
    printStringAt( xPos, yPos, "Lower Case Letter Frequency Module", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "----------------------------------", "LEFT");
    xPos = LETTERS_LEFT_BORDER;
    yPos+=2;
    printStringAt( xPos, yPos, "  a     b     c     d     e     f     g     h     i    ", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "----- ----- ----- ----- ----- ----- ----- ----- -----  ", "LEFT");
    
    xPos = COUNT_LEFT_BORDER;
    yPos++; 
    
    while( index < J_INDEX )
    {
        printIntAt( xPos, yPos, lowerCaseCount[index], "CENTER" );
        
        index++;
        
        xPos+=6;
    }
    
    yPos+=3;
    xPos = LETTERS_LEFT_BORDER;
    printStringAt( xPos, yPos, "  j     k     l     m     n     o     p     q     r    ", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "----- ----- ----- ----- ----- ----- ----- ----- -----  ", "LEFT");
    yPos++;
    xPos = COUNT_LEFT_BORDER;
    
    while( index < S_INDEX )
    {
        printIntAt( xPos, yPos, lowerCaseCount[index], "CENTER" );
        
        index++;
        
        xPos+=6;
    }
    
    yPos+=3;
    xPos = LETTERS_LEFT_BORDER;
    printStringAt( xPos, yPos, "  s     t     u     v     w     x     y     z   ", "LEFT");
    yPos++;
    printStringAt( xPos, yPos, "----- ----- ----- ----- ----- ----- ----- ----- ", "LEFT");
    yPos++;
    xPos = COUNT_LEFT_BORDER;
    
    while( index < LETTER_MAX )
    {
        printIntAt( xPos, yPos, lowerCaseCount[index], "CENTER" );
        
        index++;
        
        xPos+=6;
    }
    
    yPos+=3;
    xPos = LEFT_BORDER_X;
    printStringAt( xPos, yPos, "Lower Case letter frequency analysis complete.", "LEFT");
    yPos+=2;
    printStringAt( xPos, yPos, "Press any key to continue . . . ", "LEFT");
    
    // wait for user
       // function: waitForInput
    waitForInput(FIXED_WAIT);
}

void countUpperCase( char lineString[][STRING_MAX], int upperCaseCount[], int size )
{
    // initialize function/variables
    char letter = 'A';
    int rowIndex = 0, columnIndex = 0, ctr = 0, index=0;;
    
    // loop through each letter
    while( letter <= 'Z')
    {
        // reset column index
        rowIndex=0;
        ctr = 0;
        
        // loop through each line
        while( rowIndex < size )
        {
            // reset row index
            columnIndex = 0;
           
            // loop though each character
            while( lineString[rowIndex][columnIndex] != NULL_CHAR)
            {
                
                // if character is a match
                if( lineString[rowIndex][columnIndex] == letter )
                {
                    //increment counter
                    ctr++;
                }
               
                // increment row index
                columnIndex++;
            }
           
            // increment column index
            rowIndex++;
        }
        
        // assign count to array
        upperCaseCount[index] = ctr;
        
        // increment index
        index++;
        
        // increment letter
        letter++;
    }
        
}

void countLowerCase( char lineString[][STRING_MAX], int lowerCaseCount[], int size )
{
    // initialize function/variables
    char letter = 'a';
    int rowIndex = 0, columnIndex = 0, ctr = 0, index=0;;
    
    // loop through each letter
    while( letter <= 'z')
    {
        // reset column index
        rowIndex=0;
        ctr = 0;
        
        // loop through each line
        while( rowIndex < size )
        {
            // reset row index
            columnIndex = 0;
            
            // loop though each character
            while( lineString[rowIndex][columnIndex] != NULL_CHAR)
            {
                
                // if character is a match
                if( lineString[rowIndex][columnIndex] == letter )
                {
                    //increment counter
                    ctr++;
                }
                
                // increment row index
                columnIndex++;
            }
            
            // increment column index
            rowIndex++;
        }
        
        // assign count to array
        lowerCaseCount[index] = ctr;
        
        // increment index
        index++;
        
        // increment letter
        letter++;
    }
    
}

bool goodFile( char fileName[] )
{
    // initialize function/variables
    ifstream fin;
    bool fileGood;
    
    // open/ clear file
       // function: .clear, .open
    fin.clear();
    fin.open( fileName );
    
    // if file is good
    if( fin.good() )
    {
        fileGood = true;
    }
    
    // otherwise
    else
        fileGood = false;
    
    // close file
       //function: .close
    fin.close();
    
    // return
    return fileGood;
    
}

