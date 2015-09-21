#pragma once

#include <atlstr.h>
#include <string>
#include <d3dx9math.h>

namespace debug {
	void Log(int i);
	void Log(double i);
	void Log(char* c);
	void Log(std::string s);
	void Log(D3DXVECTOR3 v);
}


