#pragma once
#include <string>
#include <map>

class InputMap
{
public:
	InputMap();

	void init();
	void getInput();
	bool getAction(std::string action);

private:
	void addKeyboardMaping(std::string action);
	std::map<std::string, bool> input;

};

