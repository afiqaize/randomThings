#include "DataCounter.h"

template <typename T> 
DataCounter<T>::DataCounter(const std::string &name_, const std::map<std::string, std::vector<T> > &mv_bin_, const bool doSumWgt2_):
  name(name_),
  mv_bin(mv_bin_),
  doSumWgt2(doSumWgt2_)
{
  bool isValid = true;
  std::for_each(mv_bin.begin(), mv_bin.end(), [&](const std::pair<std::string, std::vector<T> > &pv_bin) {
      isValid = isValid and pv_bin.second.size() > 1 and std::is_sorted(pv_bin.second.begin(), pv_bin.second.end());
    });

  if (!isValid) {
    std::cerr << "Error: DataCounter was constructed with an invalid phase space grid!\n" << std::endl;
    exit(339);
  }

  this->createBins(mv_bin.begin(), "");
  this->createDataMap();
  doStateUpdate = true;
}



template <typename T> void DataCounter<T>::printBins()
{
  std::cout << "### =================================== ###" << std::endl;
  std::cout << "Bins for DataCounter object with name " << name << " are:" << std::endl;
  std::for_each(s_binStr.begin(), s_binStr.end(), [](const std::string &bin) {std::cout << bin << std::endl;});
  std::cout << "### =================================== ###" << std::endl;
}



template <typename T> void DataCounter<T>::fillDataMap(const std::map<std::string, T> &m_var, const double weight)
{
  doStateUpdate = true;

  const std::string binStr = this->findBin(m_var);
  if (s_binStr.count(binStr)) {
    ++m_sumEnt[binStr];
    m_sumWgt[binStr] +=  weight;

    if (doSumWgt2)
      m_sumWgt2[binStr] += (weight * weight);
  }
}



template <typename T> const std::map<std::string, Data>* DataCounter<T>::getDataMap()
{
  if (doStateUpdate)
    this->updateDataMap();

  return &m_data;
}



template <typename T> const int DataCounter<T>::getEntries()
{
  if (doStateUpdate)
    this->updateDataMap();

  int entries = 0;
  std::for_each(s_binStr.begin(), s_binStr.end(), [&](const std::string &bin) {
      entries += m_data.at(bin).entry;
    });

  return entries;
}



template <typename T> const double DataCounter<T>::getIntegral()
{
  if (doStateUpdate)
    this->updateDataMap();

  double integral = 0;
  std::for_each(s_binStr.begin(), s_binStr.end(), [&](const std::string &bin) {
      integral += m_data.at(bin).value;
    });

  return integral;
}



template <typename T> void DataCounter<T>::printDataMap()
{
  if (doStateUpdate)
    this->updateDataMap();

  std::cout << "### =================================== ###" << std::endl;
  std::cout << "DataCounter object with name " << name << 
    " has entries " << this->getEntries() << " and integral " << this->getIntegral() << std::endl;

  std::for_each(s_binStr.begin(), s_binStr.end(), [&](const std::string &bin) {
      std::cout << bin << ": entries " << m_data.at(bin).entry << 
        ", content " << m_data.at(bin).value << " +- " << m_data.at(bin).error << std::endl;
    });

  std::cout << "### =================================== ###" << std::endl;
}



template <typename T> 
void DataCounter<T>::createBins(typename std::map<std::string, std::vector<T> >::const_iterator iv_bin, const std::string &iniStr)
{
  for (unsigned iB = 1; iB < iv_bin->second.size(); ++iB) {
    std::string varStr = iv_bin->first + "_" + std::to_string(iB);
    std::string binStr = (iniStr == "") ? varStr : iniStr + "--" + varStr;

    // terminating condition
    if (std::next(iv_bin) == mv_bin.end())
      s_binStr.insert(binStr);
    else
      this->createBins(std::next(iv_bin), binStr);
  }
}



template <typename T> void DataCounter<T>::createDataMap()
{
  std::for_each(s_binStr.begin(), s_binStr.end(), [&](const std::string &bin) {
      m_sumEnt[bin] = 0;
      m_sumWgt[bin] = 0.;

      if (doSumWgt2)
        m_sumWgt2[bin] = 0.;
    });
}



template <typename T> void DataCounter<T>::updateDataMap()
{
  doStateUpdate = false;
  std::for_each(s_binStr.begin(), s_binStr.end(), [&](const std::string &bin) {
      const int ent = m_sumEnt[bin];
      const double val = m_sumWgt[bin], err = (doSumWgt2) ? std::sqrt(m_sumWgt2[bin]) : std::sqrt(m_sumWgt[bin]);

      m_data[bin] = Data(ent, val, err);
    });
}



template <typename T> const std::string DataCounter<T>::findBin(const std::map<std::string, T> &m_var)
{
  std::string binStr = "";
  for (typename std::map<std::string, T>::const_iterator i_var = m_var.begin(); i_var != m_var.end(); ++i_var) {
    // find the first element that isnt greater than var value
    auto iB = std::lower_bound( mv_bin.at(i_var->first).begin(), mv_bin.at(i_var->first).end(), i_var->second );

    // create bin string base on bin index
    std::string varStr = i_var->first + "_" + std::to_string( std::distance(mv_bin.at(i_var->first).begin(), iB) );

    // merge with bin string of other var
    binStr = (binStr == "") ? varStr : binStr + "--" + varStr;
  }

  return binStr;
}



/// templates with which the class is to be used (other numeric types can be added at a whim)
template class DataCounter<int>;
template class DataCounter<float>;
template class DataCounter<double>;
