#include "StdAfx.h"
#include "dirpath.h"

CDirPath::CDirPath()
{

}

CDirPath::~CDirPath()
{

}

void CDirPath::SetFirstPath(char *dir_path)
{
	strcpy(this->m_path ,dir_path);
}

char *CDirPath::GetNewPath(char *npath)
{
	strcpy(this->m_newpath, this->m_path);	// NULL
	strcat(this->m_newpath, npath);	// Derived Path
	return this->m_newpath;
}