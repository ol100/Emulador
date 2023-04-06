##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=prueba3
ConfigurationName      :=Debug
WorkspacePath          :=/home/javi/proyectos/prueba2/SDL2
ProjectPath            :=/home/javi/proyectos/prueba3
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=javi
Date                   :=11/03/21
CodeLitePath           :=/home/javi/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="prueba3.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)SDL2 $(LibrarySwitch)SDL2main $(LibrarySwitch)SDL2_ttf 
ArLibs                 :=  "SDL2" "SDL2main" "SDL2_ttf" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/lib/x86_64-linux-gnu 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/cpu.cpp$(ObjectSuffix) $(IntermediateDirectory)/ExtendedCPU.cpp$(ObjectSuffix) $(IntermediateDirectory)/memoria.cpp$(ObjectSuffix) $(IntermediateDirectory)/interruciones.cpp$(ObjectSuffix) $(IntermediateDirectory)/ppu.cpp$(ObjectSuffix) $(IntermediateDirectory)/graphics.cpp$(ObjectSuffix) 



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
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/javi/proyectos/prueba3/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/cpu.cpp$(ObjectSuffix): cpu.cpp $(IntermediateDirectory)/cpu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/javi/proyectos/prueba3/cpu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpu.cpp$(DependSuffix): cpu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/cpu.cpp$(DependSuffix) -MM cpu.cpp

$(IntermediateDirectory)/cpu.cpp$(PreprocessSuffix): cpu.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpu.cpp$(PreprocessSuffix) cpu.cpp

$(IntermediateDirectory)/ExtendedCPU.cpp$(ObjectSuffix): ExtendedCPU.cpp $(IntermediateDirectory)/ExtendedCPU.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/javi/proyectos/prueba3/ExtendedCPU.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ExtendedCPU.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ExtendedCPU.cpp$(DependSuffix): ExtendedCPU.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ExtendedCPU.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ExtendedCPU.cpp$(DependSuffix) -MM ExtendedCPU.cpp

$(IntermediateDirectory)/ExtendedCPU.cpp$(PreprocessSuffix): ExtendedCPU.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ExtendedCPU.cpp$(PreprocessSuffix) ExtendedCPU.cpp

$(IntermediateDirectory)/memoria.cpp$(ObjectSuffix): memoria.cpp $(IntermediateDirectory)/memoria.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/javi/proyectos/prueba3/memoria.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/memoria.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/memoria.cpp$(DependSuffix): memoria.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/memoria.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/memoria.cpp$(DependSuffix) -MM memoria.cpp

$(IntermediateDirectory)/memoria.cpp$(PreprocessSuffix): memoria.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/memoria.cpp$(PreprocessSuffix) memoria.cpp

$(IntermediateDirectory)/interruciones.cpp$(ObjectSuffix): interruciones.cpp $(IntermediateDirectory)/interruciones.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/javi/proyectos/prueba3/interruciones.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/interruciones.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/interruciones.cpp$(DependSuffix): interruciones.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/interruciones.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/interruciones.cpp$(DependSuffix) -MM interruciones.cpp

$(IntermediateDirectory)/interruciones.cpp$(PreprocessSuffix): interruciones.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/interruciones.cpp$(PreprocessSuffix) interruciones.cpp

$(IntermediateDirectory)/ppu.cpp$(ObjectSuffix): ppu.cpp $(IntermediateDirectory)/ppu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/javi/proyectos/prueba3/ppu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ppu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ppu.cpp$(DependSuffix): ppu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ppu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ppu.cpp$(DependSuffix) -MM ppu.cpp

$(IntermediateDirectory)/ppu.cpp$(PreprocessSuffix): ppu.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ppu.cpp$(PreprocessSuffix) ppu.cpp

$(IntermediateDirectory)/graphics.cpp$(ObjectSuffix): graphics.cpp $(IntermediateDirectory)/graphics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/javi/proyectos/prueba3/graphics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/graphics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/graphics.cpp$(DependSuffix): graphics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/graphics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/graphics.cpp$(DependSuffix) -MM graphics.cpp

$(IntermediateDirectory)/graphics.cpp$(PreprocessSuffix): graphics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/graphics.cpp$(PreprocessSuffix) graphics.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


