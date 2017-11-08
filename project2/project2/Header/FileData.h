#ifndef __FILEDATA_H__
#define __FILEDATA_H__

class CFileData
{
private:
	char *m_Name;
	int m_Num;
public:

	void SetFileData(char *name, const int& num);
	char*	GetName(){ return m_Name; }
	int		GetNum(){ return m_Num; }
};


#endif