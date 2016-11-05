#pragma once

static enum SMDToken 
{
	NAME, 
	NUMBER, 
	END, 
	COMMAND = '#',
	LP = '{',
	RP = '}',
	COMMA = ',',
	SEMICOLON = ';',
	SMD_ERROR
};

static FILE     *SMDFile;
static float    TokenNumber;
static char     TokenString[100];
static SMDToken CurrentToken;

static SMDToken GetToken()
{
	char ch;
	char *p = new char [255];
	char TempString[100];

	TokenString[0] = 0;

	do
	{
		if ((ch = fgetc(SMDFile)) == EOF)
		{
			return END;	
		}
		else
		{	
			if (ch == '/')		
			{
				if((ch = fgetc(SMDFile)) == '/')
				{
					while ((ch != '\n') && (ch != EOF))	
					{
						ch = fgetc(SMDFile);
					}
	
					if (ch == EOF)
					{
						return END;	
					}
				}
			}
		}
	}
	while (isspace(ch) != 0);

	switch(ch)
	{
	case 0x23:	// #
		return CurrentToken=COMMAND;
		break;
	
	case 0x3B:	// ;
		return CurrentToken=SEMICOLON;
		break;
	
	case 0x2C:	// ,

		return CurrentToken = COMMA;
		break;
	
	case 0x7B:	// {
		return CurrentToken = LP;
		break;

	case 0x7D:	// }
		return CurrentToken = RP;
		break;

	case 0x2D:	//-
	case 0x2E:	//.
	case '0':	//0
	case '1':	//1
	case '2':	//2
	case '3':	//3
	case '4':	//4		
	case '5':	//5
	case '6':	//6
	case '7':	//7
	case '8':	//8
	case '9':	//9
		ungetc(ch, SMDFile);
		p = TempString;
		
		while (((ch = getc(SMDFile)) != EOF) && ((ch == 0x2E) || (isdigit(ch) != 0) || (ch == 0x2D)))  // 2e '.'  2D '-'
		{
			*p = ch;
			p++;
		}		
		*p = 0;

		TokenNumber = atof(TempString);	
		return CurrentToken = NUMBER;
		break;

	case '\"':	// "	
		p=&TokenString[0];
		
		while (((ch=getc(SMDFile)) != EOF) && (ch != 0x22))	
		{
			*p = ch;
			p++;
		}
		if (ch != 0x22)
		{
			ungetc(ch, SMDFile);
		}
		*p = 0;
		return CurrentToken = NAME;
		break;

	default:	
		if (isalpha(ch))
		{
			p= &TokenString[0];
			*p = ch;
			p++;

			while (((ch = getc(SMDFile)) != EOF) && ((ch == 0x2E) || (ch == 0x5F) || (isalnum(ch) != 0)))
			{
				*p=ch;
				p++;
			}

			ungetc(ch, SMDFile);
			*p = 0;
			CurrentToken = NAME;
			return CurrentToken;
		}
		else
		{
			return CurrentToken = SMD_ERROR; // '<'
		}
		break;

	}
	return NAME;
}



