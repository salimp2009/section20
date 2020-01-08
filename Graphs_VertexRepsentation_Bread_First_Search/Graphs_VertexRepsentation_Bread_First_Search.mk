##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Graphs_VertexRepsentation_Bread_First_Search
ConfigurationName      :=Debug
WorkspacePath          :=/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20
ProjectPath            :=/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graphs_VertexRepsentation_Bread_First_Search
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=SALIM PAMUKCU
Date                   :=11/06/2019
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
ObjectsFileList        :="Graphs_VertexRepsentation_Bread_First_Search.txt"
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
CXXFLAGS := -pg -O0 -std=c++17 -g -O0 -std=c++17 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/private/var/folders/99/l41x9fx50gx698158t8dm4440000gn/T/AppTranslocation/E5C99A94-AC21-4865-BD68-220594266E72/d/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/Vertex.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/BreadFirstSearch.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/Vertex.cpp$(ObjectSuffix): Vertex.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graphs_VertexRepsentation_Bread_First_Search/Vertex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Vertex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vertex.cpp$(PreprocessSuffix): Vertex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vertex.cpp$(PreprocessSuffix) Vertex.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graphs_VertexRepsentation_Bread_First_Search/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/BreadFirstSearch.cpp$(ObjectSuffix): BreadFirstSearch.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section20/Graphs_VertexRepsentation_Bread_First_Search/BreadFirstSearch.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BreadFirstSearch.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BreadFirstSearch.cpp$(PreprocessSuffix): BreadFirstSearch.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BreadFirstSearch.cpp$(PreprocessSuffix) BreadFirstSearch.cpp

##
## Clean
##
clean:
	$(RM) -r ./Debug/


