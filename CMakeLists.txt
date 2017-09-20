
# Declare the name of this package:
atlas_subdir( HowtoExtendAnalysisTop None )

# This package depends on other packages:
atlas_depends_on_subdirs( PUBLIC
    TopAnalysis
    TopEvent
    TopConfiguration
    TopEventSelectionTools
    TopObjectSelectionTools
    #AsgTools
    #MuonSelectorTools
    #TopCPTools
    #TopCorrections
    TopParticleLevel
    #TopPartons
    #TopSystematicObjectMaker
    #TopFakes
    #TopDataPreparation
    #TopHLUpgrade )
    )

# This package uses ROOT:
find_package( ROOT REQUIRED COMPONENTS Core Gpad Tree Hist RIO MathCore Graf )

# Custom definitions needed for this package:
add_definitions( -g )

# Generate a CINT dictionary source file:
atlas_add_root_dictionary( HowtoExtendAnalysisTop _cintDictSource
    ROOT_HEADERS Root/LinkDef.h
    EXTERNAL_PACKAGES ROOT )

# Build a library that other components can link against:
atlas_add_library( HowtoExtendAnalysisTop Root/*.cxx Root/*.h Root/*.icc
    HowtoExtendAnalysisTop/*.h HowtoExtendAnalysisTop/*.icc HowtoExtendAnalysisTop/*/*.h
    HowtoExtendAnalysisTop/*/*.icc ${_cintDictSource} 
    PUBLIC_HEADERS HowtoExtendAnalysisTop
    LINK_LIBRARIES TopAnalysis
    #TopCPTools
    #TopCorrections
    TopEvent
    TopConfiguration
    TopEventSelectionTools
    TopObjectSelectionTools
    #AsgTools
    #MuonSelectorTools
    TopParticleLevel
    #TopPartons
    #TopSystematicObjectMaker
    #TopFakes
    #TopDataPreparation
    #TopHLUpgrade
    ${ROOT_LIBRARIES}
    INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} )

# Install data files from the package:
#atlas_install_data( share/* )

# Install user scripts
#atlas_install_scripts( scripts/*.py )

