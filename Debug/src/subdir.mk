################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Animation.cpp \
../src/Ataque.cpp \
../src/Audio.cpp \
../src/CaixaTexto.cpp \
../src/Camera.cpp \
../src/Cena.cpp \
../src/EstruturaItem.cpp \
../src/EstruturaStatus.cpp \
../src/GameObject.cpp \
../src/GrupoBatalha.cpp \
../src/GrupoCenario.cpp \
../src/GrupoPersonagens.cpp \
../src/GrupoViloes.cpp \
../src/InputManager.cpp \
../src/Item.cpp \
../src/Level.cpp \
../src/Personagem.cpp \
../src/PersonagemAtivo.cpp \
../src/PersonagemInativo.cpp \
../src/SDLBase.cpp \
../src/Sprite.cpp \
../src/StateBatalha.cpp \
../src/StateCasaRose.cpp \
../src/StateCenario.cpp \
../src/StateCredito.cpp \
../src/StateDummie.cpp \
../src/StateGameOver.cpp \
../src/StateIntro.cpp \
../src/StateManager.cpp \
../src/StateMenu.cpp \
../src/StateSelecaoAID.cpp \
../src/StateStatus.cpp \
../src/Tempo.cpp \
../src/Text.cpp \
../src/TextoOpcoes.cpp \
../src/TileMap.cpp \
../src/TileSet.cpp \
../src/main.cpp \
../src/tinyxml2.cpp 

OBJS += \
./src/Animation.o \
./src/Ataque.o \
./src/Audio.o \
./src/CaixaTexto.o \
./src/Camera.o \
./src/Cena.o \
./src/EstruturaItem.o \
./src/EstruturaStatus.o \
./src/GameObject.o \
./src/GrupoBatalha.o \
./src/GrupoCenario.o \
./src/GrupoPersonagens.o \
./src/GrupoViloes.o \
./src/InputManager.o \
./src/Item.o \
./src/Level.o \
./src/Personagem.o \
./src/PersonagemAtivo.o \
./src/PersonagemInativo.o \
./src/SDLBase.o \
./src/Sprite.o \
./src/StateBatalha.o \
./src/StateCasaRose.o \
./src/StateCenario.o \
./src/StateCredito.o \
./src/StateDummie.o \
./src/StateGameOver.o \
./src/StateIntro.o \
./src/StateManager.o \
./src/StateMenu.o \
./src/StateSelecaoAID.o \
./src/StateStatus.o \
./src/Tempo.o \
./src/Text.o \
./src/TextoOpcoes.o \
./src/TileMap.o \
./src/TileSet.o \
./src/main.o \
./src/tinyxml2.o 

CPP_DEPS += \
./src/Animation.d \
./src/Ataque.d \
./src/Audio.d \
./src/CaixaTexto.d \
./src/Camera.d \
./src/Cena.d \
./src/EstruturaItem.d \
./src/EstruturaStatus.d \
./src/GameObject.d \
./src/GrupoBatalha.d \
./src/GrupoCenario.d \
./src/GrupoPersonagens.d \
./src/GrupoViloes.d \
./src/InputManager.d \
./src/Item.d \
./src/Level.d \
./src/Personagem.d \
./src/PersonagemAtivo.d \
./src/PersonagemInativo.d \
./src/SDLBase.d \
./src/Sprite.d \
./src/StateBatalha.d \
./src/StateCasaRose.d \
./src/StateCenario.d \
./src/StateCredito.d \
./src/StateDummie.d \
./src/StateGameOver.d \
./src/StateIntro.d \
./src/StateManager.d \
./src/StateMenu.d \
./src/StateSelecaoAID.d \
./src/StateStatus.d \
./src/Tempo.d \
./src/Text.d \
./src/TextoOpcoes.d \
./src/TileMap.d \
./src/TileSet.d \
./src/main.d \
./src/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Library/Frameworks/SDL.framework/Versions/A/Headers -I/Library/Frameworks/SDL_mixer.framework/Versions/A/Headers -I/Library/Frameworks/SDL_image.framework/Versions/A/Headers -I/Library/Frameworks/SDL_ttf.framework/Versions/A/Headers -include/Library/Frameworks/SDL.framework/Versions/A/Headers/SDL.h -include/Library/Frameworks/SDL_ttf.framework/Versions/A/Headers/SDL_ttf.h -include/Library/Frameworks/SDL_image.framework/Versions/A/Headers/SDL_image.h -include/Library/Frameworks/SDL_mixer.framework/Versions/A/Headers/SDL_mixer.h -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


