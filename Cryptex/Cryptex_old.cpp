#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <robot.h>
using namespace std;


int type=2;
/*
	0: User
	1: Bundle
	2: Developer
	
*/

char ver[4]={"8.4"};

void get_location(char[]);
void Animation(int);
void Get_Pass(char*);
void write_header(char*);
void write_header_instructions(void);
void write_help(void);
void write_changelog(void);
char* compiler_search(int);

int main()
{
	char c, line[500], input[100], output[100], part[100], wordlist[100], PassKey[10000], location[100];
	int m=0;
	strcpy(input, "./");
	strcpy(output, "./");
	strcpy(wordlist, "./");
		
	//Select Type of Operation
	Selection:
	{
		cout<<"CRYPTEX HAS NOW BEEN REPLACED BY ENIGMA\nNo further development of cryptex by the the dev\n!! CURRENT VERSION MAY ALSO SHOW BUGS !!\n\n\n";
		cout<<"\t"<<"<<-----------------CRYPTEX----------------->>"<<endl<<"[Version "<<ver<<"]"<<endl<<endl;
		cout<<"1: Encrypt a file"<<endl;
		cout<<"2: Decrypt a file"<<endl;
		cout<<"3: Create Help (recommended)"<<endl;
		if(type==2)
		{
			cout<<"4: Create Changelog"<<endl;
		}
		c=getch();
		cout<<endl;
		system("cls");
		cout<<"\t"<<"<<-----------------CRYPTEX----------------->>"<<endl<<"[Version "<<ver<<"]"<<endl<<endl;
		if(c=='1')
		{
			cout<<"Encyption Mode"<<endl<<endl;
		}
		else
		{
			if(c=='2')
			{
				Selection_Decrypt:
					cout<<"Decryption Mode"<<endl<<endl;
					cout<<"Do you know the Password? (y/n):";
					c=getch();
					if(!(c=='y'||c=='Y'||c=='n'||c=='N'))
					{
						cout<<endl<<"Invalid Selection!"<<endl
							<<"Press any key to retry";
						getch();
						system("cls");
						cout<<"\t"<<"<<-----------------CRYPTEX----------------->>"<<endl<<"[Version "<<ver<<"]"<<endl<<endl;
						goto Selection_Decrypt;
					}
					if(c=='y'||c=='Y')
					{
						cout<<" "<<"Y"<<endl;
					}
					else
					{
						if(c=='n'||c=='N')
						{
							cout<<" "<<"N"<<endl;
						}
					}
			}
			else
			{
					if(c=='4'&&type==2)
					{
						cout<<"Writing the changelog"<<endl;
						write_changelog();
						cout<<endl<<endl<<"Thanks for using Cryptex"<<endl<<"--Mr. Robot";
						Animation(5500);
						exit(0);
					}
					else
					{
						if(c=='3')
						{
							cout<<"Writing Help"<<endl;
							write_help();
							cout<<endl<<endl<<"Thanks for using Cryptex"<<endl<<"--Mr. Robot";
							Animation(5500);
							exit(0);
						}
						Invalid:
							cout<<"Invalid Selection!"<<endl
								<<"Press any key to retry";
							getch();
							system("cls");
							goto Selection;
					}
				
			}
		}
	}
	
	
	inputfile:
		cout<<"Please Select the input file: "<<endl;
		strcpy(input, select_file(input, 1));
		cout<<endl<<"Input File: "<<input<<endl<<endl;
	
	outputfile:
		cout<<"Please Select the output file: "<<endl;
		strcpy(output, select_file(output, 1));
		cout<<endl<<"Output File: "<<output<<endl<<endl;
	
	if(c=='1')
	{
		Get_Pass(PassKey);
		encrypt(input, output, PassKey);
		cout<<endl<<endl<<"Encryption Complete";
	}
	else
	{
		if(c=='y'||c=='Y')
		{
			Get_Pass(PassKey);
			decrypt(input, output, PassKey);
			cout<<endl<<endl<<"Decryption Complete";
		}
		else
		{
			if(c=='n'||c=='N')
			{
				cout<<endl<<"The Program will now try to Bruteforce the password"<<endl;
				cout<<"\t Note that it requires:"<<endl;
				cout<<"\t\tA Wordlist of passwords to try"<<endl;
				cout<<"\t\tThe Input File must have some common English words"<<endl;
				cout<<"\t\tYou must know some words or phrases present in the file (OPTIONAL)"<<endl<<endl;
				cout<<"This method might not always work!!"<<endl<<endl;
				cout<<"Please Select the Wordlist file: "<<endl;
				strcpy(wordlist, select_file(wordlist, 1));
				cout<<endl<<"Wordlist file: "<<wordlist<<endl<<endl;
				
				Partials:
				cout<<"Please enter the word(s) that are present in the file"<<endl;
				cout<<"[Leave blank if unknown]: "<<endl;
				cout<<"Please seperate the words with a ';' character: "<<endl<<endl;
				cout<<"\t";
				cin.ignore();
				gets(part);
				strcpy(PassKey, decrypt_brute(input, wordlist, part));
				if(strcmp(PassKey, "!")==0)
				{
					cout<<"Decryption Failed!"<<endl;
					cout<<"Try with another wordlist"<<endl;
				}
				else
				{
					if(strcmp(PassKey, "#")==0)
					{
						cout<<"The Minimum length of a word must be 4";
						cout<<endl<<"Please Re-enter";
						cout<<endl<<endl;
						goto Partials;
					}
					else
					{
						cout<<endl<<endl<<"Workable PassKey found: "<<PassKey<<endl<<endl;
						Sleep(2000);
						decrypt(input, output, PassKey);
						cout<<"Please check the output file"<<endl;
						cout<<"If the result is not as expected, try making the above key a comment in the wordlist"<<endl;
						cout<<"Achieve this by adding \"//\" before the key"<<endl<<endl;
						cout<<"Decryption Complete"<<endl;
						cout<<endl<<endl<<"Thanks for using Cryptex"<<endl<<"--Mr. Robot";
						Animation(16500);
						return 0;
					}
				}
			}
		}
	}
	
	cout<<endl<<endl<<"Thanks for using Cryptex"<<endl<<"--Mr. Robot";
	Animation(5500);
	
	return 0;
}

void Animation(int time)
{
	int t=0;
	t=time/11;
	cout<<endl;
	cout<<"\r\t\t\t..... 5 .....";
	Sleep(2*t);
	cout<<"\r                                            ";
	cout<<"\r\t\t\t .... 4 ....";
	Sleep(2*t);
	cout<<"\r                                            ";
	cout<<"\r\t\t\t  ... 3 ...";
	Sleep(2*t);
	cout<<"\r                                            ";
	cout<<"\r\t\t\t   .. 2 ..";
	Sleep(2*t);
	cout<<"\r                                            ";
	cout<<"\r\t\t\t    . 1 .";
	Sleep(2*t);
	cout<<"\r                                            ";
	cout<<"\r\t\t\t      0";
	Sleep(t);
	cout<<endl<<endl;
	
	return;
}

void Get_Pass(char* PassKey)
{
	char pass[100];
	
	fstream fin;
	
	for(int i=0; i<100; i++)
	{
		pass[i]='\0';
	}
	
	strcpy(pass, "./");
	
	int v=0;
	cout<<"Enter the PassKey(Leave blank to select password file): "<<endl;
	v=pass_entry(PassKey, '*', 100);
	if(v==0)
	{
		strcpy(pass, select_file(pass, 1));
		cout<<endl<<"Pass File: "<<pass<<endl<<endl;
		fin.open(pass, ios::in);
		fin.seekg(0, ios::end);
		if((!fin)||(fin.tellg()==0))
		{
			cout<<"The specified file is empty!"<<endl;
			pass_entry(PassKey, '*', 100);
		}
		else
		{
			fin.clear();
			fin.seekg(0, ios::beg);
			int m=0;
			while(fin.getline(line, 500))
			{
				int i=0;
				while(i<strlen(line))
				{
					PassKey[m]=line[i];
					m++;
					i++;
				}
			}
		}
		fin.close();
	}
	
	
	return;
}



void write_help()
{
	fstream fout;
	fout.open("help.txt", ios::out | ios::trunc);
	
fout<<"<<<----------Cryptex---------->>>"<<endl;
fout<<""<<endl;
fout<<"Cryptex is an encryption program. This is the Help for Cryptex. This file can be created anytime from within the program"<<endl;
fout<<""<<endl;
fout<<"Encrypt:"<<endl;
fout<<"	The program must be provided an input in the form of a *.txt file"<<endl;
fout<<"	The user must also select an output file of the same format"<<endl;
fout<<"	The user can choose to manually enter the password or use a complex encryption key by selecting another file"<<endl;
fout<<"	An Encrypted file is produced in the selcted output file"<<endl;
fout<<""<<endl;
fout<<"Decrypt:"<<endl;
fout<<"	Decryption with Crpytex has 2 option:"<<endl;
fout<<"		(1) Normal Decryption"<<endl;
fout<<"		(2) Recovery Mode"<<endl;
fout<<"	Normal Decryption:"<<endl;
fout<<"		In this mode, the user must select the input and output file and mention the key as before"<<endl;
fout<<"		A Decrypted file is produced in the selected output file"<<endl;
fout<<"	Recovery Mode:"<<endl;
fout<<"		In case the user forgets his/her passkey, cryptex offers a recovery mode"<<endl;
fout<<"		The user must select an input and output file as before"<<endl;
fout<<"		Instead of telling the passkey, the user must now select a wordlist file (*.txt)"<<endl;
fout<<"			A wordlist file is a long list a passwords which the program will try as passwords"<<endl;
fout<<"		Optionally, if the user remembers some content of the file"<<endl;
fout<<"			He/She can provide phrases or words present in the file"<<endl;
fout<<"		This shall improve the accuracy of the Recovery Mode"<<endl;
fout<<"		Recovery Mode doesn\'t always work"<<endl;
fout<<"			It is advised to always save the output of Recovery Mode in a seperate location"<<endl;
fout<<"		If the Recovery Mode does find out a workable passkey, it is shown to the user"<<endl;
fout<<"			The output after the decryption with the said key is also saved"<<endl;
fout<<"		If the output is unexpected or wrong"<<endl;
fout<<"			Try making the wrong password a comment in the wordlist"<<endl;
fout<<"				Achieve this by adding \"//\" before the key"<<endl;
fout<<"			You could also mention words present in the file to improve the accuracy"<<endl;
fout<<""<<endl;
fout<<"There are three versions of the program at any time:"<<endl;
fout<<"	Developer"<<endl;
fout<<"	Bundle"<<endl;
fout<<"	User"<<endl;
fout<<"Developer:"<<endl;
fout<<"	This version has new features which are currently in the development phase"<<endl;
fout<<"	A lot of bugs may be present"<<endl;
fout<<"	The program includes extra features for developers:"<<endl;
fout<<"		Creating a Header File which include all functions being used in Cryptex"<<endl;
fout<<"		The C++ File of Cryptex"<<endl;
fout<<"		The changelog explaining all workings and changes of the program"<<endl;
fout<<"		Pre-filled input, output, passkey and wordlist file in a convinient location"<<endl;
fout<<"		Addons (Ascii-Convertor, File Output Code Writer)"<<endl;
fout<<"Bundle:"<<endl;
fout<<"	This is a stable version of the program"<<endl;
fout<<"	The program includes extra features for programmers:"<<endl;
fout<<"		Creating a Header File which include all functions being used in Cryptex"<<endl;
fout<<"		Pre-filled input, output, passkey and wordlist file in a convinient location"<<endl;
fout<<"		Addons (Ascii-Convertor, File Output Code Writer)"<<endl;
fout<<"User:"<<endl;
fout<<"	The stable version of the program with no extra addons"<<endl;
fout<<"	Meant to be used for encryption and decryption be an average user"<<endl;
fout<<""<<endl;
fout<<"Best attempt have been made to ensure that the program is bug free"<<endl;
fout<<"If any complaints or suggestions please mail me at:"<<endl;
fout<<"	th_rpr911@protonmail.com"<<endl;
fout<<""<<endl;
fout<<""<<endl;
fout<<""<<endl;
fout<<"<<<----------MrRobot---------->>>"<<endl;











	fout.close();
	
	return;
}

void write_changelog(void)
{
	fstream fout;
	fout.open("changelog.txt", ios::out | ios::trunc);
	
fout<<"<<<----------Cryptex---------->>>"<<endl;
fout<<""<<endl;
fout<<"// Cryptex is no longer attatched to the header file \"cryptex.h\"/\"robot.h\" //"<<endl;
fout<<"// All relevant Details about the header files are shifted to its own changelog //"<<endl;
fout<<"Ver 1:"<<endl;
fout<<"	[orignal]:"<<endl;
fout<<"		<> The Program will take the input from the file \"input.txt\""<<endl;
fout<<"		<> The output will be stored in \"output.txt\""<<endl;
fout<<"		<> Input a number for ceaser cipher"<<endl;
fout<<"			:: Add the number to each character"<<endl;
fout<<"			:: Adding 4 to \'c\' makes it \'g\'"<<endl;
fout<<"		<> Input a word for encryption"<<endl;
fout<<"			::Input-->hunger"<<endl;
fout<<"				# a-->h"<<endl;
fout<<"				# b-->u"<<endl;
fout<<"				# c-->n"<<endl;
fout<<"				# d-->g"<<endl;
fout<<"				# e-->e"<<endl;
fout<<"				# f-->r"<<endl;
fout<<"				# g-->a"<<endl;
fout<<"				# h-->b"<<endl;
fout<<"				# i-->c"<<endl;
fout<<"				# j-->d"<<endl;
fout<<"				# k-->f"<<endl;
fout<<"				# l-->i"<<endl;
fout<<"				# m-->j"<<endl;
fout<<"				# n-->k"<<endl;
fout<<"				# o-->l"<<endl;
fout<<"				# p-->m"<<endl;
fout<<"				# q-->o"<<endl;
fout<<"				# r-->p"<<endl;
fout<<"				# s-->q"<<endl;
fout<<"				# t-->s"<<endl;
fout<<"				# u-->t"<<endl;
fout<<"				# v-->v"<<endl;
fout<<"				# w-->w"<<endl;
fout<<"				# x-->x"<<endl;
fout<<"				# y-->y"<<endl;
fout<<"				# z-->z"<<endl;
fout<<"		<> The shift is stored in \"Info/c_shift.txt\""<<endl;
fout<<"		<> The output after the shift is stored in \"Info/input_c.txt\""<<endl;
fout<<"		<> The Word for the encrytion is stored in \"Info/PassKey.txt\""<<endl;
fout<<""<<endl;
fout<<"Ver 1.1:"<<endl;
fout<<"	[Improved Functions]:"<<endl;
fout<<"		<> Fixed problem in Caeser Cipher"<<endl;
fout<<"			:: When sum of char and shift is greater than 26, the shifted char goes back to beginning"<<endl;
fout<<"				# t+10=d"<<endl;
fout<<"		<> The input PassKey is turned completely to lower characters"<<endl;
fout<<"		<> The PassKey can now input words with repeated letters"<<endl;
fout<<"			:: The repeated letter is just ignored"<<endl;
fout<<"			:: \"HHHeello\"-->\"helo\""<<endl;
fout<<"ver 2.0:"<<endl;
fout<<"	[Greater range of input]:"<<endl;
fout<<"		<> Added Uppercase character to Input File"<<endl;
fout<<"			:: Caeser Cipher will now work with Uppercase characters"<<endl;
fout<<"		<> Program can now input larger files"<<endl;
fout<<"ver 2.1:"<<endl;
fout<<"	[Greater range of input]:"<<endl;
fout<<"		<> Adding Uppercase character to Input File (improved)"<<endl;
fout<<"			:: Encrytion will now work with Uppercase characters"<<endl;
fout<<"			:: Input --> HUNGER/hunger/HuNgeR"<<endl;
fout<<"				# a-->h"<<endl;
fout<<"				# b-->u"<<endl;
fout<<"				# c-->n"<<endl;
fout<<"				# d-->g"<<endl;
fout<<"				# e-->e"<<endl;
fout<<"				# f-->r"<<endl;
fout<<"				# g-->a"<<endl;
fout<<"				# h-->b"<<endl;
fout<<"				# i-->c"<<endl;
fout<<"				# j-->d"<<endl;
fout<<"				# k-->f"<<endl;
fout<<"				# l-->i"<<endl;
fout<<"				# m-->j"<<endl;
fout<<"				# n-->k"<<endl;
fout<<"				# o-->l"<<endl;
fout<<"				# p-->m"<<endl;
fout<<"				# q-->o"<<endl;
fout<<"				# r-->p"<<endl;
fout<<"				# s-->q"<<endl;
fout<<"				# t-->s"<<endl;
fout<<"				# u-->t"<<endl;
fout<<"				# v-->v"<<endl;
fout<<"				# w-->w"<<endl;
fout<<"				# x-->x"<<endl;
fout<<"				# y-->y"<<endl;
fout<<"				# z-->z"<<endl;
fout<<""<<endl;
fout<<"				# A-->H"<<endl;
fout<<"				# B-->U"<<endl;
fout<<"				# c-->N"<<endl;
fout<<"				# D-->G"<<endl;
fout<<"				# E-->E"<<endl;
fout<<"				# F-->R"<<endl;
fout<<"				# G-->A"<<endl;
fout<<"				# H-->B"<<endl;
fout<<"				# I-->C"<<endl;
fout<<"				# J-->D"<<endl;
fout<<"				# K-->F"<<endl;
fout<<"				# L-->I"<<endl;
fout<<"				# M-->J"<<endl;
fout<<"				# N-->K"<<endl;
fout<<"				# O-->L"<<endl;
fout<<"				# P-->M"<<endl;
fout<<"				# Q-->O"<<endl;
fout<<"				# R-->P"<<endl;
fout<<"				# S-->Q"<<endl;
fout<<"				# T-->S"<<endl;
fout<<"				# U-->Y"<<endl;
fout<<"				# V-->V"<<endl;
fout<<"				# W-->W"<<endl;
fout<<"				# X-->X"<<endl;
fout<<"				# Y-->Y"<<endl;
fout<<"				# Z-->Z"<<endl;
fout<<"Ver 2.2:"<<endl;
fout<<"	[Fixes Bug]:"<<endl;
fout<<"		<> Due to bug in algorithm, 2 characters could be attached with the same input"<<endl;
fout<<"			:: Due to countinous running of loop even after encryting/replacing character"<<endl;
fout<<"			:: Fixed by breaking loop (look for Ver 2.2 comment in Program if curious)"<<endl;
fout<<"Ver 2.3:"<<endl;
fout<<"	[Error Handling]:"<<endl;
fout<<"		<> Added constraints on input to ensure functionality"<<endl;
fout<<"			:: User is now prompted on random/illeagal entries"<<endl;
fout<<"		<> Improved code to improve execution time"<<endl;
fout<<"		<> Added commments to simplify code"<<endl;
fout<<"Ver 2.4:"<<endl;
fout<<"	[Improved Functions]:"<<endl;
fout<<"		<> The PassKey can now input spaces"<<endl;
fout<<"			:: The spaces are just ignored"<<endl;
fout<<"				# I am Ted --> iamted/IAMTED"<<endl;
fout<<"		<> The program can now check for repeated characters and eliminate them even if they are not consecutive"<<endl;
fout<<"			:: Before"<<endl;
fout<<"				# I am Mr Robot --> iamrobot/IAMROBOT (notice while \'m\' & \'r\' get corrected, \'o\' doesn\'t"<<endl;
fout<<"			:: Now"<<endl;
fout<<"				# I am Mr Robot --> iamrobt/IAMROBT (\'m\', \'r\', and \'o\' all are corrected)"<<endl;
fout<<"		<> Added animation when program terminates"<<endl;
fout<<"			:: 5 sec countdown"<<endl;
fout<<"			:: ensures readability of messages when running directly from executable file"<<endl;
fout<<"ver 3:"<<endl;
fout<<"	[New Input Style]:"<<endl;
fout<<"		<> The program directly asks for a password"<<endl;
fout<<"			:: The Password is a mix of alphanumeric characters"<<endl;
fout<<"		<> Caeser Cipher"<<endl;
fout<<"			:: All the numbers provided in the password are added"<<endl;
fout<<"			:: The sum is divided by 26 to get remainder"<<endl;
fout<<"				# the shift is given a default value \'1\' if no number is specified or if remainder is 0"<<endl;
fout<<"			:: Remainder becomes shift in caeser cipher"<<endl;
fout<<"		<> Encryption"<<endl;
fout<<"			:: All numbers are also removed along with previous modification"<<endl;
fout<<"Ver 3.1:"<<endl;
fout<<"	[More Input chars]:"<<endl;
fout<<"		<> The PassKey can now also input symbols from across the ascii table"<<endl;
fout<<"			:: Numbers are utilised in caesar cipher"<<endl;
fout<<"			:: Alphabets are used in encrytion"<<endl;
fout<<"			:: All other symbols are ignored"<<endl;
fout<<"Ver 4:"<<endl;
fout<<"	[New Input Option]:"<<endl;
fout<<"		<> The Program can now input the PassKey from a file"<<endl;
fout<<"			:: The file must be saved as \"pass.txt\" in the same folder as \"input.txt\""<<endl;
fout<<"			:: If the file is not found, the program shall ask the user for the PassKey"<<endl;
fout<<"Ver 4.1:"<<endl;
fout<<"	[Bug Fix]:"<<endl;
fout<<"		<> The program now on finding the \"pass.txt\" to be empty shall ask the user for the password"<<endl;
fout<<"			:: Earlier the program would just skip the PassKey and only perform Caeser Cipher with default value \'1\'"<<endl;
fout<<"Ver 5.0:"<<endl;
fout<<"	[DeCryption]:"<<endl;
fout<<"		<> The Program can now also Decrypt files which have been encrypted with Cryptex"<<endl;
fout<<"			:: The input file show now be the previously encrypted file"<<endl;
fout<<"			:: You must have the same password to get the correct output"<<endl;
fout<<"		<> All previous functions and improvements are still present"<<endl;
fout<<""<<endl;
fout<<"Ver 6.0:"<<endl;
fout<<"	[Header File]:"<<endl;
fout<<"		<> The program now uses a header file"<<endl;
fout<<"		<> This header file can be created by the program itself ;-)"<<endl;
fout<<"		<> The Header File will allow the functions of cryptex to be used across different programs!!"<<endl;
fout<<"     		<> You can now input your own location of the input, output and the password file"<<endl;
fout<<"     			:: The locations can be relative as well as as absolute"<<endl;
fout<<"      			:: It must be specified as it is in HTML or while providing location to fstream command"<<endl;
fout<<"		<> PassWord input now shows \'*\' instead of character"<<endl;
fout<<"Ver 7.0:"<<endl;
fout<<"	[File Browsing]:"<<endl;
fout<<"		<> A function which allows users to browse through local files has been added to header file"<<endl;
fout<<"			:: The function essentially lets you select a file or a folder as per your requirements"<<endl;
fout<<"		<> You can now create the header file directly in INCLUDE folder"<<endl;
fout<<"		<> The program will also search for some known locations of INCLUDE folder"<<endl;
fout<<"			:: Currently supports only Dev C++"<<endl;
fout<<"			:: More compilers will be added soon"<<endl;
fout<<"Ver 7.1:"<<endl;
fout<<"	[Error Handling and Improvements]:"<<endl;
fout<<"		<> Error Handling making sure that the program doesnt crash suddenly"<<endl;
fout<<"		<> The File browsing function now inputs a number, telling it which type of files to display"<<endl;
fout<<"			:: Check out the HeaderFile_instructions"<<endl;
fout<<"Ver 8.0:"<<endl;
fout<<"	[BruteForce]:"<<endl;
fout<<"		<> The header file now has a function which tries to figure out the PassKey used for encryption"<<endl;
fout<<"			:: A wordlist file of possible passwords is provided"<<endl;
fout<<"				# The wordlist must contain the password or the function will fail"<<endl;
fout<<"			:: The program decrypts the input file using this password"<<endl;
fout<<"			:: The program then checks the file for some common english words"<<endl;
fout<<"				# \"a\" \"if\",\"of\",\"to\",\"at\",\"on\",\"in\",\"is\",\"no\",\"so\",\"ah\",\"do\",\"am\""<<endl;
fout<<"			:: if 1 single-lettered and 2 two-lettered words match, then the password is seen workable"<<endl;
fout<<"		<> There is a lot of possibilty of error"<<endl;
fout<<"			:: Two very similar passwords yield a similar output"<<endl;
fout<<"			:: If the program decrypts a file, and the result is not as expected"<<endl;
fout<<"				# add \"//\" before the failed passkey in the wordlist"<<endl;
fout<<"				# the program will now skip this passkey"<<endl;
fout<<"			:: !!!IMPORTANT!!!"<<endl;
fout<<"				# don\'t make the output file of the decryption (in brute mode) the same as the input"<<endl;
fout<<"					// this will make sure that even if the program fails, the data isnt lost"<<endl;
fout<<""<<endl;
fout<<"Ver 8.1:"<<endl;
fout<<"	[Improved Functions]:"<<endl;
fout<<"		<> Bruteforce function now can also input a string of words which the user knows are present in the original file"<<endl;
fout<<"			:: This will improve the accuracy the function"<<endl;
fout<<"			:: This value is optional"<<endl;
fout<<"				# Multiple words can also be provided"<<endl;
fout<<"					// Words should be seprated with a \';\' character"<<endl;
fout<<"				# words are not case sensitive"<<endl;
fout<<"		<> The bruteforce function now return the whole password array"<<endl;
fout<<"		<> The password entry function can now output any character in place of the input"<<endl;
fout<<"Ver 8.2:"<<endl;
fout<<"	[Better Encryption]:"<<endl;
fout<<"		<> Now numbers present in the input file are also encrypted"<<endl;
fout<<"			:: They just undergo Ceasar Cipher shift"<<endl;
fout<<"				# 1 + 8 = 9"<<endl;
fout<<"			:: If the sum goes greater than 9, the number series starts again from 0"<<endl;
fout<<"				# 1 + 9 = 0 {10%10=0}"<<endl;
fout<<"					// The default value of the shift is 1, so there will always be a minimum shift of 1"<<endl;
fout<<"		<> The different version (Dev, Bundle and User) are now mentioned while compliling the file"<<endl;
fout<<"			:: This ensures that only select features are availabe to the users"<<endl;
fout<<"Ver 8.3:"<<endl;
fout<<"	[Password Function improved]:"<<endl;
fout<<"		<> bug fixed in pass_entry() function"<<endl;
fout<<"			:: Before, the program would crash if password of the max length was entered"<<endl;
fout<<"Ver 8.4:"<<endl;
fout<<"	[Header File improved]:"<<endl;
fout<<"		<> The Header File is now \"robot.h\" instead of \"cryptex.h\""<<endl;
fout<<"		<> Bug in pass_entry() function fixed"<<endl;
fout<<"			:: Before, the function would output random data if password of the max length was entered"<<endl;
fout<<"		<> A new function \"typeout\" outputs a specified character array as if it was bein typed out"<<endl;
fout<<"Ver 9.0/1.0:"<<endl;
fout<<"	[Design & Function Overhaul]:"<<endl;
fout<<"		<> The complete cryptex.cpp has been re-written"<<endl;
fout<<"		<> The ability to create the Header File has been limited to Developers"<<endl;
fout<<"			:: It can only be created via the DevKit Program"<<endl;
fout<<"		<> All menus are now more organised and slight animations have been added throughout the program"<<endl;
fout<<"		<> The cryptex.cpp file is self encrypted"<<endl;
fout<<"			:: It can only be decrypted by a Developer"<<endl;
fout<<"		<> Developer mode can only be unlocked with a Unique ID"<<endl;
fout<<"			:: This code is generated via DevKit program"<<endl;
fout<<"		<> A new set of files have been created for this overhaul"<<endl;
fout<<""<<endl;
fout<<"<<<----------MrRobot---------->>>"<<endl;













	fout.close();
	
	return;
}

//Mr.Robot
