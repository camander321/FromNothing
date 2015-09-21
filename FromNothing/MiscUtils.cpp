#include "MiscUtils.h"

void debug::Log(int i) {
	CString s;
	s.Format(_T("%d\n"), i);
	OutputDebugString(s);
}

void debug::Log(double i) {
	CString s;
	s.Format(_T("%f\n"), i);
	OutputDebugString(s);
}

void debug::Log(char* c) {
	CString s;
	s.Format(_T("%s\n"), c);
	OutputDebugString(s);
}

void debug::Log(std::string c)
{
	Log((char*)c.c_str());
}

void debug::Log(D3DXVECTOR3 v)
{
	CString s;
	s.Format(_T("%f, %f, %f\n"), v.x, v.y, v.z);
	OutputDebugString(s);
}


