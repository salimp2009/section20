##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Shapes_Exercise
ConfigurationName      :=Debug
WorkspacePath          :=/Users/salimp/Documents/cplusplus/CPPWorkspace/Section19
ProjectPath            :=/Users/salimp/Documents/cplusplus/CPPWorkspace/Section19/Shapes_Exercise
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=SALIM PAMUKCU
Date                   :=27/03/2019
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
ObjectsFileList        :="Shapes_Exercise.txt"
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
CXXFLAGS := -std=c++17 -std=c++14 -Wall -g -O0 -std=c++17 -std=c++14 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/private/var/folders/99/l41x9fx50gx698158t8dm4440000gn/T/AppTranslocation/E5C99A94-AC21-4865-BD68-220594266E72/d/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/Shapes.cpp$(ObjectSuffix) $(IntermediateDirectory)/Triangle.cpp$(ObjectSuffix) $(IntermediateDirectory)/Vector3.cpp$(ObjectSuffix) $(IntermediateDirectory)/Shapes_Utility.cpp$(ObjectSuffix) $(IntermediateDirectory)/Circle.cpp$(ObjectSuffix) $(IntermediateDirectory)/I_Draw.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/Shapes.cpp$(ObjectSuffix): Shapes.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section19/Shapes_Exercise/Shapes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Shapes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Shapes.cpp$(PreprocessSuffix): Shapes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Shapes.cpp$(PreprocessSuffix) Shapes.cpp

$(IntermediateDirectory)/Triangle.cpp$(ObjectSuffix): Triangle.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section19/Shapes_Exercise/Triangle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Triangle.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Triangle.cpp$(PreprocessSuffix): Triangle.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Triangle.cpp$(PreprocessSuffix) Triangle.cpp

$(IntermediateDirectory)/Vector3.cpp$(ObjectSuffix): Vector3.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section19/Shapes_Exercise/Vector3.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Vector3.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vector3.cpp$(PreprocessSuffix): Vector3.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vector3.cpp$(PreprocessSuffix) Vector3.cpp

$(IntermediateDirectory)/Shapes_Utility.cpp$(ObjectSuffix): Shapes_Utility.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section19/Shapes_Exercise/Shapes_Utility.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Shapes_Utility.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Shapes_Utility.cpp$(PreprocessSuffix): Shapes_Utility.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Shapes_Utility.cpp$(PreprocessSuffix) Shapes_Utility.cpp

$(IntermediateDirectory)/Circle.cpp$(ObjectSuffix): Circle.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section19/Shapes_Exercise/Circle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Circle.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Circle.cpp$(PreprocessSuffix): Circle.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Circle.cpp$(PreprocessSuffix) Circle.cpp

$(IntermediateDirectory)/I_Draw.cpp$(ObjectSuffix): I_Draw.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section19/Shapes_Exercise/I_Draw.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/I_Draw.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/I_Draw.cpp$(PreprocessSuffix): I_Draw.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/I_Draw.cpp$(PreprocessSuffix) I_Draw.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/salimp/Documents/cplusplus/CPPWorkspace/Section19/Shapes_Exercise/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

##
## Clean
##
clean:
	$(RM) -r ./Debug/


