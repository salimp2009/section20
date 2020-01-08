##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Graphs_Depth_First_Search_Vertex
ConfigurationName      :=Debug
WorkspacePath          :=/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20
ProjectPath            :=/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graphs_Depth_of_Search_First_Vertex
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=SALIM PAMUKCU
Date                   :=13/06/2019
CodeLitePath           :="/Users/salimp/Library/Application Support/CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
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
ObjectsFileList        :="Graphs_Depth_First_Search_Vertex.txt"
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
CXX      := g++
CC       := gcc
CXXFLAGS := -g -O0 -std=c++17 -Wall -g -O0 -std=c++17 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/private/var/folders/99/l41x9fx50gx698158t8dm4440000gn/T/AppTranslocation/E5C99A94-AC21-4865-BD68-220594266E72/d/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Vertex.cpp$(ObjectSuffix) $(IntermediateDirectory)/DepthFirstSearch.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graphs_Depth_of_Search_First_Vertex/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/Vertex.cpp$(ObjectSuffix): Vertex.cpp $(IntermediateDirectory)/Vertex.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graphs_Depth_of_Search_First_Vertex/Vertex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Vertex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vertex.cpp$(DependSuffix): Vertex.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Vertex.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Vertex.cpp$(DependSuffix) -MM Vertex.cpp

$(IntermediateDirectory)/Vertex.cpp$(PreprocessSuffix): Vertex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vertex.cpp$(PreprocessSuffix) Vertex.cpp

$(IntermediateDirectory)/DepthFirstSearch.cpp$(ObjectSuffix): DepthFirstSearch.cpp $(IntermediateDirectory)/DepthFirstSearch.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graphs_Depth_of_Search_First_Vertex/DepthFirstSearch.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DepthFirstSearch.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DepthFirstSearch.cpp$(DependSuffix): DepthFirstSearch.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DepthFirstSearch.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DepthFirstSearch.cpp$(DependSuffix) -MM DepthFirstSearch.cpp

$(IntermediateDirectory)/DepthFirstSearch.cpp$(PreprocessSuffix): DepthFirstSearch.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DepthFirstSearch.cpp$(PreprocessSuffix) DepthFirstSearch.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


