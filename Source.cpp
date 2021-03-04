#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <fstream>

using namespace std;
//================================================================ MAIN TEXT EDITOR============================================================== 
	struct Line
	{
		int Size;
		char* Cs;
	};
	struct Document
	{
		int NoofLines;
		Line* Lines;
	};
	struct Word
	{
		char*Cs;
	};
	struct Sentence
	{
		int WSize;
		Word *Ws;
	};
	struct Pragaraph
	{
		int Sensize;
		Sentence *Ss;
	};
	void gotoRowCol(int rpos, int cpos)
	{
		int xpos = cpos, ypos = rpos;
		COORD scrn;
		HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
		scrn.X = xpos; scrn.Y = ypos;
		SetConsoleCursorPosition(hOuput, scrn);
	}
	//Initializing 
	void Initializing(Document &Doc, int &cr, int &cc)
	{
		cr = 0, cc = 0;
		Doc.NoofLines = 1;
		Doc.Lines = new Line[Doc.NoofLines];
		Doc.Lines[0].Size = 0;
		Doc.Lines[0].Cs = new char[Doc.Lines[0].Size];
		Doc.Lines[0].Cs[0] = '\0';



	}
	//LOADING
	void LOADFILE(Document &Doc, int &Cr, int &Cc, char file[])
	{
		ifstream rdr(file);
		if (!file)
		{
			exit(NULL);
		}
		rdr >> Doc.NoofLines;
		Doc.Lines = new Line[Doc.NoofLines];

		rdr.ignore();
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			char *copyingline = new char[100];
			rdr.getline(copyingline, 100, '\n');
			Doc.Lines[i].Cs = copyingline;
			Doc.Lines[i].Size = strlen(copyingline);
			//Doc.Lines[i].Cs[Doc.Lines[i].Size] = '\0';
		}
	}
	//Make Doc Useable Phase-II
	void makeitusablegrow(Document &Doc)
	{
		Document fakevar;
		fakevar.NoofLines = Doc.NoofLines;
		fakevar.Lines = new Line[Doc.NoofLines];

		for (int i = 0; i < Doc.NoofLines - 1; i++)
		{
			fakevar.Lines[i].Cs = new char[Doc.Lines[i].Size + 1];
		}
		fakevar.Lines[Doc.NoofLines - 1].Size = 0;
		fakevar.Lines[Doc.NoofLines - 1].Cs = new char[fakevar.Lines[Doc.NoofLines - 1].Size];
		fakevar.Lines[Doc.NoofLines - 1].Cs[0] = '\0';
		for (int i = 0; i < Doc.NoofLines - 1; i++)
		{
			fakevar.Lines[i].Size = Doc.Lines[i].Size;
			for (int j = 0; j <= Doc.Lines[i].Size; j++)
			{
				fakevar.Lines[i].Cs[j] = Doc.Lines[i].Cs[j];

			}
			fakevar.Lines[i].Cs[fakevar.Lines[i].Size + 1] = '\0';
		}

		Doc = fakevar;


	}
	void makeitusableshrink(Document &Doc)
	{


		Document fakevar;
		fakevar.NoofLines = Doc.NoofLines;
		fakevar.Lines = new Line[Doc.NoofLines];

		for (int i = 0; i < Doc.NoofLines; i++)

		{
			fakevar.Lines[i].Cs = new char[Doc.Lines[i].Size];
		}
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			fakevar.Lines[i].Size = Doc.Lines[i].Size;
			for (int j = 0; j < Doc.Lines[i].Size; j++)
			{
				fakevar.Lines[i].Cs[j] = Doc.Lines[i].Cs[j];
			}
			fakevar.Lines[i].Cs[Doc.Lines[i].Size] = '\0';
		}

		Doc = fakevar;


	}
	//changing No. of lines
	void changenolofdoc(Document &Doc, int &lastNoofrow)
	{
		if (lastNoofrow < Doc.NoofLines)
		{
			makeitusablegrow(Doc);
			lastNoofrow = Doc.NoofLines;

		}
		else if (lastNoofrow > Doc.NoofLines)
		{
			makeitusableshrink(Doc);
			lastNoofrow = Doc.NoofLines;
		}

	}
	//SIMPLE ADD  
	void addsimpleatend(char ch, Document &Doc, int& Cr, int &Cc)
	{
		char *characterstring = new char[Doc.Lines[Cr].Size + 1];
		for (int i = 0; i < Doc.Lines[Cr].Size; i++)
		{
			characterstring[i] = Doc.Lines[Cr].Cs[i];
		}
		characterstring[Doc.Lines[Cr].Size] = ch;
		characterstring[Doc.Lines[Cr].Size + 1] = '\0';

		Doc.Lines[Cr].Size++;

		Doc.Lines[Cr].Cs = characterstring;
		Cc++;
		//PH-2
		if (Cc == 80)
		{
			Cc = 0;
			Cr++;
			Doc.NoofLines++;
		}
		else
		{
			return;
		}
	}
	// On pressing backspace 
	void OnPressingBACKSPACEiflineshift(Document &Doc, int &Cc, int &Cr)
	{
		for (int i = Cr; i < Doc.NoofLines; i++)
		{
			Doc.Lines[i].Cs = Doc.Lines[i + 1].Cs;
			Doc.Lines[i].Size = Doc.Lines[i + 1].Size;
		}
		Cr--;

		Doc.NoofLines--;
		makeitusableshrink(Doc);

	}
	// SHIFT EXTRALETTERS TO NEXT LINE
	void shiftinglettertonextline(Document &Doc, int Cr)
	{

		char *characterpointer = new char[Doc.Lines[Cr + 1].Size + 1];
		characterpointer[0] = Doc.Lines[Cr].Cs[Doc.Lines[Cr].Size - 1];

		for (int i = 1; i <= strlen(Doc.Lines[Cr + 1].Cs); i++)
		{
			characterpointer[i] = Doc.Lines[Cr + 1].Cs[i - 1];
		}

		characterpointer[Doc.Lines[Cr + 1].Size + 1] = '\0';
		Doc.Lines[Cr + 1].Size++;
		Doc.Lines[Cr + 1].Cs = characterpointer;
	}
	//TEXT IN MIDDLE
	void addinmiddle(char ch, Document &Doc, int& Cr, int &Cc, int &lastNOL)
	{
		char *characterstring = new char[Doc.Lines[Cr].Size + 1];
		for (int i = 0; i < Cc; i++)
		{
			characterstring[i] = Doc.Lines[Cr].Cs[i];
		}
		characterstring[Cc] = ch;
		for (int i = Cc + 1; i <Doc.Lines[Cr].Size + 1; i++)
		{
			characterstring[i] = Doc.Lines[Cr].Cs[i - 1];
		}
		characterstring[Doc.Lines[Cr].Size + 1] = '\0';
		//delete[] Doc.Lines[Cr].Cs;
		Doc.Lines[Cr].Size++;
		Doc.Lines[Cr].Cs = characterstring;
		Cc++;
		if (Doc.Lines[Cr].Size>79)
		{
			if (Cr == Doc.NoofLines - 1)
			{
				Doc.NoofLines++;
				changenolofdoc(Doc, lastNOL);
			}

			for (int i = Cr; i < Doc.NoofLines - 1; i++)
			{
				if (Doc.Lines[i].Size>79)
				{
					shiftinglettertonextline(Doc, i);
					Doc.Lines[i].Size = 79;
				}
			}


		}

		if (Cc == 80)
		{
			Doc.Lines[Cr].Size = 79;
			Cc = 0;
			Doc.Lines[Cr + 1].Size = strlen(Doc.Lines[Cr + 1].Cs + 1);
			Cr++;

		}
		else
		{
			return;
		}
	}
	// BACKSPACE
	void backspacemainwork(Document &Doc, int& Cr, int &Cc)
	{

		if ((Cr <= 0 && Cc <= 0) || (Cr < 0))
		{
			return;
		}
		if (Cc == 0 && Doc.Lines[Cr].Size == 0)
		{
			Doc.NoofLines--;
			Cc = Doc.Lines[Cr - 1].Size;
			Cr--;
			return;
		}
		if (Cc == 0)
		{
			Cc = Doc.Lines[Cr - 1].Size;
			Cr--;
			return;
		}
		else
		{
			char *characterstring = new char[Doc.Lines[Cr].Size];//As last will be Null 
			for (int i = 0; i <= Cc - 2; i++)
			{
				characterstring[i] = Doc.Lines[Cr].Cs[i];
			}
			for (int i = Cc; i <= Doc.Lines[Cr].Size; i++)
			{
				characterstring[i - 1] = Doc.Lines[Cr].Cs[i];
			}
			characterstring[Doc.Lines[Cr].Size] = '\0';
			Cc -= 2;
			Cc++;
			//delete []Doc.Lines[Cr].Cs;
			Doc.Lines[Cr].Size--;
			Doc.Lines[Cr].Cs = characterstring;
			if (Cc == 0 && Cr != 0)
			{
				Cc = Doc.Lines[Cr - 1].Size;
				if (Doc.Lines[Cr].Size == 0)
				{
					Doc.NoofLines--;
				}
				Cr--;
			}
			else
			{
				return;
			}
		}
	}
	//ON PRESSING ENTER 
	void OnPressingEnteriflineshift(Document &Doc, int &Cc, int &Cr)
	{
		char *chractertypearray1 = new char[Cc + 1];
		char *chractertypearray2 = new char[Doc.Lines[Cr].Size - Cc];
		for (int i = 0; i < Cc; i++)
		{
			chractertypearray1[i] = Doc.Lines[Cr].Cs[i];
		}
		chractertypearray1[Cc] = '\0';
		for (int i = 0; i < Doc.Lines[Cr].Size - Cc; i++)
		{
			chractertypearray2[i] = Doc.Lines[Cr].Cs[Cc + i];
		}
		chractertypearray2[Doc.Lines[Cr].Size - Cc] = '\0';
		//shifting all lines
		Doc.NoofLines++;
		makeitusablegrow(Doc);
		Doc.Lines[Doc.NoofLines - 1].Size = 0;
		int index = 0;
		for (int i = Cr + 1; i < Doc.NoofLines; i++)
		{
			Doc.Lines[Doc.NoofLines - index - 1] = Doc.Lines[Doc.NoofLines - index - 2];
			Doc.Lines[Doc.NoofLines - index - 1].Size = strlen(Doc.Lines[Doc.NoofLines - index - 1].Cs);
			index++;
		}
		Doc.Lines[Cr].Cs = chractertypearray1;
		Doc.Lines[Cr].Size = strlen(chractertypearray1);
		Doc.Lines[Cr + 1].Cs = chractertypearray2;
		Doc.Lines[Cr + 1].Size = strlen(chractertypearray2);
		Cc = 0;
	}
	//MOVING CURSOR
	void Columnchange(Document Doc, int value, int &Cc, int &Cr)
	{

		if (value == 77 && Cc != 79 && Doc.Lines[Cr].Size > Cc)
		{
			Cc++;
		}
		else if (value == 77 && Cc == 79 && Doc.NoofLines - 1 > Cr)
		{
			Cc = 0;
			Cr++;
		}
		else if (value == 75 && Cc != 0)
		{
			Cc--;
		}
		else if (value == 75 && Cc == 0 && Cr != 0)
		{
			Cc = Doc.Lines[Cr - 1].Size;
			Cr--;
		}
	}
	void Rowchange(Document Doc, int value, int &Cr, int &Cc)
	{
		if (value == 80 && Doc.NoofLines - 1 > Cr)
		{
			if (Cc > Doc.Lines[Cr + 1].Size)
			{
				Cc = Doc.Lines[Cr + 1].Size;
			}

			Cr++;
		}
		else if (value == 72 && Cr != 0)
		{
			if (Cc > Doc.Lines[Cr - 1].Size)
			{
				Cc = Doc.Lines[Cr - 1].Size;
			}
			Cr--;
		}
	}
	//PRINTING DOCUMENT
	void PrintingallDocument(Document Doc, int Cr)
	{
		system("cls");


		//cout << "\r";
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			cout << Doc.Lines[i].Cs << "\n";
		}
	}
	//SAVING -PH2---> phase one doesnt contain reading 
	void SavingCurrentDocument(Document Doc)
	{
		cout << "\n\n  FILE SAVING SHORT KEY DETECTED  \n\n   PLEASE TYPE NAME FOR FILE :";
		char *filename = new char[100];
		cin.getline(filename, 100);

		ofstream printtofile(filename);
		printtofile << Doc.NoofLines << "\n";
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			printtofile << Doc.Lines[i].Cs << "\n";
		}
	}
	//adding text
	void addtextintoDOC(Document &Doc, int &Cc, int &Cr, char typedletter, int &LASTNOL)
	{
		if (Cc >= Doc.Lines[Cr].Size)
		{
			addsimpleatend(typedletter, Doc, Cr, Cc);
		}
		else if (Cc < Doc.Lines[Cr].Size)
		{
			addinmiddle(typedletter, Doc, Cr, Cc, LASTNOL);
		}
	}
	//encrypting saving
	void saveasecryptedfile(Document Doc)
	{
		int datashuffle = 20;
		char filename[100];
		cin.ignore();
		char passwordforfile[100];
		cout << "\n\n\n FOR SAVING FILE AS ENCRPTED FIRST TYPE ITS PASSWORD  : ";	
		cin.getline(passwordforfile, 100);
		cout << "\n\n ENTER NAME OF FILE TO BE SAVE AS : ";
		cin.getline(filename, 100);
		ofstream encryptwriter(filename);
		encryptwriter << Doc.NoofLines<<"\n";
		char passwordencrypt[100];
		for (int i = 0; i<strlen(passwordforfile); i++)
		{
			char ch;
			ch = passwordforfile[i];
			for (int j = 0; j < datashuffle; j++)
			{
				ch--;
			}
			passwordencrypt[i] = ch;
		}
		passwordencrypt[strlen(passwordforfile)] = '\0';
		encryptwriter << passwordencrypt << "\n";
		Document encryptedDoc;
		encryptedDoc.Lines = new Line[Doc.NoofLines];
		for (int i = 0; i < Doc.NoofLines; i++)
		{

			encryptedDoc.Lines[i].Cs = new char[Doc.Lines[i].Size];
			for (int j = 0; j < Doc.Lines[i].Size; j++)
			{
				char ch;
				ch = Doc.Lines[i].Cs[j];
				for (int i = 0; i < datashuffle; i++)
				{
					ch--;
				}
				encryptedDoc.Lines[i].Cs[j] = ch;
			}
			encryptedDoc.Lines[i].Cs[Doc.Lines[i].Size] = '\0';
			encryptwriter << encryptedDoc.Lines[i].Cs << "\n";
		}

	}
	//Main Code
	void MainTExtCode(int &Cr, int &Cc, Document &Doc, char &typedletter)
	{
		int lastNoofrow = Doc.NoofLines;
		bool continueornot = true;
		PrintingallDocument(Doc, Cr);
		while (continueornot == true)
		{
			gotoRowCol(Cr, Cc);
			if (_kbhit())
			{
				int ASCIIForEnteredChar = _getch();

				switch (ASCIIForEnteredChar)
				{
				case 224://arrows
					ASCIIForEnteredChar = _getch();
					Columnchange(Doc, ASCIIForEnteredChar, Cc, Cr);
					Rowchange(Doc, ASCIIForEnteredChar, Cr, Cc);
					break;
				case 8://backspace

					if (Cc == 0 && Cr != 0 && Doc.Lines[Cr].Size == 0 && Cr < Doc.NoofLines)
					{
						OnPressingBACKSPACEiflineshift(Doc, Cc, Cr);
						lastNoofrow = Doc.NoofLines;
					}
					else
					{
						backspacemainwork(Doc, Cr, Cc);
					}
					break;

				case 13://enter
					if (Cc == Doc.Lines[Cr].Size)
					{
						Doc.NoofLines++;
						Cc = 0;
						Cr++;

					}
					else
					{
						OnPressingEnteriflineshift(Doc, Cc, Cr);
						lastNoofrow = Doc.NoofLines;
						Cr++;
					}
					break;
				case 0://SAVING F1
					ASCIIForEnteredChar = _getch();
					if (ASCIIForEnteredChar == 59)
					{
						SavingCurrentDocument(Doc);
					}
					else if (ASCIIForEnteredChar == 60)
					{
						saveasecryptedfile(Doc);
					}
					break;
				case 27://esc
				{
							continueornot = false;
							break;
				}
				default:
					typedletter = ASCIIForEnteredChar;
					addtextintoDOC(Doc, Cc, Cr, typedletter, lastNoofrow);

				}
				changenolofdoc(Doc, lastNoofrow);



				if (continueornot)
				{
					PrintingallDocument(Doc, Cr);
				}
				else if (!continueornot)
				{
					cout << " \n\n\n BREAKING ALL PROCESSING !!!!";
				}
			}



		}
	}
//========================================================== FEATURES =============================================================
//PART A
	void loadfromfile(Document &Doc,char *filename, int &Cr, int &Cc, char &typedletter)
	{
		cout << " TYPE FILE NAME ----> ";
		cin >> filename;
		LOADFILE(Doc, Cr, Cc, filename);
		
	}
//PART B
	void newfile(Document &Doc,int &Cr,int &Cc,char &typedletter)
	{
		Initializing(Doc, Cr, Cc);
		MainTExtCode(Cr, Cc, Doc, typedletter);
	}
//PART c
	void changemylineintouppercase(Document &Doc, int LineNumber)
	{
		LineNumber--;
		char *intouppercase=new char [100];//as max letters in one line is 80
		for (int i = 0; i < Doc.Lines[LineNumber].Size; i++)
		{
			intouppercase[i] = toupper(Doc.Lines[LineNumber].Cs[i]);
		}
		intouppercase[Doc.Lines[LineNumber].Size] = '\0';
		Doc.Lines[LineNumber].Cs = intouppercase;
	}
	void Uppercase(Document &Doc,int &Cr,int &Cc,char*filename,char &typedletter)
	{
		int linenumber;
		cout << " TYPE FILE NAME ----> ";
		cin >> filename;
		LOADFILE(Doc, Cr, Cc, filename);
		PrintingallDocument(Doc, Cr);
		cout << "\n\n ENTER THE LINE NUMBER : ";
		cin >> linenumber;
		changemylineintouppercase(Doc, linenumber);
		system("cls");
		MainTExtCode(Cr, Cc, Doc, typedletter);
		
	}
//PART D
	void changemylineintolowercase(Document &Doc, int LineNumber)
	{
		LineNumber--;
		char *intolowercase = new char[100];//as max letters in one line is 80
		for (int i = 0; i < Doc.Lines[LineNumber].Size; i++)
		{
			intolowercase[i] = tolower(Doc.Lines[LineNumber].Cs[i]);
		}
		intolowercase[Doc.Lines[LineNumber].Size] = '\0';
		Doc.Lines[LineNumber].Cs = intolowercase;
	}
	void Lowercase(Document &Doc, int &Cr, int &Cc, char*filename, char &typedletter)
	{
		int linenumber;
		cout << " TYPE FILE NAME  ----> ";
		cin >> filename;
		LOADFILE(Doc, Cr, Cc, filename);
		PrintingallDocument(Doc, Cr);
		cout << "\n\n ENTER THE LINE NUMBER : ";
		cin >> linenumber;
		changemylineintolowercase(Doc, linenumber);
		system("cls");
		MainTExtCode(Cr, Cc, Doc, typedletter);

	}
//part E
	int helpingfunction_FOrcountingdigts(Document Doc, int Cc, int Cr)
	{
		int index = Cc, index2;
		while (Doc.Lines[Cr].Cs[index] != ' ' && Cc<Doc.Lines[Cr].Size)
		{
			index++;
			Cc++;
		}
		index2 = index;
		while (Doc.Lines[Cr].Cs[index2-1] != ' ' && Cc != 0)
		{
			index2--;
			Cc--;
		}
		return  index-index2;
	}
	void RecordingWordposition(int &Fline, int &FColumn, Document Doc, Word word,int lastsavedline,int lastsavedcolumn)
	{
	    int wordlength = strlen(word.Cs);
		int countoflength = 0;
		int index=0;
		for (int i = lastsavedline; i < Doc.NoofLines; i++)
		{
			for (int j = lastsavedcolumn; j < Doc.Lines[i].Size; j++)
			{
				if (Doc.Lines[i].Cs[j] == word.Cs[index])
				{
					countoflength++;
					index++;
					if (countoflength == wordlength)
					{
						//as the index starts from 0 therefore 1 added in both
						Fline = i;
						FColumn = (j - (wordlength)+1);
						return;
					}
				}
				else
				{
					index = 0;
					countoflength = 0;
				}


			}
			lastsavedcolumn = 0;
			
		}
	}
	void FindingWordInCaseSenstive(Document &Doc,char *filename,int &Cr,int &Cc)
	{
		int FLine, FColumn;
		Word word;
		word.Cs = new char[100];//word size limit 100
		cout << " TYPE FILE NAME FROM WHICH WORD IS TO BE FIND ----> ";
		cin >> filename;
		LOADFILE(Doc, Cr, Cc, filename);
		PrintingallDocument(Doc, Cr);
		cin.ignore();
		cout << "\n\n ENTER WORD : ";
		cin.getline(word.Cs, 100);
		RecordingWordposition(FLine, FColumn, Doc, word,0,0);
		int requiredlength = strlen(word.Cs);
		int numbershouldbe = helpingfunction_FOrcountingdigts(Doc, FColumn, FLine);
		if (FLine >=0 && FColumn >=0 && requiredlength == numbershouldbe)
		{
			cout << " THE WORD  EXISTS ON LINE : " << FLine+1 << " AND ON COLUMN : " << FColumn+1;
			cout << "\n\n\n";
		}
		else
		{
			cout << "   THE WORD DOESNT EXIST MAY TRY INSENSITIVE SEARCH ......";
		}
	

	}
//part F 
	void RecordingWordpositionIn(int &Fline, int &FColumn, Document Doc, Word word)
	{
		int wordlength = strlen(word.Cs);
		int countoflength = 0;
		int index = 0;
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			for (int j = 0; j <Doc.Lines[i].Size; j++)
			{
				if (toupper(Doc.Lines[i].Cs[j]) == word.Cs[index] || tolower(Doc.Lines[i].Cs[j]) == word.Cs[index])
				{
					countoflength++;
					index++;
					if (countoflength == wordlength)
					{
						//as the index starts from 0 therefore 1 added in both
						Fline = i ;
						FColumn = (j - wordlength) + 1;
					}
				}
				else
				{
					index = 0;
					countoflength = 0;
				}

			}

		}
	}
	void FindingWordInCaseInSenstive(Document &Doc, char *filename, int &Cr, int &Cc)
	 {
		 int FLine, FColumn;
		 Word word;
		 word.Cs = new char[100];//word size limit 100
		 cout << " TYPE FILE NAME FROM WHICH WORD IS TO BE FIND ----> ";
		 cin >> filename;
		 LOADFILE(Doc, Cr, Cc, filename);
		 PrintingallDocument(Doc, Cr);
		 cin.ignore();
		 cout << "\n\n ENTER WORD  : ";
		 cin.getline(word.Cs, 100);
		 RecordingWordpositionIn(FLine, FColumn, Doc, word);
		 int requiredlength = strlen(word.Cs);
		 int numbershouldbe = helpingfunction_FOrcountingdigts(Doc, FColumn, FLine);
		 if (FLine >= 0 && FColumn >= 0 && requiredlength == numbershouldbe)
		 {
			 cout << " THE WORD  EXISTS ON LINE : " << FLine+1<< " AND ON COLUMN : " << FColumn+1;
			 cout << "\n\n\n";
		 }
		 else
		 {
			 cout << "      THE WORD DOESNT EXISTS  ......";
		 }
	}
//part G
	void Doessentencexists(Document Doc, char *sentence,int &locationline ,int &locationcolumn)
	{
		
		int lengthrequied = strlen(sentence);
		int counter = 0,startpointline,startpointcolumn=0;
		int index = 0;
		for (int i = 0; i < 8; i++)
		{
			//cout << "                      --->" << i << "\n";
			for (int j = 0; j < Doc.Lines[i].Size; j++)
			{
				if (Doc.Lines[i].Cs[j] == sentence[index] )
				{
					if (counter == 0)
					{
						startpointline = i;
						startpointcolumn = j;
					}
					counter++;
					index++;
					
					//cout << counter << "\n";
					if (counter == lengthrequied)
					{
						locationcolumn = startpointcolumn;
						locationline = startpointline;
						return;
					}
				}
				else
				{
					counter = 0;
					index = 0;
				}

			}
			counter = 0;
			index = 0;
		}
	
		locationcolumn = -1, locationline = -1;
	}
	void SentenceFinding(Document &Doc)
	{
		int Cr, Cc;
		char *filename=new char [100];
		char *senstence = new char[100];
		cout << "\n\n ENTER THE NAME OF FILE YOU WANT TO OPEN : ";
		cin.getline(filename, 100);
		LOADFILE(Doc,Cr, Cc, filename);
		PrintingallDocument(Doc, Cr);
		cout << "\n ENTER THE NAME OF FILE WHERE LIES SENTENCE : ";
		cin.getline(filename, 100);
		ifstream rdr(filename);
		rdr.getline(senstence, 100);
		cout <<"\n\n"<<senstence;
		Doessentencexists(Doc, senstence, Cr, Cc);
		if (Cr >= 0 && Cc >= 0)
		{
			cout << " \n\n  THIS SENTENCE IS FOUND AT LOCATION LINE : " << Cr + 1;
			cout << " AND STARTING COLUMN :" << Cc + 1;
		}
		else
		{
			cout << " \n\n    ENTERED SENTENCE DONT EXIST IN THIS DOCUMENT !!!!! .......";
		}		
	}
//part H
	void SearchSubstring(Document &Doc, char *filename, int &Cr, int &Cc)
	{
		int FLine, FColumn;
		Word SUBSTRING;
		SUBSTRING.Cs = new char[100];//SENTENCE size limit 100
		cout << " TYPE FILE NAME FROM WHICH WORD IS TO BE FIND ----> ";
		cin >> filename;
		LOADFILE(Doc, Cr, Cc, filename);
		PrintingallDocument(Doc, Cr);
		cin.ignore();
		cout << "\n\n ENTER SUBSTRING : ";
		cin.getline(SUBSTRING.Cs, 100);
		RecordingWordposition(FLine, FColumn, Doc, SUBSTRING,0,0);
		if (FLine >=0 && FColumn >=0 )
		{
			cout << " THE SUBSTRING  EXISTS ON LINE : " << FLine+1 << " AND ON COLUMN : " << FColumn+1;
			cout << "\n\n\n";
		}
		else
		{
			cout << "   THE SUBSTRING DOESNT EXIST !!!!!! ......";
		}
	}
//part I
	void findandreplaceword(Document &Doc)
	{
		char *filename=new char [100];
		int Cr;
		int Cc;
		char ch;
		int lastlocationline = 0, lastlocationcolumn = 0;
		cout << " TYPE FILE NAME FROM WHICH WORD IS TO BE REPLACED ----> ";
		cin >> filename;
		LOADFILE(Doc, Cr, Cc, filename);
		int LNOL = Doc.NoofLines;
		PrintingallDocument(Doc, Cr);
		Word word;
		cin.ignore();
		cout << " ENTER WORD TO REPLACE : ";
		word.Cs = new char[100];
		cin.getline(word.Cs, 100);
		int length = strlen(word.Cs);
		word.Cs[length] = '\0';
		cout << "\n ENTER THE WORD TO BE REPLACED WITH : ";
		Word REPLACEDWORD;
		REPLACEDWORD.Cs = new char[100];
		cin.getline(REPLACEDWORD.Cs, 100);
		int replacedlength = strlen(REPLACEDWORD.Cs);
		REPLACEDWORD.Cs[replacedlength] = '\0';

		RecordingWordposition(Cr, Cc, Doc, word,lastlocationline,lastlocationcolumn);
		int looptimes = helpingfunction_FOrcountingdigts(Doc, Cc, Cr);
		Cc += length;
		for (int i = 0; i < length; i++)
		{
			backspacemainwork(Doc, Cr, Cc);
		}
		
		for (int i = 0; i <replacedlength; i++)
		{
			ch = REPLACEDWORD.Cs[i];
			addtextintoDOC(Doc, Cc, Cr, ch,LNOL);
		}
        
		MainTExtCode(Cr, Cc, Doc, ch);
	}
//part J
	void findandreplacewordall(Document &Doc)
	{
		char *filename = new char[100];
		int Cr=0;
		int Cc=0;
		char ch;
		int lastlocationline = 0, lastlocationcolumn = 0;
		cout << " TYPE FILE NAME FROM WHICH WORD IS TO BE REPLACED ----> ";
		cin >> filename;
		LOADFILE(Doc, Cr, Cc, filename);
		int LNOL = Doc.NoofLines;
		PrintingallDocument(Doc, Cr);
		Word word;
		cin.ignore();
		cout << " ENTER WORD TO REPLACE IN WHOLE FILE : ";
		word.Cs = new char[100];
		cin.getline(word.Cs, 100); 
		int length = strlen(word.Cs);
		word.Cs[length] = '\0';
		cout << "\n ENTER THE WORD TO BE REPLACED WITH : ";
		Word REPLACEDWORD;
		REPLACEDWORD.Cs = new char[100];
		cin.getline(REPLACEDWORD.Cs, 100);
		int replacedlength = strlen(REPLACEDWORD.Cs);
		REPLACEDWORD.Cs[replacedlength] = '\0';
		bool loop = true;
		while (loop)
		{
			lastlocationcolumn = Cc , lastlocationline = Cr;
			RecordingWordposition(Cr, Cc, Doc, word, lastlocationline, lastlocationcolumn);
			if (lastlocationcolumn == Cc && lastlocationline == Cr && Cr!=0 && Cc!=0)
			{
				PrintingallDocument(Doc, Cr);
				loop = false;
			}
			else
			{
				lastlocationcolumn = Cc , lastlocationline = Cr;
				int looptimes = helpingfunction_FOrcountingdigts(Doc, Cc, Cr);
				Cc += length;
				for (int i = 0; i < length; i++)
				{
					backspacemainwork(Doc, Cr, Cc);
				}

				for (int i = 0; i < replacedlength; i++)
				{
					ch = REPLACEDWORD.Cs[i];
					addtextintoDOC(Doc, Cc, Cr, ch, LNOL);
				}
			}
		}
		MainTExtCode(Cr, Cc, Doc, ch);
	}
//part W 
	void openencryptedfile(Document &Doc,int &Cr,int &Cc)
	{
		char typedletter;
		char *filename = new char[100];
		int datashuffle = 20;
		Document Ecrypteddata;
		char passwordcheck[100];
		cout << " TYPE FILE NAME ----> ";
		cin >> filename;
	    
		ifstream reader(filename);
		reader >> Ecrypteddata.NoofLines;
		Doc.NoofLines = Ecrypteddata.NoofLines;
		Ecrypteddata.Lines = new Line[Ecrypteddata.NoofLines];
		cout << "\n\n\n   PLEASE INPUT PASSWORD IN ORDER TO ACCESS THE FILE : ";
		reader.ignore();
		reader.getline(passwordcheck, 100,'\n');
 		char usertypedpassword[100];
		cin.ignore();
		cin.getline(usertypedpassword, 100);
		for (int i = 0; i < strlen(passwordcheck); i++)
		{
			char ch = passwordcheck[i];
			for (int i = 0; i < datashuffle; i++)
			{
				ch++;
			}
			passwordcheck[i] = ch;
		}
		for (int i = 0; i < strlen(passwordcheck); i++)
		{
			if (passwordcheck[i] != usertypedpassword[i])
			{
				cout << "\n\n SORRY BUT THE PASSWORD ENTERED DOESN'T MATCHES WITH THE PASSWORD THAT WAS ENTERED BY THE OWNER";
				return;
			}
		}
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			Ecrypteddata.Lines[i].Cs = new char[100];
			
			reader.getline(Ecrypteddata.Lines[i].Cs, 100, '\n');
			for (int j = 0; j < strlen(Ecrypteddata.Lines[i].Cs); j++)
			{
				char ch = Ecrypteddata.Lines[i].Cs[j];
				for (int k = 0; k < datashuffle; k++)
				{
					ch++;
				}
				Ecrypteddata.Lines[i].Cs[j] = ch;
			}
			Doc.Lines[i].Cs = Ecrypteddata.Lines[i].Cs;
			Doc.Lines[i].Size = strlen(Ecrypteddata.Lines[i].Cs);
			Doc.Lines[i].Cs[strlen(Ecrypteddata.Lines[i].Cs)] = '\0';
		}
		MainTExtCode(Cr, Cc, Doc, typedletter);
	}

//part R
	void mergingTWOFilesintoOne(Document &Doc)
	{
		Document Doc1,Doc2;
		int Cr, Cc;
		char ignoremaroch;
		char filename[100];
		
		cout << "  FOR FIRST FILE \n\n";
		loadfromfile(Doc1, filename, Cr, Cc, ignoremaroch);
	    cout << "  FOR SECOND FILE \n\n";
		loadfromfile(Doc2, filename, Cr, Cc, ignoremaroch);
		Doc.NoofLines = Doc1.NoofLines + Doc2.NoofLines;
		Doc.Lines = new Line[Doc.NoofLines];
		for (int i = 0; i < Doc1.NoofLines; i++)
		{
			Doc.Lines[i].Cs = Doc1.Lines[i].Cs;
		}
		for (int i = 0; i < Doc2.NoofLines; i++)
		{
			Doc.Lines[i + Doc1.NoofLines].Cs = Doc2.Lines[i].Cs;
		}
	}
//part-U
	void letscountNumberofPARAGRAPH(Document &Doc)
	{ 
		int Noofparagraph = 0;
		char *filename = new char[100];
		int Cr = 0;
		int Cc = 0;
		int lastlocationline = 0, lastlocationcolumn = 0;
		cout << " TYPE FILE NAME FROM WHICH  NUMBER OF PARAGRAPH IS TO BE CALCULATED ---> ";
		cin >> filename;
		LOADFILE(Doc, Cr, Cc, filename);
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			if (Doc.Lines[i].Size == 0 && Doc.Lines[i + 1].Size == 0)
			{
				Noofparagraph++;
			}
		}
		PrintingallDocument(Doc, Cr);
		cout << "\n\n  LOADED FILE CONTAIN " << Noofparagraph << " NO . OF PARAGRAPH ...!!!! ";
	}
//PART-K
	void addwordinfront(int &Cr,int &Cc,char ch,Document &Doc)
	{
		int NOL = Doc.NoofLines;
		addinmiddle(ch,Doc, Cr, Cc, NOL);

	}
	void addprefix(Document &Doc)
	{
		char ch, *filename = new char[100];
		Word word;
		word.Cs= new char[100];
		int Cr, Cc;
		char *prefix = new char[100];
		loadfromfile(Doc, filename, Cr, Cc, ch);
		PrintingallDocument(Doc, Cr);
		cin.ignore();
		cout << " ENTER WORD TO ADD PREFIX : ";
		cin.getline(word.Cs, 100);
		cout << " \n ENTER PRE FIX WORD TO ADD  : ";
		cin.getline(prefix, 100);
		RecordingWordposition(Cr, Cc, Doc,word, 0,0);
		for (int i = 0; i < strlen(prefix); i++)
		{
			
			addwordinfront(Cr, Cc, prefix[i], Doc);
		}
		MainTExtCode(Cr, Cc, Doc, ch);
	   
	}
//PART-L
	void addwordinend(int &Cr, int &Cc, char ch, Document &Doc)
	{
		int NOL = Doc.NoofLines;
		addinmiddle(ch, Doc, Cr, Cc, NOL);

	}
	void addpostfix(Document &Doc)
	{
		char ch, *filename = new char[100];
		Word word;
		word.Cs = new char[100];
		int Cr, Cc;
		char *postfix = new char[100];
		loadfromfile(Doc, filename, Cr, Cc, ch);
		PrintingallDocument(Doc, Cr);
		cin.ignore();
		cout << " ENTER WORD TO ADD POSTFIX : ";
		cin.getline(word.Cs, 100);
		cout << " \n ENTER POST FIX WORD TO ADD  : ";
		cin.getline(postfix, 100);
		RecordingWordposition(Cr, Cc, Doc, word, 0, 0);
		int lenghtofword = helpingfunction_FOrcountingdigts(Doc, Cc, Cr); 
		Cc = +lenghtofword;
		for (int i = 0; i < strlen(postfix); i++)
		{

			addwordinend(Cr, Cc, postfix[i], Doc);
		}
		MainTExtCode(Cr, Cc, Doc, ch);

	}
//part M
	void MAINCOUNTWORDWLegth(Document &Doc)
	{
		int Cc=0, Cr=0;
		char ch;
		char *filename = new char[100];
		loadfromfile(Doc, filename, Cr, Cc, ch);
		PrintingallDocument(Doc, Cr);
         
		int lastlegth = 0;
		int average = 0;
		int totalwords = 0;
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			Cr = i;
			Cc = 0;
			while (Cc<Doc.Lines[i].Size)
			{
				lastlegth = helpingfunction_FOrcountingdigts(Doc, Cc, Cr);
				if (lastlegth>1)
				{
					totalwords++;
					average = average + lastlegth;
					if (Cc + lastlegth + 1 < Doc.Lines[i].Size)
					{
						Cc =Cc+ lastlegth + 1;
					}
					else
					{
						break;
					}
				}
				else
				{
					Cc++;
				}
				//cout << "check \n";
			}
			
		}
		average = average / totalwords;

		cout << " \n\n  TOTAL NUMBER OF WORDS ARE : " << totalwords;
		cout << "\n\n AVERAGE WORD LENGTH IN WHOLE FILE IS : " << average;
	}
//PART -N
	void substringcount(Document &Doc)
	{
		int Cc = 0, Cr = 0;
		char ch;
		int index = 0, counters = 0,mainresult=0, lengthofsubstring = 0;;
		char *filename = new char[100];
		loadfromfile(Doc, filename, Cr, Cc, ch);
		PrintingallDocument(Doc, Cr);
		char *SUBSTRING = new char[100];
		cin.ignore();
		cout << "\n\n ENTER SUBSTRING : ";
		cin.getline(SUBSTRING, 100);
		lengthofsubstring = strlen(SUBSTRING);
		int j = 0, i = 0;
		while (index < Doc.NoofLines)
		{
			
			while( i < Doc.Lines[index].Size)
			{

				if (Doc.Lines[index].Cs[i] == SUBSTRING[j])
				{
					i++;
					j++;
					counters++;
					
				}
				else
				{
					j = 0;
					i++;
					counters = 0;
				}
				if (counters == lengthofsubstring)
				{
					mainresult++;
					counters = 0;
					j = 0;

				}

	
				
				
		
				
			}
			j = 0;
			i = 0;
			index++;
		}
		cout << " ENTERED SUBSTRING HAVE COUNT : " << mainresult;
		
	}
// PART O
	int caculatenumberofspecialch(Document Doc)
	{
		int counters = 0;
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			for (int j = 0; j < Doc.Lines[i].Size; j++)
			{
				if (Doc.Lines[i].Cs[j] >= 'a' && Doc.Lines[i].Cs[j] <= 'z' || Doc.Lines[i].Cs[j] >= 'A' && Doc.Lines[i].Cs[j] <= 'Z' && Doc.Lines[i].Cs[j] >= '0' &&Doc.Lines[i].Cs[j] <= '9')
				{

				}
				else
				{
					counters++;
				}
			}
		}
		return counters;

	}
	void NumberofSpecialCharacters(Document Doc)
	{
		char *filename = new char[100];
		int Cr, Cc;
		cout << " \n  ENTER THE NAME OF FILE TO LOAD FOR THIS CHECK : ";
		cin.getline(filename, 100);
		LOADFILE(Doc, Cr, Cc, filename);
		int numberofspecialch = caculatenumberofspecialch(Doc);
		PrintingallDocument(Doc, Doc.NoofLines);
		cout << "\n\n\n   TOTAL NUMBER OF SPECIAL CHARACTERS INCLUDING SPACES ARE : " << numberofspecialch;

	}
//PART P
	int Sentececount(Document &Doc)
	{
		int count = 0;
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			for (int j = 0; j < Doc.Lines[i].Size-1; j++)
			{
				if (Doc.Lines[i].Cs[j] == ' ' && Doc.Lines[i].Cs[j + 1] == '.')
				{
					count++;
				}
			}
		}
		return count;
	}
	void mainsentencecounter(Document &Doc)
	{
		int Cc = 0, Cr = 0;
		char ch;
		int index = 0, counters = 0, mainresult = 0, lengthofsubstring = 0;;
		char *filename = new char[100];
		loadfromfile(Doc, filename, Cr, Cc, ch);
		PrintingallDocument(Doc, Cr);
		cout << " THE NUMBER OF SENTENCES IN THIS LOADED FILE ARE : " << Sentececount(Doc);

	}
//PART Q
	void LARGESTWORDSIZE(Document &Doc)
	{
		int Cc = 0, largestCc, largestCr, Cr = 0;
		char ch;
		int index = 0, counters = 0, mainresult = 0, lengthofsubstring = 0;;
		char *filename = new char[100];
		loadfromfile(Doc, filename, Cr, Cc, ch);
		PrintingallDocument(Doc, Cr);
		int largestsize = 0;
		int size = 0;
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			Cr = i;
			for (int j = 0; j < Doc.Lines[i].Size; j++)
			{
				size = helpingfunction_FOrcountingdigts(Doc, Cc, Cr);
				Cc = Cc + size+1;
				j = Cc;
				if (largestsize < size)
				{
					largestsize = size;
					largestCc = Cc-size;
					largestCr = Cr;
				}
			}
			Cc = 0;
		}
		cout << " THE LARGEST WORD LENGTH IS : " << largestsize;
	}
//PART S
	void SMALLESRWORDSIZE(Document &Doc)
	{
		int Cc = 0, Cr = 0;
		char ch;
		int index = 0, counters = 0, mainresult = 0, lengthofsubstring = 0;;
		char *filename = new char[100];
		loadfromfile(Doc, filename, Cr, Cc, ch);
		PrintingallDocument(Doc, Cr);
		int smallestsize = helpingfunction_FOrcountingdigts(Doc, Cc, Cr);
		int size = 0;
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			Cr = i;
			for (int j = 0; j < Doc.Lines[i].Size; j++)
			{
				size = helpingfunction_FOrcountingdigts(Doc, Cc, Cr);
				Cc = Cc + size + 1;
				j = Cc;
				if (smallestsize > size)
				{
					smallestsize = size;
					
				}
			}
			Cc = 0;
		}
		cout << "\n\n THE SMALLEST WORD LENGTH IS : " << smallestsize;

	}
//PART T
	void copymydataintostringipass(const Document &Doc, int Cc, int Cr, int length,char *&str1)
	{
		str1 = new char[length+1];
		for (int i = 0; i < length; i++)
		{
			str1[i]=Doc.Lines[Cr].Cs[Cc + i];
		}
		str1[length] = '\0';
	}
	void FINDINGMAXWORDHAVINGOTHERWORDS(Document &Doc)
	{
		int numberofsubworbs = 0;
		int maxnumberofsubwords = 0;
		char ch; int Cc = 0, Cr = 0;
		int index = 0, counters = 0, mainresult = 0, lengthofsubstring = 0;;
		char *filename = new char[100];
		loadfromfile(Doc, filename, Cr, Cc, ch);
		PrintingallDocument(Doc, Cr);
		char *search, *compare;
		int existingnumbers = 0;
		int indexonsearchingrow = 0, indexonsearchingcol = 0;
		int indexoncomparingrow = 0, indexoncomparingingcol = 0;
		int maxindexoncomparingrow = 0, maxindexoncomparingingcol = 0;
		int sizeforsearch = 0,sizeforcompare=0;
		sizeforsearch = helpingfunction_FOrcountingdigts(Doc, indexonsearchingcol, indexonsearchingrow);
		sizeforcompare = helpingfunction_FOrcountingdigts(Doc, indexoncomparingingcol, indexoncomparingrow);
		copymydataintostringipass(Doc, indexonsearchingcol, indexonsearchingrow, sizeforsearch, search);
		copymydataintostringipass(Doc, indexoncomparingingcol, indexoncomparingrow,sizeforcompare, compare);
		while (indexoncomparingrow < Doc.NoofLines)
		{
			indexoncomparingrow = index;
			sizeforcompare = helpingfunction_FOrcountingdigts(Doc, indexoncomparingingcol, indexoncomparingrow);
			copymydataintostringipass(Doc, indexoncomparingingcol, indexoncomparingrow, sizeforcompare, compare);
			
			for (int i = 0; i < Doc.NoofLines; )
			{
				for (int j = 0; j < Doc.Lines[i].Size; )
				{
					sizeforsearch = helpingfunction_FOrcountingdigts(Doc, indexonsearchingcol, indexonsearchingrow);
					copymydataintostringipass(Doc, indexonsearchingcol, indexonsearchingrow, sizeforsearch, search);
					
					if (sizeforsearch <= sizeforcompare)
					{
						for (int loop = 0; loop < sizeforsearch; loop++)
						{
							for (int loop2 = 0; loop2 < sizeforcompare; loop2++)
							{
								if (search[loop] == compare[loop2])
								{
									existingnumbers++;
								}
							}
						}
						if (existingnumbers >= sizeforsearch)
						{
							numberofsubworbs++;
							if (numberofsubworbs > maxnumberofsubwords)
							{
								maxnumberofsubwords = numberofsubworbs;
								maxindexoncomparingrow = indexoncomparingrow;
								maxindexoncomparingingcol = indexoncomparingingcol;
							}
						}

					}
					existingnumbers = 0;
					indexonsearchingcol = indexonsearchingcol + sizeforsearch + 1;
					j = indexonsearchingcol;
					indexonsearchingrow = i;
					
				}
				i++;
				indexonsearchingcol = 0;
				indexonsearchingrow++;

     		}
			
			    numberofsubworbs = 0;
				indexonsearchingcol = 0;
				indexonsearchingrow = 0;
				indexoncomparingingcol =indexoncomparingingcol+sizeforcompare+1;
				
				if (indexoncomparingingcol > Doc.Lines[index].Size)
				{
					index++;
					indexoncomparingingcol = 0;
				}
				
				indexoncomparingrow = index;
				
		}
		cout << "\n\nTHE WORD HAVING MAX OTHER WORDS IS AT LOCATION :	ROW : " << maxindexoncomparingrow+1<< " AND COLUMN : " << maxindexoncomparingingcol+1;
		cout << " \n IT INCLUDES : " << maxnumberofsubwords-1<< " WORDS INSIDE IT SELF";
	}
//PRAt V
	int wordcountwithinlimit(Document &Doc, int Startrow, int Lastrow)
	{
		int Cr = 0;
		int Cc = 0;
		int lastlegth;
		int totalwords = 0;
		for (int i = Startrow; i < Lastrow; i++)
		{
			Cr = i;
			Cc = 0;
			while (Cc<Doc.Lines[i].Size)
			{
				lastlegth = helpingfunction_FOrcountingdigts(Doc, Cc, Cr);
				if (lastlegth>1)
				{
					totalwords++;

					if (Cc + lastlegth + 1 < Doc.Lines[i].Size)
					{
						Cc = Cc + lastlegth + 1;
					}
					else
					{
						break;
					}
				} 
					else
					{
						Cc++;
					}

				}
			
		}
		return totalwords;
	}
	void numberofwordsinlaegrestparagraph(Document &Doc)
	{
		int numberofwords = 0, maxnumberofword = 0;
		int numberoflargestpragraph = 0;
		char *filename = new char[100];
		int Cr = 0;
		int Cc = 0;
		int lastlocationline = 0, lastlocationcolumn = 0;
		cout << " TYPE FILE NAME FROM WHICH  PARAGRAPH IS TO BE READ---> ";
		cin >> filename;
		LOADFILE(Doc, Cr, Cc, filename);
		PrintingallDocument(Doc, Cr);
		Cr = 0;
		Cc = 0;
		for (int i = 0; i < Doc.NoofLines; i++)
		{
			if (Doc.Lines[i].Size == 0 && Doc.Lines[i + 1].Size == 0)
			{
				Cr = lastlocationline;
				lastlocationline = i;
			
				numberofwords = wordcountwithinlimit(Doc, Cr, lastlocationline);
				if (numberofwords>maxnumberofword)
				{
					maxnumberofword = numberofwords;
					numberoflargestpragraph++;
					
				}
				
			}
			
		}
		cout << " LARGEST PARAGRAPH IS : " << numberoflargestpragraph+1 << " AND IT IS HAVING NEARLY : " << maxnumberofword << "	WORDS IN IT !! ";
	}
//==========================================================MENU=================================================================
void menuandExecution(Document &Doc)
{
	bool loop = true;
	char option;
	int Cr=0, Cc = 0;
	char filename[] = "hello.txt";
	LOADFILE(Doc, Cr, Cc,filename);
	PrintingallDocument(Doc, Cr);
	char typedletter;
	while (loop) 
	{
		if (_kbhit())
		{
			option = _getch();
			if (option >= 'A' && option <= 'X')
			{
				loop = false;
				cout << "\r                                          ";
				Sleep(100);
				system("cls");
				switch (option)
				{

				case 'A':
				{
							loadfromfile(Doc, filename, Cr, Cc, typedletter);
							MainTExtCode(Cr, Cc, Doc, typedletter);
							break;
				}
				case 'B':
				{
							newfile(Doc, Cr, Cc, typedletter);
							break;
				}
				case 'C':
				{
							Uppercase(Doc, Cr, Cc, filename, typedletter);
							break;
				}
				case 'D':
				{
							Lowercase(Doc, Cr, Cc, filename, typedletter);
							break;
				}
				case 'E':
				{
							FindingWordInCaseSenstive(Doc, filename, Cr, Cc);
							break;
				}
				case 'F':
				{
							FindingWordInCaseInSenstive(Doc, filename, Cr, Cc);
							break;
				}
				case 'G':
				{
							SentenceFinding(Doc);
							break;
				}
				case 'H':
				{
							SearchSubstring(Doc, filename, Cr, Cc);
							break;
				}
				case 'I':
				{
							findandreplaceword(Doc);
							break;
				}
				case 'J':
				{
							findandreplacewordall(Doc);
							break;
				}
				case 'K':
				{
							addprefix(Doc);
							break;
				}
				case 'L':
				{
							addpostfix(Doc);
							break;
				}
				case 'M':
				{
							MAINCOUNTWORDWLegth(Doc);
							break;
				}
				case 'N':
				{
							substringcount(Doc);
							break;
				}
				case 'P':
				{
							mainsentencecounter(Doc);
							break;
				}
				case 'Q':
				{
							LARGESTWORDSIZE(Doc);
							break;
				}
				case 'V':
				{
							numberofwordsinlaegrestparagraph(Doc);
							break;
				}
				case 'R':
				{
							mergingTWOFilesintoOne(Doc);
							MainTExtCode(Cr, Cc, Doc, typedletter);
							break;
                              						
				}
				case 'S':
				{
							SMALLESRWORDSIZE(Doc);
							break;
				}
				case 'T':
				{
							FINDINGMAXWORDHAVINGOTHERWORDS(Doc);
							break;
				}
				case 'U':
				{
							letscountNumberofPARAGRAPH(Doc);
							break;
				}
				case'W':
				{
						   openencryptedfile(Doc, Cr, Cc);
						   break;
				}
				case 'O':
				{
							NumberofSpecialCharacters(Doc);
							break;
				}
				default:
					cout << "   ERROR IN SELECTION -__-   PUFFF!!!!";
					break;
				}

			}
		}

		else
		{
			Sleep(80);
			cout << "\r                           - / | \ - - / | \ - ";
			Sleep(80);
			cout << "\r                           / | \ - / / | \ - / ";
			Sleep(80);
			cout << "\r                           | \ - / | | \ - / | ";
			Sleep(80);
			cout << "\r                           \ - / | \ \ - / | \ ";
			
		}
	}
}
int main()
{
	
	Document DOC;
	menuandExecution(DOC);
	_getch();
	return 0;

}