#include <iostream>
#include <map>
#include <ctime>
#include <sstream>
#include <iterator>
#include <bitset>
#include "TFile.h"
#include "TChain.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "MJVetoEvent.hh"
#include "MJTRun.hh"
#include "GATDataSet.hh"
#include "GATChannelSelectionInfo.hh"
#include "GATDetInfoProcessor.hh"

using namespace std;
using namespace MJDB;

int main(int argc, char** argv)
{
  if (argc < 5) {
		cout << "Usage: ./runtime partNum runRank firstRun lastRun\n"
         << "    partNum = P3LQK, P3KJR, P3LQG, etc.\n"
         << "    runRank = gold, silver, bronze, etc.\n"
		     << "    Ex.1: ./runtime P3LTP silver 25672 32930 \n";

		return 1;
	}
 
  string part = argv[1];
  string rank = argv[2];
  int firstRun = stoi(argv[3]);
  int lastRun = stoi(argv[4]);
  bool docs=true;
  string fullView = "";
  fullView = Form("run_rank?key=[\"%s\",\"%s\"]",part.c_str(),rank.c_str());

  // Access DB
  const string dbString = "mjd_run_database";
  const string dbServer = "mjdb.phy.ornl.gov";
  MJDatabase runDB(&dbString, &dbServer);
  runDB.SetServerScheme("https");
  MJDocument runDoc;
  runDoc.Get_View(runDB,"dbApp",fullView,docs);
  string errorMessage;
  if (runDB.GetDBStatus(errorMessage)!=0){
    cout << "Failed to get document.  cURL error: " << runDB.GetDBStatus(errorMessage)
         << " Message: " << errorMessage << endl;
    return 0;
  }
  int nDocs = runDoc["rows"].Length();
  cout << "Found " << nDocs << " run records.\n";
  cout << runDB.GetURL() << endl; // you can check this in a browser
  // runDoc.Dump();
  // Loop over the document

  double blindBG=0;
  double openBG=0;
  double cal=0;

  for (int i = 0; i < nDocs; i++)
  {
    // int run = atoi(runDoc["rows"][i]["value"].Value().AsString().c_str());
    // runDoc["rows"][i].Dump(); // dump just one document
    int runInDoc = atoi(runDoc["rows"][i]["doc"]["RunNumber"].Value().AsString().c_str());
    bool isOpen = ( runDoc["rows"][i]["doc"]["access"].Value().AsString() == "open" );
    int runBits = atoi( runDoc["rows"][i]["doc"]["orca_run_bits"].Value().AsString().c_str() );
    // int runQuality = atoi( runDoc["rows"][i]["doc"]["RunQualityVal"].Value().AsString().c_str() );
    // string runRank = runDoc["rows"][i]["doc"]["RunRank"].Value().AsString();  // gold, silver, etc
    // string timestamp = runDoc["rows"][i]["doc"]["timestamp"].Value().AsString();
    // int stopTime = atoi( runDoc["rows"][i]["doc"]["time"].Value().AsString().c_str() );
    double runElapsedTime = stod( runDoc["rows"][i]["doc"]["ElapsedTime"].Value().AsString() );

    bitset<32> b(runBits);

    //      if (!isOpen && runInDoc >= 29989 && runInDoc <= 31899 && !b[3] && !b[4]) {
    if (runInDoc >= firstRun && runInDoc <= lastRun) {
      if (runElapsedTime > 3605) {      
	cout<< "Run greater than 3605 seconds! \t Run: " << runInDoc << "\t Runtime: "
	    << runElapsedTime << "\n";
      }
      if (!isOpen) {
	if (b[3] || b[4]) {
	  cout << "Blind calibration?? \n";
	}
	else {
	  blindBG += runElapsedTime;
	}
      }
      else {
	if (b[3] || b[4]) {
	  cal += runElapsedTime;
	}
	else {
	  openBG += runElapsedTime;
	}
      }
    }
  }
  cout << "Blind background: " << blindBG/86400 << " days \n";
  cout << "Open background: " << openBG/86400 << " days \n";
  cout << "Calibrations: " << cal/86400 << " days \n";
  return 0;
}
