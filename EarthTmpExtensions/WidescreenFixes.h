#pragma once
#include "pch.h"

class WidescreenFixes
{
private:
	static void ApplyConstructorCrashFix();
	static void AdjustSidepanelSize();
	static void AdjustBottomPanelSize();
	static void AdjustCompassSize();
public:
	static void Apply();
};