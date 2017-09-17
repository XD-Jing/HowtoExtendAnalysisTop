# HowtoExtendAnalysisTop
```bash
mkdir YourDir
cp -r HowtoExtendAnalysisTop .
rcSetup Top,2.4.32
rc find_packages
rc compile
top-xaod HowtoExtendAnalysisTop/share/dil-cuts_official.txt HowtoExtendAnalysisTop/share/smdy.txt
