//
//  testAnalScript.cpp
//  
//
//  Created by Jamin on 8/18/16.
//
//

#include <stdio.h>
#include <iostream>
//#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <stdlib.h>

#include "TChain.h"
#include "TFile.h"

#include "GATDataSet.hh"
#include <string>

int main()
{
  std::cout << "Begin script..." << std::endl;
    
  // Data file
  std::string dataFile;
    
  // Directory where data is found.
  std::string dataPath("/global/project/projectdirs/majorana/users/jrager/AzScan/data/");
    
  // Load the set of run files given in command line.
  //std::ofstream ofs;
  //ofs.open ("checkOrder.csv", std::ofstream::out | std::ofstream::app);
    
  //Loop over files
  UInt_t runNumb;
  UInt_t z = 0;
  // runNumb < 194
  for (runNumb = 0; runNumb < 194; runNumb+=2, z+=2) {
    std::cout << "runNumb = "  << runNumb << std::endl;
    std::cout << "z = "  << z << std::endl;
    //ofs << "runNumb = " << runNumb << "\n";
    //ofs << "z = " << z << "\n";
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = dataPath + std::string("angle") + buffer + ".root";
    std::cout<<"Opening file"<<dataFile<<std::endl;
    TFile f2(dataFile.c_str());
    TChain *chain = new TChain("mjdTree");
    chain->Add(dataFile.c_str());
        
    // Event loop!
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
            
      if(eventNum % 10000 == 1) {
	//ofs << "eventNum =" << eventNum << "\n";
	std::cout << "eventNum ="  << eventNum-1 << std::endl;
      }
            
    } // for event loop
    f2.Close();
    //std::cout << "Finished Event Loop." << std::endl;
  }
  //std::cout << "Finished run loop." << std::endl;
    
  std::cout << "Done!" << std::endl;
    
  return 0;
}
