#include "HowtoExtendAnalysisTop/HowtoExtendAnalysisTopLoader.h"

#include "HowtoExtendAnalysisTop/EvenEventNumberSelector.h"
#include "TopConfiguration/TopConfig.h"

#include <iostream>
#include "TFile.h"

namespace top{
  top::EventSelectorBase* HowtoExtendAnalysisTopLoader::initTool(const std::string& /*name*/, const std::string& line, TFile* /*outputFile*/, std::shared_ptr<top::TopConfig> /*config*/,EL::Worker* /*wk*/)
  {
    //get the first bit of the string and store it in toolname
    std::istringstream iss(line);
    std::string toolname;
    getline(iss, toolname, ' ');

    //any parameters?
    std::string param;
    if (line.size() > toolname.size())
        param = line.substr(toolname.size() + 1);

    if (toolname == "EVEN")
        return new top::EvenEventNumberSelector();  
    //else if (toolname.find("OTHER_TOOL") == 0)
    //  return OtherToolThatYouInvented()    
    
    return nullptr;      
  }
}
