#pragma once

#define MSGGET(cat, id) ( (cat) * 256 + (id) )

class CMsg
{

public:

	CMsg();
	virtual ~CMsg();

	void LoadMSG(LPSTR filename);		// Считать сообщения из Messages.ini и запомнить
	LPSTR Get(int idx);					// Получить сообщение, тут в качестве аргумента всегда MSGGET(x, y)

private:

	char szDefaultMsg[50];				// Сообщение по дефаулту (если то что просим не найдено)
	std::map<int, std::string> MsgById;	// Индекс строки = CAT * 256 + ID
	void lMsgFree();					// Удалить все сообщения (освободить память)
};