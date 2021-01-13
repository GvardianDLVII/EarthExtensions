#include "pch.h"
#include "TerrainRenderProxy.h"
#include <map>
#include <list>


static int textures = 0;
static int squares = 0;

class TextureInfo
{
public:
	DWORD textureNum;
	DWORD textureSize;
	TextureInfo(DWORD textureNum, DWORD textureSize)
	{
		this->textureNum = textureNum;
		this->textureSize = textureSize;
		textures++;
	}
	bool operator <(const TextureInfo& b) const
	{
		return textureNum * textureSize < b.textureNum * b.textureSize;
	}
	~TextureInfo()
	{
		long x = 1;
		x--;
		textures--;
	}
};
class SquareInfo
{
public:
	D3DVERTEX* Vertices;
	LPWORD Indices;
	SquareInfo(D3DVERTEX* lpvVertices, LPWORD lpwIndices)
	{
		Vertices = new D3DVERTEX[4];
		Indices = new WORD[6];
		memcpy(Vertices, lpvVertices, 4 * sizeof(D3DVERTEX));
		memcpy(Indices, lpwIndices, 6 * sizeof(WORD));
		squares++;
	}
	SquareInfo(const SquareInfo &other)
	{
		Vertices = new D3DVERTEX[4];
		Indices = new WORD[6];
		memcpy(Vertices, other.Vertices, 4 * sizeof(D3DVERTEX));
		memcpy(Indices, other.Indices, 6 * sizeof(WORD));
		squares++;
	}
	~SquareInfo()
	{
		delete[] Vertices;
		delete[] Indices;
		squares--;
	}
};

TerrainRenderProxy::TerrainRenderProxy()
{
	d3dDevice = (IDirect3DDevice3*)0x009FBC24; //constant address of D3DDevice initialized by TheMoonProject.exe
}

TextureInfo* currentTexture;

typedef std::map<TextureInfo, std::list<SquareInfo>> RenderBuffer;
RenderBuffer renderBuffer;

HRESULT TerrainRenderProxy::DoSomethingWithTexture(DWORD textureNum, DWORD textureSize)
{
	TextureInfo mapKey(textureNum, textureSize);
	RenderBuffer::iterator it = renderBuffer.find(mapKey);
	if (it != renderBuffer.end())
	{
		currentTexture = const_cast<TextureInfo*>(&(it->first));
	}
	else
	{
		renderBuffer.insert(std::pair<TextureInfo,std::list<SquareInfo>>(TextureInfo(textureNum, textureSize), std::list<SquareInfo>()));
		it = renderBuffer.find(mapKey);
		currentTexture = const_cast<TextureInfo*>(&(it->first));
	}
	return 0;
}

HRESULT TerrainRenderProxy::RegisterSingleSquareRendering(LPVOID lpvVertices, LPWORD lpwIndices)
{
	renderBuffer[*currentTexture].push_back(SquareInfo((D3DVERTEX*)lpvVertices, lpwIndices));
	return 0;
}

HRESULT TerrainRenderProxy::Commit()
{
	//todo: commit changes

	//call replaced asm code
	//005C9BCB 6A 01                push        1  
	//005C9BCD FF 15 D4 E2 9F 00    call        dword ptr ds : [9FE2D4h]
	typedef void (__stdcall *originalCall)(WORD param);

	void* originalFunctionPointer = (void*)(*((long*)0x009FE2D4));
	originalCall call = (originalCall)(originalFunctionPointer);
	call(1);
	renderBuffer.clear();
	return 0;
}