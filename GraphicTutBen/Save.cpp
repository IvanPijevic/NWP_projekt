#include "Save.h"

Save::Save()
{}

Save::~Save()
{}

void Save::createSaveFile()
{
	std::ofstream outfile("Save.txt");

	

	outfile.close();
}