// Misc playground for practicing stuff
// Use with: g++ -std=c++11 -o misc misc.cpp ----> ./misc fileName

#include <iostream>
#include <algorithm>
#include <vector>
#include <typeinfo>
#include <string>

#include <random>
#include <chrono>

#include "/home/afiqaize/Downloads/eft/rivet/DataCounter.h"

int main() {
  std::map<std::string, std::vector<double> > mv_bin;
  mv_bin["cHel"] = {-1., 0., 1.};
  mv_bin["ckk"] = {-1., -0., 1.};
  mv_bin["cnn"] = {-1., -0., 1.};
  mv_bin["crr"] = {-1., -0., 1.};

  DataCounter<double> dat("test", mv_bin, true);
  //dat.printBins();

  std::map<std::string, double> m_var;
  m_var["cHel"] = 0.;
  m_var["ckk"] = 0.;
  m_var["cnn"] = 0.;
  m_var["crr"] = 0.;

  std::mt19937_64 rng;
  // initialize the random number generator with time-dependent seed
  uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
  rng.seed(ss);
  // initialize a uniform distribution between 0 and 1
  std::uniform_real_distribution<double> uni_m1_p1(-1., 1.);
  std::uniform_real_distribution<double> uni_0_p1(0., 1.);
  // ready to generate random numbers
  for (int i = 0; i < 100000; i++) {
    m_var["cHel"] = uni_m1_p1(rng);
    m_var["ckk"] = uni_m1_p1(rng);
    m_var["cnn"] = uni_m1_p1(rng);
    m_var["crr"] = uni_m1_p1(rng);
    double weight = uni_0_p1(rng);

    dat.fillDataMap(m_var, weight);
  }

  dat.printDataMap();

  for (int i = 0; i < 100000; i++) {
    m_var["cHel"] = uni_m1_p1(rng);
    m_var["ckk"] = uni_m1_p1(rng);
    m_var["cnn"] = uni_m1_p1(rng);
    m_var["crr"] = uni_m1_p1(rng);
    double weight = uni_0_p1(rng);

    dat.fillDataMap(m_var, weight);
  }

  std::cout << std::endl;
  dat.printDataMap();

  return 0;
}


