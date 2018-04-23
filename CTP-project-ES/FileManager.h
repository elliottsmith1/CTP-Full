#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

class FileManager
{
public:
	bool iterateFile(std::string fileName, std::function<void(const std::string &)> callback);

	std::vector<float*> LoadBehaviour(std::string fileName);

private:
	bool IsNumber(const std::string& s);

	std::vector<std::vector<float>> behaviours;

};