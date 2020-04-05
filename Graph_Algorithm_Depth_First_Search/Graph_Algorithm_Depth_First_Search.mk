##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Graph_Algorithm_Depth_First_Search
ConfigurationName      :=Debug
WorkspacePath          :=/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20
ProjectPath            :=/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graph_Algorithm_Depth_First_Search
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=SALIM PAMUKCU
Date                   :=21/03/2020
CodeLitePath           :="/Users/salimp/Library/Application Support/CodeLite"
LinkerName             :=clang++
SharedObjectLinkerName :=clang++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Graph_Algorithm_Depth_First_Search.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := clang++
CC       := clang
CXXFLAGS := -g -std=c++17 -Wall -g -O0 -std=c++17 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/private/var/folders/99/l41x9fx50gx698158t8dm4440000gn/T/AppTranslocation/E5C99A94-AC21-4865-BD68-220594266E72/d/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/DepthFirstSearch.cpp$(ObjectSuffix) $(IntermediateDirectory)/Vertex.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/DepthFirstSearch.cpp$(ObjectSuffix): DepthFirstSearch.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graph_Algorithm_Depth_First_Search/DepthFirstSearch.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DepthFirstSearch.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DepthFirstSearch.cpp$(PreprocessSuffix): DepthFirstSearch.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DepthFirstSearch.cpp$(PreprocessSuffix) DepthFirstSearch.cpp

$(IntermediateDirectory)/Vertex.cpp$(ObjectSuffix): Vertex.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graph_Algorithm_Depth_First_Search/Vertex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Vertex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vertex.cpp$(PreprocessSuffix): Vertex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vertex.cpp$(PreprocessSuffix) Vertex.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graph_Algorithm_Depth_First_Search/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

##
## Clean
##
clean:
	$(RM) -r ./Debug/


