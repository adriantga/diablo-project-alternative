#pragma once

#include "Character.h"

enum class LineType;

void ShowStats(const Character& aCharacter, const Diablo& aDiablo);
void ShowInventory(const Character& aCharacter);
int GetRandomNumber(const int aMin, const int aMax);
int CalculateDamage(const Character& aSource, const Character& aTarget);
void DrawMenuLine(LineType aMenuLineType);
void DrawBreakerLine(LineType aBreakerLineType);
bool HasSubceeded(int aSource, int aValue);
bool HasExceeded(int aValue, int aSource);
void ClearInput();
void Exit();
void ClearScreen();
void ForceInput(int& aInput, int aMin, int aMax);
void Pause();
int Min(int aValue, int aMin);
int Max(int aValue, int aMax);
int Clamp(int aValue, int aMin, int aMax);
void WriteLine(const char* aText, bool aNewLine = true);