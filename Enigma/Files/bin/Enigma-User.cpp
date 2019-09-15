#include <iostream>	// Basic Console I/O Controls
#include <fstream>	// Basic File I/O Controls
#include <conio.h>	// For getch() function
#include <string.h>	// Basic String Manipulation
#include <stdlib.h>	// Giving cmd commands to the system
#include <robot.h>	// Custom Header File
#include <UID.h>	// Custom ( For Unique PassWord )
using namespace std;

char VER[4]={"20B"};	// Enter the Version Index Number here
char S_VER_R[][4] = {"2.0"};	// Enter the list of versions of robot.h header file Enigma is compilable with
char S_VER_U[][4] = {"1.0"};	// Enter the lsit of versions of UID.h header file Enigma is compilable with
char end_msg[] = "MR. ROBOT";	// Enter the message to be typed out when the program exits
char matrix_msg[] = "ENCRYPTED";	// Enter the message to be shown as matrix

char input[200] = "";	// Input File / Text
char output[200] = "";	// Output File /Text
char password[100] = "";	// Password text

int s_len;	// Variable for holding screen length
char selection = '\0';	// Variable to hold the users choices
int count = 0;	// Variable which acts as a counter globally
char UID[11];	// Variable to hold the Unique ID for the PC

char heading[] = "<<<<<-------------------ENIGMA--------------------->>>>>";	// The Heading of the console
char version[9] = "[Ver:";	// Version name to be displayed

class Configurations
{
	private:
		char last_pass[100] = "";	// Last used password // stored only till the program runs
		char last_UID[11] = "";	// Last workable UID	// stored only till the program runs
	
	public:
		char* get_last_pass(void)	// Return the last used password
		{
			return last_pass;
		}
		
		void save_pass(char* pass_to_save)	// Save the password to last_pass
		{
			strcpy( last_pass, pass_to_save );
			return;
		}
		
		char* get_last_UID(void)	// Return the last workable UID
		{
			return last_UID;
		}
		
		void save_UID(char* UID_to_save)	// Save the UID to last_UID
		{
			strcpy( last_UID, UID_to_save );
			return;
		}
}config;

// FUNCTION PROTOTYPES //


int CheckConfig(char);	// Checks if the Header File versions are supported
void show_heading(int animation);	// Output the Heading and the Version label
void show_mode(char, int);	// Output the program mode
void encryption(void);	// Encryption Menu
void decryption(void);	// Decryption Menu
void advanced(void);	// A select few advanced options
void developer(void);	// Developer Menu
void help(void);	// Help Menu
char* out_file_name(char*);	// Returns what the name of the output file should be acc to the name of the input file
void working_animation(void);	// Shows an animation when program is given a command
void exit_animation(void);	// Shows an animation at the end of the program

// DEVELOPER OPTIONS //

void developer(void);	// Developer Menu
void create_file(int);	// Create files according to a index number
int confirm_UID(void);	// Ask the user for the UID and check if it is correct

// DEVELOPER OPTIONS //

// MAIN FUNCTIONS //


int main()
{
	if( !CheckConfig( 'R' ) || !CheckConfig( 'U' ) )	// Checking the Version of robot.h and UID.h
	{
		cout << paragraph( "\n:: ENIGMA -------- Unsupported Header Files ::\n\n" );
		
		cout << paragraph( "## Version " )
			 << VER;
		cout << paragraph( " of Enigma supports the following Versions of Custom Header Files:\n" );
		cout << paragraph("\t## ROBOT.H:\n");
			
		for( int i = 0; i < ( sizeof( S_VER_R ) / ( 4 * sizeof( char ) ) ); i++ )	// Getting number of versions in suppoerted list and running the loop
		{
			cout << "\t\t" << paragraph( S_VER_R[i] ) << endl;
		}
		
		cout << paragraph( "\t## UID.H:\n" );
		for( int i = 0; i < ( sizeof( S_VER_U ) / ( 4 * sizeof( char ) ) ); i++ )	// Getting number of versions in suppoerted list and running the loop
		{
			cout << "\t\t" << paragraph( S_VER_U[i] ) << endl;
		}
		cout << endl << "Press any key to terminate...\n";
		getch();
		exit( 1 );
	}
	
	if( strlen( version ) != 9 )
	{
		app_string( version, VER );	// Appening the Version Index to the Version Label
		app_string( version, "]" );
	}
	
	console_cursor( 0 );
	
	show_heading( 1 );
	
	MAIN:
	
	show_heading( 0 );
	
	
	cout << paragraph("1. Encryption\n2. Decryption\n3. Advanced Options\n4. Developer\n5. Help\nc. Exit Program\n::" );
	console_cursor( 1 );
	selection = getch();
	console_cursor( 0 );
	cout << selection	<< endl << endl;
	
	switch( selection )
	{
		case '1':
			encryption();
			break;
		case '2':
			decryption();
			break;
		case '3':
			advanced();
			break;
		case '4':
			developer();
			break;
		case '5':
			help();
			break;
		case 'c':
			exit_animation();
			break;
		case 13:	// 13: Enter Key
			break;
		default:
			cout << paragraph( " Invalid Selection!\nPress any key to Retry\n" );
			getch();
			break;
	}
	goto MAIN;
	
	return 0;
}

int CheckConfig(char initial)
/*
initial:
	'R': robot.h
	'U': UID.h
*/
{
	
	char header_version[4];
	
	switch( initial )
	{
		case 'R':
			strcpy( header_version, get_version_robot() );
			
			count = 0;
			for( int i = 0; i < ( sizeof( S_VER_R ) / ( 4 * sizeof( char ) ) ); i++ )	// Getting number of versions in suppoerted list and running the loop
			{
				if( strcmp( S_VER_R[i], header_version ) == 0 )
				{
					count = 1;
				}
			}
			
			if( count == 1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
			
			break;
		case 'U':
			strcpy( header_version, get_version_UID() );
			
			count = 0;
			for( int i = 0; i < ( sizeof( S_VER_U ) / ( 4 * sizeof( char ) ) ); i++ )	// Getting number of versions in suppoerted list and running the loop
			{
				if( strcmp( S_VER_U[i], header_version ) == 0 )
				{
					count = 1;
				}
			}
			
			if( count == 1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
			
			break;
	}
}


void show_heading(int animation)
/*
animation:
	0: OFF
	1: ON
*/
{
	system( "cls" );
	center_align( heading );
	
	switch( animation )
	{
		case 0:
			cout.write( heading, strlen( heading ) );
			cout << endl;
			cout.write( version, strlen( version ) );
			cout << endl << endl;
			break;
		case 1:
			typeout( heading, 't', 900 );
			cout << endl;
			typeout( version, 't', 200 );
			cout << endl << endl;
			break;
	}
	
	return;
}


void show_mode(char mode, int animation)
/*
mode:
	'e': encryption
	'd': decryption
	'v': developer
	'h': help
animation:
	0: OFF
	1: ON
*/
{
	char full_mode[20];
	
	// Loading variable full_mode as per the parameter
	switch( mode )
	{
		case 'e':
			strcpy( full_mode, "// ENCRYPTION //");
			break;
		case 'd':
			strcpy( full_mode, "// DECRYPTION //");
			break;
		case 'h':
			strcpy( full_mode, "// HELP //");
			break;
		case 'a':
			strcpy( full_mode, "// ADVANCED //");
			break;
		case 'v':
			strcpy( full_mode, "// DEVELOPER //");
			break;
	}
	
	switch( animation )
	{
		case 0:
			cout.write( full_mode, strlen( full_mode ) );
			break;
		case 1:
			for( int i = 0; i < strlen( full_mode ); i++ )
			{
				gotoXY( + 5, 0, 1 );	// Move 15 space ahead of actual output position
				for( int j = getX(); j >= i; j-- )	// Runs loop will the time char does not get in its position (acc. to i)
				{
					cout << full_mode[i];
					
					Sleep( 1 );
					
					if( !( i == j ) )
					{
						// Cleans the previous output and moves to one position behind earlier
						gotoXY( -1, 0, 1 );
						cout << " ";
						gotoXY( -2, 0, 1 );
					}
				}
			}
			break;
	}
	cout << endl << endl;
	
	return;
}


void encryption()
{
	fstream fout;	// File to save the output (if required)
	
	show_heading( 0 );
	show_mode( 'e', 1 );
	
	
	ENCRYPTION_TYPE:
	
	show_heading( 0 );
	show_mode( 'e', 0 );
	
	cout << paragraph( "What do you want to Encrypt?\n" );
	cout << paragraph( "1. File on Computer\n2. Message (Console Input)\nc. Cancel\n::");	// Options to encrypt a file or a message directly
	console_cursor( 1 );
	selection = getch();
	console_cursor( 0 );
	cout << selection	<< endl << endl;
	
	switch( selection )
	{
		case 13:	// 13: Enter Key
			goto ENCRYPTION_TYPE;
			break;
		case '1':
			ENCRYPTION_DATA_ENTRY:
			
			// Clearing File Variables
			for( int i = 0; i < 200; i++ )
			{
				input[i] = '\0';
				output[i] = '\0';
			}
			
			
			show_heading( 0 );
			show_mode( 'e', 0 );
			
			typeout( paragraph( ":: Select the input FILE ::" ), 't', 2000 );
			cout << endl << endl;
			strcpy( input, select_file( "", 1 ) );	// Getting input file
			if( strlen( input ) == 0 )	// In the case user cancels
			{
				return;
			}
			
			show_heading( 0 );	// Clearing the screen after getting the input
			show_mode( 'e', 0 );
			
			cout << paragraph( "The selected input file is:\n" ) << input << endl << endl;
			
			typeout( paragraph( ":: Select the output FOLDER ::" ), 't', 2000 );
			cout<< endl << endl;
			strcpy( output, select_file( "", 2 ) );	// Getting the output file
			if( strlen( output ) == 0 )	// In the case user cancels
			{
				return;
			}
			
			show_heading( 0 );	// Clearing the screen after getting the output folder
			show_mode( 'e', 0);
			
			cout << paragraph( "The selected input file is:\n" ) << input << endl << endl;
			
			// Adding the name of the file to the output
			app_string( output, "/" );
			app_string( output, out_file_name( input ) );
			
			cout << paragraph( "The output will be saved in the file:\n") << output << endl << endl;
			
			ENCRYPTION_FILE_PASSWORD:
			for( int i = 0; i < 100; i++ )
			{
				password[i] = '\0';	// Clearing variable password
			}
			
			if(! strlen( config.get_last_pass() ) == 0 )	// If an old password is saved
			{
				typeout( paragraph( "Use the previous Password? [y/*]: "), 't', 1000 );
				console_cursor( 1 );
				selection = getch();
				cout << selection << endl << endl;
				console_cursor( 0 );
				
				switch( selection )
				{
					case 'y':	// Use it
						strcpy( password, config.get_last_pass() );
						cout << paragraph( "Password being used: " );
						cout << paragraph( password );
						cout << endl << endl;
						break;
					default:	// Create new entry
						typeout( paragraph( "Enter Password for Encryption: "), 't', 1000 );
						pass_entry( password, 0, 12);	// Getting password for encrypting file
						cout << endl;
						break;
				}
			}
			else
			{
				// create new password entry
				typeout( paragraph( "Enter Password for Encryption: "), 't', 1000 );
				pass_entry( password, 0, 12);	// Getting password for encrypting file
				cout << endl;				
			}
			
			if( strlen( password ) == 0 || password[0] == ' ' )	// Lenth of password cannot be 0 and itmust not start with a blank (makes it possble that the entire password is blank, and also has no meaning)
			{
				cout << paragraph( "Invalid Password!\nPress any key to retry\n[Esc] Key to Cancel" );
				selection = getch();
				
				switch( selection )
				{
					case 27:	// Ascii value of Esc Key is 27
						break;
					default:
						cout << endl << endl;
						goto ENCRYPTION_FILE_PASSWORD;
				}
				
				break;
			}
			
			config.save_pass( password );
			
			ENCRYPTION_DATA_ACCURATE:
			typeout( paragraph( "Are the above mentioned details correct?\nPlease ensure that the password is correct and that you do not forget it. Your data can be lost forever!!\n[y/n]: " ), 't', 6000 );
			console_cursor( 1 );
			selection = getch();
			console_cursor( 0 );
			cout << selection << endl << endl;
			
			switch( selection )
			{
				case 'y':
					working_animation();
					encrypt(input, password, output);
					cout << endl;
					
					cout << paragraph( "[ | ] ENCRYPTION COMPLETE [ | ]\n\nPress any to go back to Main Menu\n" );
					getch();
					
					break;
				case 'n':
					ENCRYPTION_RETRY:
					cout << "Retry? [y/n]: ";
					console_cursor( 1 );
					selection = getch();
					console_cursor( 0 );
					cout << selection << endl << endl;
					
					switch( selection )
					{
						case 'y':
							goto ENCRYPTION_DATA_ENTRY;
							break;
						case 'n':
							break;
						default:
							cout << endl;
							goto ENCRYPTION_RETRY;
					}
					break;
				default:
					cout << paragraph( " Invalid Selection!\nPress any key to Retry\n[Esc] to Cancel\n" );
					selection = getch();
					
					switch( selection )
					{
						case 27:	// Ascii Value of Esc key is 27
							break;
						default:
							goto ENCRYPTION_DATA_ACCURATE;
					}
			}
			break;
		case '2':
			ENCRYPTION_TEXT_ENTRY:
			
			// Clearing Variables
			for( int i = 0; i < 200; i++ )
			{
				input[i] = '\0';
				output[i] = '\0';
			}
			
			show_heading( 0 );
			show_mode( 'e', 0 );
			
			typeout( paragraph( "Enter the Message to be Encrypted:\n" ), 't', 1000 );
			console_cursor( 1 );
			cin.getline( input, 200 );	// Getting the message to be encrypted
			console_cursor( 0 );
			cout << endl;
			
			if( strlen( input ) == 0 )	// If the input is empty
			{
				cout << paragraph( "Invalid Input!\nInput cannot be Empty!\nPress any key to retry\n[Esc] Key to Cancel" );
				selection = getch();
				
				switch( selection )
				{
					case 27:	// Ascii value of Esc Key is 27
						break;
					default:
						cout << endl << endl;
						goto ENCRYPTION_TEXT_ENTRY;
						break;
				}
			}
			
			ENCRYPTION_TEXT_PASSWORD:
			for( int i = 0; i < 100; i++ )
			{
				password[i] = '\0';	// Clearing variable password
			}
			
			if(! strlen( config.get_last_pass() ) == 0 )
			{
				typeout( paragraph( "Use the previous Password? [y/*]: "), 't', 1000 );
				console_cursor( 1 );
				selection = getch();
				cout << selection << endl << endl;
				console_cursor( 0 );
				
				switch( selection )
				{
					case 'y':
						strcpy( password, config.get_last_pass() );
						cout << paragraph( "Password being used: " );
						cout << paragraph( password );
						cout << endl << endl;
						break;
					default:
						typeout( paragraph( "Enter Password for Encryption: "), 't', 1000 );
						pass_entry( password, 0, 12);	// Getting password for encrypting file
						cout << endl;
						break;
				}
			}
			else
			{
				typeout( paragraph( "Enter Password for Encryption: "), 't', 1000 );
				pass_entry( password, 0, 12);	// Getting password for encrypting file
				cout << endl;			
			}
			
			if( strlen( password ) == 0 || password[0] == ' ' )	// If the password is empty or has a space in the beginning
			{
				cout << paragraph( "Invalid Password!\nPress any key to retry\n[Esc] Key to Cancel" );
				selection = getch();
				
				switch( selection )
				{
					case 27:	// Ascii value of Esc Key is 27
						break;
					default:
						cout << endl << endl;
						goto ENCRYPTION_TEXT_PASSWORD;
						break;
				}
			}
			
			config.save_pass( password );
			
			working_animation();
			strcpy( output, encrypt( input, password ) );
			
			// Display the output
			cout << paragraph( "\nENIGMA:\n\t" );
			typeout( paragraph( output ), 't', 1000 * ( strlen( output ) / 3) );
			cout << endl <<endl;
			
			
			ENCRYPTION_OUT_SAVE:
			cout << paragraph( "Do you want to save the output?\n[y/n]: ");	// Save the encrypted output to a file
			console_cursor( 1 );
			selection = getch();
			console_cursor( 0 );
			cout << selection << endl << endl;
			
			switch( selection )
			{
				case 'y':
					char out_loc[200];
					
					show_heading( 0 );	// Clear Screen after selection
					show_mode( 'e', 0 );
					
					// Display the output
					cout << paragraph( "ENIGMA:\n\t" );
					cout << paragraph( output );
					cout << endl <<endl;
					
					typeout( ":: Select FOLDER to save output ::\n\n", 't', 2000 );
					strcpy( out_loc, select_file( "", 2) );	// Getting the output location
					if( strlen( out_loc ) == 0 )	// In the case user cancels
					{
						return;
					}
					
					// Adding File Name to the location
					app_string( out_loc, "/EnigmaOut.txt" );
					
					show_heading( 0 );
					show_mode( 'e', 0 );
					
					// Display the output
					cout << paragraph( "ENIGMA:\n\t" );
					cout << paragraph( output );
					cout << endl <<endl;
					
					cout << paragraph( "Saving the Output to:\n" );
					cout << paragraph( out_loc );
					cout << endl << endl;
					
					fout.open( out_loc, ios::out | ios::app );
					
					// Writing output to the file
					fout.write( input, strlen( input ) );
					fout << ": ";
					fout.write( output, strlen( output ) - 1 );	// Skipping the '\n' attatched to the output
					fout << " [ PASS: ";
					fout.write( password, strlen( password ) );
					fout << "]\n";
					
					fout.close();
					
					// Small Animation for finishing
					for( int i = 0; i < screen_len() - 4; i++ )
					{
						cout<<".";
						Sleep(25);
					}
					
					typeout( "...", 'i', 500 );
					
					cout << endl;
					cout << paragraph( "Output Saved\n\n" );
					cout << paragraph( "Press any key to continue to Main Menu OR press r to encrypt again\n" );	// Encrypt another message
					selection = getch();
					
					switch( selection )
					{
						case 'r':
							goto ENCRYPTION_TEXT_ENTRY;
							break;
						default:
							break;
					}
					break;
				case 'n':
					cout << paragraph( "Press any key to continue to Main Menu OR press r to encrypt again\n" );	// Encrypt another message
					selection = getch();
					
					switch( selection )
					{
						case 'r':
							goto ENCRYPTION_TEXT_ENTRY;
							break;
						default:
							break;
					}
					break;
				default:
					cout << paragraph( " Invalid Selection!\nPress any key to Retry\n" );
					getch();
					
					cout << endl;
					goto ENCRYPTION_OUT_SAVE;
			}
			
			break;
		case 'c':
			break;
		default:
			cout << paragraph( " Invalid Selection!\nPress any key to Retry\n[Esc] to Cancel\n" );
			selection = getch();
			
			switch( selection )
			{
				case 27:	// Ascii Value of Esc key is 27
					break;
				default:
					goto ENCRYPTION_TYPE;
			}
			break;
	}
	
	return;
}

void decryption()
{
	fstream fout;	// File to save the output (if required)
	
	show_heading( 0 );
	show_mode( 'd', 1 );
	
	
	DECRYPTION_TYPE:
	
	show_heading( 0 );
	show_mode( 'd', 0 );
	
	cout << paragraph( "What do you want to Decrypt?\n" );
	cout << paragraph( "1. File on Computer\n2. Message (Console Input)\nc. Cancel\n::");	// Options to encrypt a file or a message directly
	console_cursor( 1 );
	selection = getch();
	console_cursor( 0 );
	cout << selection	<< endl << endl;
	
	switch( selection )
	{
		case 13:	// 13: Enter Key
			goto DECRYPTION_TYPE;
			break;
		case '1':
			DECRYPTION_DATA_ENTRY:
			
			// Clearing File Variables
			for( int i = 0; i < 200; i++ )
			{
				input[i] = '\0';
				output[i] = '\0';
			}
			
			
			show_heading( 0 );
			show_mode( 'd', 0 );
			
			typeout( paragraph( ":: Select the input FILE ::" ), 't', 2000 );
			cout << endl << endl;
			strcpy( input, select_file( "", 1 ) );	// Getting input file
			if( strlen( input ) == 0 )	// In the case user cancels
			{
				return;
			}
			
			show_heading( 0 );	// Clearing the screen after getting the input
			show_mode( 'd', 0 );
			
			cout << paragraph( "The selected input file is:\n" ) << input << endl << endl;
			
			typeout( paragraph( ":: Select the output FOLDER ::" ), 't', 2000 );
			cout<< endl << endl;
			strcpy( output, select_file( "", 2 ) );	// Getting the output file
			if( strlen( output ) == 0 )	// In the case user cancels
			{
				return;
			}
			
			show_heading( 0 );	// Clearing the screen after getting the output folder
			show_mode( 'd', 0);
			
			cout << paragraph( "The selected input file is:\n" ) << input << endl << endl;
			
			// Adding the name of the file to the output
			app_string( output, "/" );
			app_string( output, out_file_name( input ) );
			
			cout << paragraph( "The output will be saved in the file:\n") << output << endl << endl;
			
			DECRYPTION_FILE_PASSWORD:
			for( int i = 0; i < 100; i++ )
			{
				password[i] = '\0';	// Clearing variable password
			}
			
			if(! strlen( config.get_last_pass() ) == 0 )
			{
				typeout( paragraph( "Use the previous Password? [y/*]: "), 't', 1000 );
				console_cursor( 1 );
				selection = getch();
				cout << selection << endl << endl;
				console_cursor( 0 );
				
				switch( selection )
				{
					case 'y':
						strcpy( password, config.get_last_pass() );
						break;
					default:
						typeout( paragraph( "Enter Password for Decryption: "), 't', 1000 );
						pass_entry( password, '*', 12);	// Getting password for encrypting file
						cout << endl;
						break;
				}
			}
			else
			{
				typeout( paragraph( "Enter Password for Decryption: "), 't', 1000 );
				pass_entry( password, '*', 12);	// Getting password for encrypting file
				cout << endl;
			}
			
			if( strlen( password ) == 0 || password[0] == ' ' )
			{
				cout << paragraph( "Invalid Password!\nPress any key to retry\n[Esc] Key to Cancel" );
				selection = getch();
				
				switch( selection )
				{
					case 27:	// Ascii value of Esc Key is 27
						break;
					default:
						cout << endl << endl;
						goto DECRYPTION_FILE_PASSWORD;
				}
				
				break;
			}
			
			config.save_pass( password );
			
			DECRYPTION_DATA_ACCURATE:
			typeout( paragraph( "Are the above mentioned details correct?\nPlease ensure that the password is correct or the output will be gibberish and undesired!!\n[y/n]: " ), 't', 6000 );
			console_cursor( 1 );
			selection = getch();
			console_cursor( 0 );
			cout << selection << endl << endl;
			
			switch( selection )
			{
				case 'y':
					working_animation();
					decrypt(input, password, output);
					cout << endl;
					
					cout << paragraph( "[ | ] DECRYPTION COMPLETE [ | ]\n\nPress any to go back to Main Menu\n" );
					getch();
					
					break;
				case 'n':
					DECRYPTION_RETRY:
					cout << "Retry? [y/n]: ";
					selection = getch();
					cout << selection << endl << endl;
					
					switch( selection )
					{
						case 'y':
							goto DECRYPTION_DATA_ENTRY;
							break;
						case 'n':
							break;
						default:
							cout << endl;
							goto DECRYPTION_RETRY;
					}
					break;
				default:
					cout << paragraph( " Invalid Selection!\nPress any key to Retry\n[Esc] to Cancel\n" );
					selection = getch();
					
					switch( selection )
					{
						case 27:	// Ascii Value of Esc key is 27
							break;
						default:
							goto DECRYPTION_DATA_ACCURATE;
					}
			}
			break;
		case '2':
			DECRYPTION_TEXT_ENTRY:
			
			// Clearing Variables
			for( int i = 0; i < 200; i++ )
			{
				input[i] = '\0';
				output[i] = '\0';
			}
			
			show_heading( 0 );
			show_mode( 'd', 0 );
			
			typeout( paragraph( "Enter the Message to be Decrypted:\n" ), 't', 1000 );
			console_cursor( 1 );
			cin.getline( input, 200 );	// Getting the message to be encrypted
			console_cursor( 0 );
			cout << endl;
			
			if( strlen( input ) == 0 )	// If the input is empty
			{
				cout << paragraph( "Invalid Input!\nInput cannot be Empty!\nPress any key to retry\n[Esc] Key to Cancel" );
				selection = getch();
				
				switch( selection )
				{
					case 27:	// Ascii value of Esc Key is 27
						break;
					default:
						cout << endl << endl;
						goto DECRYPTION_TEXT_ENTRY;
						break;
				}
			}
			
			DECRYPTION_TEXT_PASSWORD:
			for( int i = 0; i < 100; i++ )
			{
				password[i] = '\0';	// Clearing variable password
			}
			
			
			if(! strlen( config.get_last_pass() ) == 0 )
			{
				typeout( paragraph( "Use the previous Password? [y/*]: "), 't', 1000 );
				console_cursor( 1 );
				selection = getch();
				cout << selection << endl << endl;
				console_cursor( 0 );
				
				switch( selection )
				{
					case 'y':
						strcpy( password, config.get_last_pass() );
						break;
					default:
						typeout( paragraph( "Enter Password for Decryption: "), 't', 1000 );
						pass_entry( password, '*', 12);	// Getting password for encrypting file
						cout << endl;
						break;
				}
			}
			else
			{
				typeout( paragraph( "Enter Password for Decryption: "), 't', 1000 );
				pass_entry( password, '*', 12);	// Getting password for encrypting file
				cout << endl;
			}
			
			if( strlen( password ) == 0 || password[0] == ' ' )	// If the password is empty or has a space in the beginning
			{
				cout << paragraph( "Invalid Password!\nPress any key to retry\n[Esc] Key to Cancel" );
				selection = getch();
				
				switch( selection )
				{
					case 27:	// Ascii value of Esc Key is 27
						break;
					default:
						cout << endl << endl;
						goto DECRYPTION_TEXT_PASSWORD;
				}
				
				break;
			}
			
			config.save_pass( password );
			
			working_animation();
			strcpy( output, decrypt( input, password ) );
			
			// Display the output
			cout << paragraph( "\nENIGMA:\n\t" );
			typeout( paragraph( output ), 't', 1000 * ( strlen( output ) / 3) );
			cout << endl <<endl;
			
			
			DECRYPTION_OUT_SAVE:
			cout << paragraph( "Do you want to save the output?\n[y/n]: ");	// Save the decrypted output to a file
			selection = getch();
			cout << selection << endl << endl;
			
			switch( selection )
			{
				case 'y':
					char out_loc[200];
					
					show_heading( 0 );	// Clear Screen after selection
					show_mode( 'd', 0 );
					
					// Display the output
					cout << paragraph( "ENIGMA:\n\t" );
					cout << paragraph( output );
					cout << endl <<endl;
					
					typeout( ":: Select FOLDER to save output ::\n\n", 't', 2000 );
					strcpy( out_loc, select_file( "", 2) );	// Getting the output location
					if( strlen( out_loc ) == 0 )	// In the case user cancels
					{
						return;
					}
					// Adding File Name to the location
					app_string( out_loc, "/EnigmaOut.txt" );
					
					show_heading( 0 );
					show_mode( 'd', 0 );
					
					// Display the output
					cout << paragraph( "ENIGMA:\n\t" );
					cout << paragraph( output );
					cout << endl <<endl;
					
					cout << paragraph( "Saving the Output to:\n" );
					cout << paragraph( out_loc );
					cout << endl << endl;
					
					fout.open( out_loc, ios::out | ios::app );
					
					// Writing output to the file
					fout.write( input, strlen( input ) );
					fout << ": ";
					fout.write( output, strlen( output ) - 1 );	// Skipping the '\n' attatched to the output
					fout << " [ PASS: ";
					fout.write( password, strlen( password ) );
					fout << "]\n";
					
					fout.close();
					
					// Small Animation for finishing
					for( int i = 0; i < screen_len() - 4; i++ )
					{
						cout<<".";
						Sleep(25);
					}
					typeout( "...", 'i', 500 );
					cout << endl;
					
					cout << paragraph( "Output Saved\n\n" );
					cout << paragraph( "Press any key to continue to Main Menu OR press r to decrypt again\n" );	// Encrypt another message
					selection = getch();
					
					switch( selection )
					{
						case 'r':
							goto DECRYPTION_TEXT_ENTRY;
							break;
						default:
							break;
					}
					break;
				case 'n':
					cout << paragraph( "Press any key to continue to Main Menu OR press r to decrypt again\n" );	// Encrypt another message
					selection = getch();
					
					switch( selection )
					{
						case 'r':
							goto DECRYPTION_TEXT_ENTRY;
							break;
						default:
							break;
					}
					break;
					break;
				default:
					cout << paragraph( " Invalid Selection!\nPress any key to Retry\n" );
					getch();
					
					cout << endl;
					goto DECRYPTION_OUT_SAVE;
			}
			
			break;
		case 'c':
			break;
		default:
			cout << paragraph( " Invalid Selection!\nPress any key to Retry\n[Esc] to Cancel\n" );
			selection = getch();
			
			switch( selection )
			{
				case 27:	// Ascii Value of Esc key is 27
					break;
				default:
					goto DECRYPTION_TYPE;
			}
			break;
	}
	
	return;
}

void advanced()
{
	show_heading( 0 );
	show_mode( 'a', 1 );
	
	ADVANCED_MENU:
	
	show_heading( 0 );
	show_mode( 'a', 0 );
	
	// Choose an advanced option
	cout << paragraph( "1. See the source code\nc. Cancel\n::" );
	console_cursor( 1 );
	selection = getch();
	cout << selection << endl << endl;
	console_cursor( 0 );
	
	switch( selection )
	{
		case 13:	// 13: Enter Key
			goto ADVANCED_MENU;
			break;
		case '1':
			cout << paragraph( "Generating the C++ file in the current Directory\n\n" );
			
			// Small Animation for finishing
			for( int i = 0; i < screen_len() - 4; i++ )
			{
				cout<<".";
				Sleep(25);
			}
			typeout( "...", 'i', 500 );
			cout << endl;
			
			create_file( 1 );
			
			cout << paragraph( "Press any key to head to Main Menu\n");
			getch();
			break;
		case 'c':
			break;
		default:
			cout << paragraph( " Invalid Selection!\nPress any key to Retry\n[Esc] to Cancel\n" );
			selection = getch();
			
			switch( selection )
			{
				case 27:	// Ascii Value of Esc key is 27
					break;
				default:
					goto ADVANCED_MENU;
			}
			break;
	}
	return;
}

void help()
{
	
}


char* out_file_name(char* input_file)
{
	char out_file[200];	// Temporary location to store the output of the function
	for( int i = 0; i < 200; i++ )
	{
		out_file[i] = '\0';	// Clearing the variable out_file
	}
	
	char file_extension[10];	// Temporary location to store the extension of the input file
	for( int i = 0; i < 10; i++ )
	{
		file_extension[i] = '\0';	// Clearing the variable file_extension
	}
	
	char in_file[200];	// Temporary location to store the input file
	for( int i = 0; i < 200; i++)
	{
		in_file[i] = '\0';	// Clearing the variable in_file
	}
	strcpy( in_file, input_file );	// Original Variable must not be changed
	
	for( int i = strlen( in_file ) - 1; i >= 0; i--)	// Check from the last of the file
	{
		if( in_file[i] == '/' )
		{
			for( int j = 0; j <= i; j++ )	// Run loop till it reaches '/'
			{
				in_file[j] = '\0';	// Clearing everything before the file name
			}
			
			i++;	// Move to the file name
			for(count = 0 ; in_file[i] != '\0'; count++, i++ )
			{
				in_file[count] = in_file[i];	// copy the file name to the beginning of the variable
			}
			count++;	// Moving to 1 letter after the file name
			for(; count < 200; count++)
			{
				in_file[count] = '\0';	// Everything after the file name must be removed
			}
			
			break;
		}
	}
	
	int f_len = strlen( in_file );
	for( int i = f_len - 1; i >= 0; i--)	// Check from the last of the string
	{
		if( in_file[i] == '.')
		{
			for(int j = 0; i < f_len; i++, j++)
			{
				file_extension[j] = in_file[i];	// Copying the ending (extension) of the input file to file_extension
				in_file[i] = '\0';
			}
			
			break;
		}
	}
	
	// format of file name: [input_file_name]_EnigmaOut.[Extension]
	app_string( out_file, in_file );
	app_string( out_file, "_EnigmaOut" );
	app_string( out_file, file_extension );
	
	return out_file;
}


void working_animation()
{
	console_cursor( 0 );
	// First output a small animation
	cout << "[ | ] ENIGMA ";	
	typeout( ". . .", 't', 3000 );
	
	cout << '\r' << "[ | ] READY " << " ...  ";
	Sleep( 600 );
	cout << '\r' << "[ | ] READY " << "  .   ";
	Sleep( 600 );
	
	// List of all messages will be shown along side a rotating bar
	char messages[][30] = {"[ | ] Caesar Cipher", "[ | ] Layering", "[ | ] Scrambling"};
	
	for( int k = 0; k < sizeof( messages ) / ( 30 * sizeof( char ) ); k++ )	// Get number of elements on the list and acc. to it, run the loop
	{
		cout << '\r' << "                         ";	// Blank out the output line
		cout << '\r' << messages[k];
		gotoXY( 0, getY(), 0 );
		cout << "[ ";
		for( int i = 1; i < 161; i++ )	// Change shape acc. to position in loop run
		{
			switch( i % 4 )
			{
				case 0:
					cout << "|";
					break;
				case 1:
					cout << "/";
					break;
				case 2:
					cout << "-";
					break;
				case 3:
					cout << "\\";
					break;
			}
			
			gotoXY( strlen( messages[k] ) - 2, 0, 1 );	// goto a point just forward the message (for neatness)
			Sleep( 10 );
			gotoXY( -strlen( messages[k] ) + 2 - 1, 0, 1 );	// go one point behind the original to make output on the same place
		}
	}
	
	cout << '\r' << "                      ";
	cout << '\r' << "[ X ] DONE!" << endl;
	Sleep( 800 );
	
	return;
}

void exit_animation()
{
	center_align( end_msg );
	
	console_cursor( 1 );
	
	for( int i = 0; i < strlen( end_msg ); i++ )	// Typeout the end_msg at an incresing rate
	{
		cout << end_msg[i];
		Sleep( 50 * ( strlen( end_msg ) - i ) ) ;	// Rate is dependent on the current position
	}
	cout << endl << endl;
	
	console_cursor( 0 );
	Sleep( 1000 );
	
	COORD pos;	// To save current coordinates
	pos.Y = getY();
	
	int m_side = 0;	// To store the length / breadth / side of the matrix being formed
	m_side = pow( strlen( matrix_msg ), 0.5 );	// side * side = length of the message
	
	char matrix[m_side][m_side + 1];	// 1 extra tu store termination '\0'
	for( int i = 0; i < m_side; i++ )
	{
		for( int j = 0; j < m_side + 1; j++ )
		{
			matrix[i][j] = matrix_msg[ ( m_side * i ) + j ];	// add the line index (multiplied by the number of elements in a line) to the position to get the position in matrix_msg
		}
	}
	
	for( int i = 1; i <= 26 * 3; i++ )
	{
		gotoXY( 0, pos.Y, 0 );	// go to the (0, original_line)
		
		int shift = i % 26;	// shift must be between 0 and 25
		
		for( int j = 0; j < m_side; j++ )
		{
			center_align( ( 2 * m_side ) + 1 );	// Center align the matrix (after adding the gaps in the middle)
			for( int k = 0; k < m_side; k++ )
			{
				if( matrix[j][k] + shift - 'A' < 26 )
				{
					cout << (char)( matrix[j][k] + shift ) << "  ";	// the letter remains between A and Z after adding the shift to it. Also adds a gap
				}
				else
				{
					cout << (char)( matrix[j][k] + shift - 26 ) << "  ";	// the letter goes beyond Z after adding the shift to it. So the cycle is restarted from A. Also adds a gap
				}
			}
			cout << endl << endl;
		}
		
		Sleep( 50 );
	}
	
	for( int i = 0; i < 3; i++ )
	{
		gotoXY( 0, pos.Y, 0 );	// goto the initial position
		for( int j = 0; j < m_side; j++ )
		{
			center_align( ( 2 * m_side ) + 1 );	// Center align the matrix again
			for( int k = 0; k < m_side; k++ )
			{
				cout << " " << "  ";	// Clear out the output
			}
			cout << endl << endl;
		}
		gotoXY( 0, pos.Y, 0 );
		
		Sleep( 150 );
		
		for( int j = 0; j < m_side; j++ )
		{
			center_align( ( 2 * m_side ) + 1 );
			for( int k = 0; k < m_side; k++ )
			{
				cout << (char)( matrix[j][k] ) << "  ";	// Reprint the output
			}
			cout << endl << endl;
		}
		
		Sleep( 300 );	// A small wait...gives an effect of Blinking
	}
	Sleep( 3000 );
	
	exit( 0 );
}

// DEVELOPER FUNCTIONS

void developer()
{
	fstream check;	// To check if files get created successfully or not
	
	show_heading( 0 );
	show_mode( 'v', 1 );
	
	if( strlen( config.get_last_UID() ) == 0 )	// If a successful UID has not been awarded (thus save is empty)
	{
		if(! confirm_UID() )	// Check if the UID confirms or not
		{
			return;
		}
		else
		{
			config.save_UID( UID_Gen() );	// If it does, save it and continue
		}
	}
	
	
	
	DEVELOPER_MENU:
	
	// Clear Screen but retain titles (no animation)
	show_heading( 0 );
	show_mode( 'v', 0 );
	
	cout << paragraph( "1. Create C++ File\nc. Cancel\n::" );
	console_cursor( 1 );
	selection = getch();
	cout << selection << endl << endl;
	console_cursor( 0 );
	
	switch( selection )
	{
		case 13:	// 13: Enter Key
			goto DEVELOPER_MENU;
			break;
		case '1':
			cout << paragraph( "Generating the C++ file in the current Directory\n\n" );
			create_file( 2 );
			
			cout << paragraph( "Press any key to back to Developer Menu\n");
			getch();
			goto DEVELOPER_MENU;
			
			break;
		case 'c':
			break;
		default:
			cout << paragraph( " Invalid Selection!\nPress any key to Retry\n[Esc] to Cancel\n" );
			selection = getch();
			
			switch( selection )
			{
				case 27:	// Ascii Value of Esc key is 27
					break;
				default:
					goto DEVELOPER_MENU;
					break;
			}
			break;
	}
	
	return;
}

void create_file(int index)
/*
index:
	1: Enigma-User.cpp
	2: Enimga-Dev.cpp
*/
{
	system( "@echo off" );
	switch( index )
	{
		case 1:
			system( "attrib Files\\bin -h -s >nul 2>nul" );	// Clearing hidden from folder
			system( "attrib Files\\bin\\\"Enigma-User.cpp\" -h -s >nul 2>nul" );	// Clearing hidden from file
			system( "copy Files\\bin\\\"Enigma-User.cpp\" \"./\" >nul 2>nul" );	// Copying file to current directory
			break;
		case 2:
			system( "attrib Files\\bin -h -s >nul 2>nul" );	// Clearing hidden from folder
			system( "attrib Files\\bin\\\"Enigma-Dev.cpp\" -h -s >nul 2>nul" );	// Clearing hidden from file
			system( "copy Files\\bin\\\"Enigma-Dev.cpp\" \"./\" >nul 2>nul" );	// Copying file to current directory
			break;
	}
	
	switch( index )
	{
		case 1:
			system( "attrib Files\\bin\\\"Enigma-User.cpp\" +h +s >nul 2>nul" );	// Rehiding original file
			system( "attrib Files\\bin +h +s >nul 2>nul" );	// Rehiding original folder
			break;
		case 2:
			system( "attrib Files\\bin\\\"Enigma-Dev.cpp\" +h +s >nul 2>nul" );	// Rehiding original file
			system( "attrib Files\\bin +h +s >nul 2>nul" );	// Rehiding original folder
			break;
	}
	
	fstream check;	// To check if the desired file has been created or not
	switch( index )
	{
		case 1:
			check.open( "Enigma-User.cpp", ios::in );	// Checking if the file was created or not
			if( check )
			{
				typeout( paragraph( "File generated successfully!!"), 't', 2000 );
				Sleep( 250 );
				cout << endl;
				cout << paragraph( "The source code of the program has been kept open. But the options and functioning of Developer mode and Advanced mode are locked. This is to ensure that the certain features cannot be overidden. In case you change the code and it no longer compiles, you will have to download the program again. Use this option at your own risk.\n");
				cout << endl;
			}
			else
			{
				cout << endl << endl;
				cout << paragraph( "!!! UNEXPECTED ERROR !!!\n");
				cout << paragraph( "The program was unable to generate the C++ File. The program relies on the integrity of configuration files in Files folder. If you have partially deleted or moved the Files folder, then please extract the program again and DO NOT MANUALLY EDIT ANY OBJECT PRESENT IN THE FILES FOLDER!" );
				cout << endl << endl;
			}
			check.close();
			break;
		case 2:
			check.open( "Enigma-Dev.cpp", ios::in );
			if( check )
			{
				cout << paragraph( "File created successfuly\n\n" );
			}
			else
			{
				cout << endl;
				cout << paragraph( "File creation failed\nPossible reason of error: bin folder edited\n\n" );
			}
			check.close();
			break;
	}
	
	return;
}

int confirm_UID()
{
	COORD pos;	// to hold current position
	pos.X = getX();
	pos.Y = getY();
	
	UID_ATTEMPT:
	
	while( getY() != pos.Y )	// Till the cursor doesnt reach the first line of output
	{
		for( int i = 0; i < screen_len() - 1; i++ )
		{
			cout << " ";	// Clearing the whole line
		}
		
		gotoXY( 0, getY() - 1, 0 );	// Go one line back / up
	}
	
	cout << paragraph( "[   ] Enter the UID: " );
	for( int i = 0; i < 10; i++ )
	{
		cout << " ";	// Clear any previous attempt being shown on the screen
	}
	gotoXY( -10, 0, 1 );	// go to the position of entry of UID
	pass_entry(UID, '*', 10 );
	
	gotoXY( 0, pos.Y, 0 );	// Go back to the beginning of the original line
	if( strcmp( UID, UID_Gen() ) == 0 )	// If UID correct
	{
		
		cout << "[ 1 ]";	// Show correct
		
		gotoXY( 0, pos.Y + 1, 0 );	// next line
		
		cout << paragraph( "Correct UID" );
		typeout( "...", 'i', 1000 );
		return 1;	// return true
	}
	else	// If UID is incorrect
	{
		cout << "[ X ]";	// Show wrong
		
		gotoXY(0, pos.Y + 1, 0 );	// next line
		
		cout << paragraph( "\nIncorrect UID\nThe UID can be generated via the DevKit (Developer only)\n\nPress any key to Retry\n[Esc] to Cancel\n" );
		selection = getch();
		
		switch( selection )
		{
			case 27:	// Ascii Value of Esc key is 27
				return 0;	// return false
				break;
			default:
				goto UID_ATTEMPT;	// retry
				break;
		}
	}
}
