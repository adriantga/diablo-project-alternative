#pragma once

enum class LineType;

void DrawMenuLine(LineType aMenuLineType);
void DrawBreakerLine(LineType aBreakerLineType);
bool HasSubceeded(int aSource, int aValue);
bool HasExceeded(int aValue, int aSource);
void ShowStats(bool aIsPlayer);
void ClearInput();
void Exit();
void ClearScreen();
void ForceInput(int& aInput, int aMin, int aMax);
void Pause();
int Min(int aValue, int aMin);
void WriteLine(const char* aText, bool aNewLine = true);