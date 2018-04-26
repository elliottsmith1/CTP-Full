#include "FileManager.h"

/////////////////////////////////////////////////////////////////////////////
// Tutorial used for this class can be found at: ////////////////////////////
// thispointer.com/c-how-to-read-a-file-line-by-line-into-a-vector/ /////////
/////////////////////////////////////////////////////////////////////////////


bool FileManager::iterateFile(std::string fileName, std::function<void(const std::string&)> callback)
{
	// Open the File
	std::ifstream in(fileName.c_str());
 
	// Check if object is valid
	if(!in)
	{
		std::cerr << "Cannot open the File : "<<fileName<<std::endl;
		return false;
	}
 
	std::string str;
	// Read the next line from File untill it reaches the end.
	while (std::getline(in, str))
	{
		// Call the given callback
		callback(str);
	}
	//Close The File
	in.close();
	return true;
}

float* FileManager::LoadBehaviour(std::string fileName)
{
	//std::vector<std::string> behaviour;
	std::vector<float> behaviour;

	//Call given lambda function for each line in file
	bool res = iterateFile(fileName.c_str(), [&](const std::string & str) {

		if (IsNumber(str))
		{
			// Add to vector
			float num = std::atof(str.c_str());
			behaviour.push_back(num);
		}

		//if not a number then interpret the line into float
		else
		{
			float num;

			if (str == "ADD_I32")
			{
				num = 1;
			}
			else if (str == "SUB_I32")
			{
				num = 2;
			}
			else if (str == "MUL_I32")
			{
				num = 3;
			}
			else if (str == "LT_I32")
			{
				num = 4;
			}
			else if (str == "GT_I32")
			{
				num = 5;
			}
			else if (str == "EQ_I32")
			{
				num = 6;
			}
			else if (str == "JMP")
			{
				num = 7;
			}
			else if (str == "JMPT")
			{
				num = 8;
			}
			else if (str == "JMPF")
			{
				num = 9;
			}
			else if (str == "CONST_I32")
			{
				num = 10;
			}
			else if (str == "LOAD")
			{
				num = 11;
			}
			else if (str == "GLOAD")
			{
				num = 12;
			}
			else if (str == "S_LOAD")
			{
				num = 13;
			}
			else if (str == "S_STORE")
			{
				num = 14;
			}
			else if (str == "STORE")
			{
				num = 15;
			}
			else if (str == "GSTORE")
			{
				num = 16;
			}
			else if (str == "PRINT")
			{
				num = 17;
			}
			else if (str == "POP")
			{
				num = 18;
			}
			else if (str == "HALT")
			{
				num = 19;
			}
			else if (str == "CALL")
			{
				num = 20;
			}
			else if (str == "RET")
			{
				num = 21;
			}
			else if (str == "PAUSE")
			{
				num = 22;
			}
			else if (str == "STAT_LOAD")
			{
				num = 23;
			}
			else if (str == "STAT_SAVE")
			{
				num = 24;
			}
			else if (str == "RAND")
			{
				num = 25;
			}
			else if (str == "CHECK_NEAR")
			{
				num = 26;
			}
			else if (str == "GET_X_POS")
			{
				num = 27;
			}
			else if (str == "GET_Y_POS")
			{
				num = 28;
			}
			else if (str == "CHECK_COLOUR")
			{
				num = 29;
			}
			else if (str == "CHANGE_COLOUR")
			{
				num = 30;
			}

			behaviour.push_back(num);
			//std::cout << num << "\n";
		}
	});

	float* nums = new float[behaviour.size()];

	for (int i = 0; i < behaviour.size(); i++)
	{
		nums[i] = behaviour[i];
	}

	//return FSM as float array
	return nums;
}

bool FileManager::IsNumber(const std::string & s)
{
	//used to check if line in file is a number
	try
	{
		std::stod(s);
	}
	catch (...)
	{
		return false;
	}
	return true;
}


