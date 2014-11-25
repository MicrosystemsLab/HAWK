#include "StdAfx.h"
#include "BasicExcel.hpp"

using namespace YExcel;

vector<double> lookUpDevice(const char* waferID, const char* deviceID)
{
	BasicExcel xls("Cantilever Inventory 97.xls");
	BasicExcelWorksheet* sheet = xls.GetWorksheet(waferID);
	BasicExcelCell* cell;
	
	//convert from const char* to string to concatenate:
	std::string cantID(waferID);
	cantID.append(deviceID);

	vector<double> specifications;

	if (sheet) {
		size_t maxRows = sheet->GetTotalRows();
		size_t maxCols = sheet->GetTotalCols();

		size_t r = 0;
		size_t deviceColumn = 1;	

		//find correct device column
		for (size_t c=1; c<maxCols; c++) {
			cell = sheet->Cell(r,c);
			
			if (cell->Type() == 5) { //make sure entry is a string.	
				std::string cantIDtest(cell->GetString());
				if(cantID.compare(cantIDtest)==0) { // compare strings
					deviceColumn = c;
					break;
				}
			}	
		}

		// if device column never changed, device not found, return error = -2
		if(deviceColumn == 1) {
			specifications.push_back(-2);
		} else {
			//report cantilever specs:
			//get frequency
			r = 38;
			cell = sheet->Cell(r,deviceColumn);
			double frequency = cell->GetDouble();
			//get stiffness
			r = 39;
			cell = sheet->Cell(r,deviceColumn);
			double stiffness = cell->GetDouble();
			//get sensitivity
			r = 42;
			cell = sheet->Cell(r,deviceColumn);
			double sensitivity = cell->GetDouble();
			//get p parameter
			r = 43;
			cell = sheet->Cell(r,deviceColumn);
			double pParameter = cell->GetDouble();
			//get i parameter
			r = 44;
			cell = sheet->Cell(r,deviceColumn);
			double iParameter = cell->GetDouble();
			// get d parameter
			r = 45;
			cell = sheet->Cell(r,deviceColumn);
			double dParameter = cell->GetDouble();

			//return specs
			specifications.push_back(frequency);
			specifications.push_back(stiffness);
			specifications.push_back(sensitivity);
			specifications.push_back(pParameter);
			specifications.push_back(iParameter);
			specifications.push_back(dParameter);
		}
		
	} else { // if can't load the sheet, return vector with first entry = -1.
		specifications.push_back(-1);
	}

	return specifications;
}



