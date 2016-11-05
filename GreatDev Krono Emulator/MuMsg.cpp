#include "StdAfx.h"
#include "MuMsg.h"

CMsg::CMsg()
{
	this->lMsgFree();
}

CMsg::~CMsg()
{
	this->lMsgFree();
}

void CMsg::lMsgFree()
{
	memset(&this->szDefaultMsg, 0, sizeof(this->szDefaultMsg));
	this->MsgById.clear();
}

void CMsg::LoadMSG(LPSTR filename)
{
	FILE* MSGFile;
	char szBufferError[128];
	char szLine[255];
	
	MSGFile = fopen(filename, "rb");
	
	if (MSGFile == NULL)
	{
		wsprintf(szBufferError, "Could not open %s !", filename);
		MessageBox(NULL, szBufferError, "Error", MB_OK);
		return;
	}

	// buffer
	char bLine[255] = {0};
	int bCat, bId, bIndex;
	char bMSG[255] = {0};

	while(!feof(MSGFile))
	{
		fgets(szLine, 255, MSGFile); // get line

		// Skip comments & end's
		if(szLine[0] == '/' || strcmp(szLine, "end") == 0 || strcmp(szLine, "end\n") == 0 || strcmp(szLine, "\n") == 0) continue;

		// Parse
		sscanf(szLine, "%d %d \"%255[^\"]\"", &bCat, &bId, &bMSG);

		// Add MSG to MAP
		bIndex = bCat * 256 + bId;
		this->MsgById[bIndex] = bMSG;
	}

	fclose(MSGFile);
}

LPSTR CMsg::Get(int idx)
{
	if (this->MsgById.count(idx) > 0)
	{
		return (char*) this->MsgById[idx].c_str();
	}
	else {
		int cat = floor((float)(idx/256));
		int id = idx % 256;

		wsprintf(this->szDefaultMsg, "MuMsg: Message error -> cat: %d id: %d", cat, id);
		return (char*) this->szDefaultMsg;
	}
}
