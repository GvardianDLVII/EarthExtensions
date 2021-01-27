#include "pch.h"
#include "Configuration.h"
#include <fstream>
#include <sstream>

float Configuration::ShadowRenderThreshold = 50.0f;

int Configuration::GroundRenderBufferSize = 150;
int Configuration::NavMeshRenderBufferSize = 10000;
int Configuration::GreenOverlayRenderBufferSize = 10000;
int Configuration::ResourcesRenderBufferSize = 10000;
int Configuration::WaterRenderBufferSize = 150;
int Configuration::ShadowRenderBufferSize = 100;
int Configuration::MeshRenderBufferSize = 150;

bool Configuration::EnableRenderOverflowCrashFix = true;
bool Configuration::EnableTerrainRenderingOptimization = true;
bool Configuration::EnableWaterRenderingOptimization = true;
bool Configuration::EnableShadowRenderingOptimization = true;
bool Configuration::EnableMeshRenderingOptimization = true;


float Configuration::GetShadowRenderThreshold() { return ShadowRenderThreshold; }

int Configuration::GetGroundRenderBufferSize() { return GroundRenderBufferSize; }
int Configuration::GetNavMeshRenderBufferSize() { return NavMeshRenderBufferSize; }
int Configuration::GetGreenOverlayRenderBufferSize() { return GreenOverlayRenderBufferSize; }
int Configuration::GetResourcesRenderBufferSize() { return ResourcesRenderBufferSize; }
int Configuration::GetWaterRenderBufferSize() { return WaterRenderBufferSize; }
int Configuration::GetShadowRenderBufferSize() { return ShadowRenderBufferSize; }
int Configuration::GetMeshRenderBufferSize() { return MeshRenderBufferSize; }

bool Configuration::GetEnableRenderOverflowCrashFix() { return EnableRenderOverflowCrashFix; }
bool Configuration::GetEnableTerrainRenderingOptimization() { return EnableTerrainRenderingOptimization; }
bool Configuration::GetEnableWaterRenderingOptimization() { return EnableWaterRenderingOptimization; }
bool Configuration::GetEnableShadowRenderingOptimization() { return EnableShadowRenderingOptimization; }
bool Configuration::GetEnableMeshRenderingOptimization() { return EnableMeshRenderingOptimization; }

void Configuration::ReadConfig()
{
	std::ifstream configFile("EarthTmpExtensions.ini");
	if (!configFile.is_open()) {
		return;
	}
	for (std::string line; getline(configFile, line); )
	{
		trim(line);
		if (line.empty() || line[0] == '#')
		{
			continue;
		}
		int splitIndex = line.find('=');
		std::string key = line.substr(0, splitIndex);
		std::string value = line.substr(splitIndex + 1);
		trim(key);
		trim(value);
		if (key == "ShadowRenderThreshold")
		{
			ShadowRenderThreshold = std::stof(value);
		} else if(key == "GroundRenderBufferSize")
		{
			GroundRenderBufferSize = std::stoi(value);
		} else if(key == "NavMeshRenderBufferSize")
		{
			NavMeshRenderBufferSize = std::stoi(value);
		} else if(key == "GreenOverlayRenderBufferSize")
		{
			GreenOverlayRenderBufferSize = std::stoi(value);
		} else if(key == "ResourcesRenderBufferSize")
		{
			ResourcesRenderBufferSize = std::stoi(value);
		} else if(key == "WaterRenderBufferSize")
		{
			WaterRenderBufferSize = std::stoi(value);
		} else if(key == "ShadowRenderBufferSize")
		{
			ShadowRenderBufferSize = std::stoi(value);
		} else if(key == "MeshRenderBufferSize")
		{
			MeshRenderBufferSize = std::stoi(value);
		} else if(key == "EnableRenderOverflowCrashFix")
		{
			EnableRenderOverflowCrashFix = value == "1";
		} else if(key == "EnableTerrainRenderingOptimization")
		{
			EnableTerrainRenderingOptimization = value == "1";
		} else if(key == "EnableWaterRenderingOptimization")
		{
			EnableWaterRenderingOptimization = value == "1";
		} else if(key == "EnableShadowRenderingOptimization")
		{
			EnableShadowRenderingOptimization = value == "1";
		} else if(key == "EnableMeshRenderingOptimization")
		{
			EnableMeshRenderingOptimization = value == "1";
		}
	}
	configFile.close();
}