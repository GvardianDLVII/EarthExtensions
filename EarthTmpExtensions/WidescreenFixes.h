#pragma once
#include "pch.h"

class WidescreenFixes
{
private:
	static void ApplyConstructorCrashFix();
	static void AdjustSidepanelSize();
	static void AdjustBottomPanelSize();
public:
	static void Apply();
};