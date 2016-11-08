// Trigger result log reader
// Use with: g++ -o log log.cpp ----> ./log fileName

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {

  if(argc < 2) {

    cout << "Need an input file..." << endl;
    return 0;

  }

  //char fileName[1000];

  //cout << "Insert target file name." << endl;
  //cin >> fileName;

  //ifstream infile(fileName);
  ifstream infile(argv[1]);
  float a1, a2, a3, a4, a5, a6, pasSum = 0., totSum = 0.;
  int count = 0;
  string textline;
  const char *linest;

  for(int i = 0; i < 1000; i++) {

    a1 = 0.; a2 = 0.; a3 = 0.;
    a4 = 0.; a5 = 0.; a6 = 0.;

    getline(infile, textline); linest = textline.c_str();
    if (textline.find("TrigReport") != string::npos) {
 
      sscanf(linest, "%*s %f %f %f %f %f %f", &a1, &a2, &a3, &a4, &a5, &a6);
      //cout << a4 << endl;
      pasSum = pasSum + a4;
      totSum = totSum + a3;
      count++;

    }
  }

  cout << "Total passing event = " << (int) pasSum << endl;
  cout << "Total processed events = " << (int) totSum << endl;
  cout << "Total jobs = " << count << endl;

  return 0;

}
