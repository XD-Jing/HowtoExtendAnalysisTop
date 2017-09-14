#ifndef HOWTOEXTENDANALYSISTOP_HOWTOEXTENDANALYSISTOPLOADER_H
#define HOWTOEXTENDANALYSISTOP_HOWTOEXTENDANALYSISTOPLOADER_H

#include "TopEventSelectionTools/ToolLoaderBase.h"

/**
 * The name of this class has to be $packagename + Loader 
 * 
 * So if your package is called foo, you'll need a fooLoader class
 * 
 * This allows us to write custom event selection tools 
 */

namespace top{
  
  class HowtoExtendAnalysisTopLoader : public ToolLoaderBase {
    public:
      top::EventSelectorBase* initTool(const std::string& name, const std::string& line, TFile* outputFile, std::shared_ptr<top::TopConfig> config,EL::Worker* wk = nullptr);

      ClassDef(top::HowtoExtendAnalysisTopLoader, 0)      
  };
}

#endif
