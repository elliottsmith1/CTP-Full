#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

class FileManager
{
public:
	bool iterateFile(std::string fileName, std::function<void(const std::string &)> callback);	//read through file

	float* LoadBehaviour(std::string fileName);	//load FSM

private:
	bool IsNumber(const std::string& s);	//check if line is a number
};