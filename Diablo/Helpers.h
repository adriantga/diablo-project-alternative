#pragma once

class Character;
struct Diablo;

enum class LineType;

int Min(int aSource, int aMin);
int Max(int aSource, int aMax);
void ShowStats(const Character& aCharacter, const Diablo& aDiablo);
void ShowInventory(const Character& aCharacter);
void WriteLine(const char* aText, bool aNewLine = true);
int GetRandomNumber(int aMin, int aMax);
int CalculateDamage(const Character& aSource, const Character& aTarget);
void DrawMenuLine(LineType aLineType);
void DrawBreakerLine(LineType aLineType);
bool HasSubceeded(int aSource, int aValue);
bool HasExceeded(int aSource, int aValue);
void ClearInput();
void Pause();
void ClearScreen();
void ForceInput(int& aInput, int aMin = -1, int aMax = -1);