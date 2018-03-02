#ifndef DataCounter_h
#define DataCounter_h

/// A simple class that keeps track of counts in N-dimensional phase space split into M-bins
/*** TO-DO list
 * Ensure proper statistics handling
 * Projections? Goodness-of-Fit? Ehh...
 ***/

#include <iostream>
#include <algorithm>
#include <memory>

#include <vector>
#include <map>
#include <set>
#include <string>

struct Data {
  int entry;
  double value, error;

  /// constructor
  Data() : entry(0), value(0.), error(0.) {}
  Data(const int ent, const double val, const double err) : entry(ent), value(val), error(err) {}
  Data(const Data& dat) : entry(dat.entry), value(dat.value), error(dat.error) {}
};

template <typename T> class DataCounter {
 public:
  /// constructor
  DataCounter(const std::string &name_, const std::map<std::string, std::vector<T> > &mv_bin_, const bool doSumWgt2_ = false);

  /// print all the bin labels
  void printBins();

  /// fill the data map
  void fillDataMap(const std::map<std::string, T> &m_var, const double weight = 1.);

  /// return the data as m[bin] = entry, value, error
  const std::map<std::string, Data>* getDataMap();

  /// get total entries
  const int getEntries();

  /// get integral = sum of values
  const double getIntegral();

  /// print all the bin labels and data content
  void printDataMap();

 private:

  /// parse the given m_bin into multiple bin labels
  void createBins(typename std::map<std::string, std::vector<T> >::const_iterator iv_bin, const std::string& iniStr);

  /// create the data map based on the defined binning
  void createDataMap();

  /// update the data map
  void updateDataMap();

  /// find the bins for a given map var-val
  const std::string findBin(const std::map<std::string, T> &m_var);

  std::string name;
  std::map<std::string, std::vector<T> > mv_bin;
  bool doSumWgt2, doStateUpdate;

  std::set<std::string> s_binStr;

  std::map<std::string, int> m_sumEnt;
  std::map<std::string, double> m_sumWgt;
  std::map<std::string, double> m_sumWgt2;
  std::map<std::string, Data> m_data;
};

#endif







