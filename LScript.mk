##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=LScript
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM
ProjectPath            :=/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Abthahi Ahmed Rifat
Date                   :=28/11/24
CodeLitePath           :=/home/abthahi/.codelite
LinkerName             :=/usr/bin/g++-11
SharedObjectLinkerName :=/usr/bin/g++-11 -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=$(IntermediateDirectory)
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="LScript.txt"
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
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++-11
CC       := /usr/bin/gcc-11
CXXFLAGS :=  -gdwarf-2 -O0 -Wall $(Preprocessors)
CFLAGS   :=  -gdwarf-2 -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/includes_Parser.cpp$(ObjectSuffix) $(IntermediateDirectory)/includes_Tokenizer.cpp$(ObjectSuffix) $(IntermediateDirectory)/includes_Interpreter.cpp$(ObjectSuffix) $(IntermediateDirectory)/includes_Arithmetic.cpp$(ObjectSuffix) $(IntermediateDirectory)/includes_Condition.cpp$(ObjectSuffix) $(IntermediateDirectory)/includes_ErrorLog.cpp$(ObjectSuffix) $(IntermediateDirectory)/includes_global.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/includes_Types.cpp$(ObjectSuffix) $(IntermediateDirectory)/includes_Variables.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/includes_Functions.cpp$(ObjectSuffix) 



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
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)


$(IntermediateDirectory)/.d:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/includes_Parser.cpp$(ObjectSuffix): includes/Parser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/includes_Parser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/includes_Parser.cpp$(DependSuffix) -MM includes/Parser.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/includes/Parser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/includes_Parser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/includes_Parser.cpp$(PreprocessSuffix): includes/Parser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/includes_Parser.cpp$(PreprocessSuffix) includes/Parser.cpp

$(IntermediateDirectory)/includes_Tokenizer.cpp$(ObjectSuffix): includes/Tokenizer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/includes_Tokenizer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/includes_Tokenizer.cpp$(DependSuffix) -MM includes/Tokenizer.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/includes/Tokenizer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/includes_Tokenizer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/includes_Tokenizer.cpp$(PreprocessSuffix): includes/Tokenizer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/includes_Tokenizer.cpp$(PreprocessSuffix) includes/Tokenizer.cpp

$(IntermediateDirectory)/includes_Interpreter.cpp$(ObjectSuffix): includes/Interpreter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/includes_Interpreter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/includes_Interpreter.cpp$(DependSuffix) -MM includes/Interpreter.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/includes/Interpreter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/includes_Interpreter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/includes_Interpreter.cpp$(PreprocessSuffix): includes/Interpreter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/includes_Interpreter.cpp$(PreprocessSuffix) includes/Interpreter.cpp

$(IntermediateDirectory)/includes_Arithmetic.cpp$(ObjectSuffix): includes/Arithmetic.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/includes_Arithmetic.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/includes_Arithmetic.cpp$(DependSuffix) -MM includes/Arithmetic.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/includes/Arithmetic.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/includes_Arithmetic.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/includes_Arithmetic.cpp$(PreprocessSuffix): includes/Arithmetic.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/includes_Arithmetic.cpp$(PreprocessSuffix) includes/Arithmetic.cpp

$(IntermediateDirectory)/includes_Condition.cpp$(ObjectSuffix): includes/Condition.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/includes_Condition.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/includes_Condition.cpp$(DependSuffix) -MM includes/Condition.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/includes/Condition.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/includes_Condition.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/includes_Condition.cpp$(PreprocessSuffix): includes/Condition.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/includes_Condition.cpp$(PreprocessSuffix) includes/Condition.cpp

$(IntermediateDirectory)/includes_ErrorLog.cpp$(ObjectSuffix): includes/ErrorLog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/includes_ErrorLog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/includes_ErrorLog.cpp$(DependSuffix) -MM includes/ErrorLog.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/includes/ErrorLog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/includes_ErrorLog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/includes_ErrorLog.cpp$(PreprocessSuffix): includes/ErrorLog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/includes_ErrorLog.cpp$(PreprocessSuffix) includes/ErrorLog.cpp

$(IntermediateDirectory)/includes_global.cpp$(ObjectSuffix): includes/global.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/includes_global.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/includes_global.cpp$(DependSuffix) -MM includes/global.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/includes/global.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/includes_global.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/includes_global.cpp$(PreprocessSuffix): includes/global.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/includes_global.cpp$(PreprocessSuffix) includes/global.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/includes_Types.cpp$(ObjectSuffix): includes/Types.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/includes_Types.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/includes_Types.cpp$(DependSuffix) -MM includes/Types.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/includes/Types.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/includes_Types.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/includes_Types.cpp$(PreprocessSuffix): includes/Types.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/includes_Types.cpp$(PreprocessSuffix) includes/Types.cpp

$(IntermediateDirectory)/includes_Variables.cpp$(ObjectSuffix): includes/Variables.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/includes_Variables.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/includes_Variables.cpp$(DependSuffix) -MM includes/Variables.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/includes/Variables.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/includes_Variables.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/includes_Variables.cpp$(PreprocessSuffix): includes/Variables.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/includes_Variables.cpp$(PreprocessSuffix) includes/Variables.cpp

$(IntermediateDirectory)/includes_Functions.cpp$(ObjectSuffix): includes/Functions.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/includes_Functions.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/includes_Functions.cpp$(DependSuffix) -MM includes/Functions.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/mnt/sda/Development/Projects/Cpp/CPP_PROGRAM/LScript/includes/Functions.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/includes_Functions.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/includes_Functions.cpp$(PreprocessSuffix): includes/Functions.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/includes_Functions.cpp$(PreprocessSuffix) includes/Functions.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


