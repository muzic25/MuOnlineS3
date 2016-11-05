// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
// gate.h

#ifndef GATE_H
#define GATE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAX_GATES 256

class CGate
{
public:

	CGate();
	virtual ~CGate();

	void Init();
	void Load(LPSTR Buffer, int iSize);
	void Load(LPSTR filename);
	int IsGate(int GateNumber);
	int GetGate(int mgt, short& x, short& y, BYTE& MapNumber, BYTE& dir, short& Level);
	int GetLevel(int GateNumber);
	int IsInGate(int aIndex, int GateNumber);
	int CheckGateLevel(int aIndex, int GateNumber);


private:

	BYTE m_This[256];	// 4
	BYTE m_Flag[256];	// 104
	BYTE m_MapNumber[256];	// 204
	BYTE m_Sx[256];	// 304
	BYTE m_Sy[256];	// 404
	BYTE m_Ex[256];	// 504
	BYTE m_Ey[256];	// 604
	BYTE m_TargetGate[256];	// 704
	BYTE m_Dir[256];	// 804
	BYTE m_Level[256];	// 904
};

extern CGate gGateC;

#endif