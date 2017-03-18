#pragma once

#include "Arena.h"

/*
²��O����t�m���A�Ω�޲zŪ��Wz�ɪ��O�������
@By Wanger.
*/

class MemoryPoolMan
{
private:
	memt::Arena *pArena = new memt::Arena();

public:
	MemoryPoolMan() {};

	/*static MemoryPoolMan *GetInstance()
	{
		static MemoryPoolMan *sMemoryPool = new MemoryPoolMan();
		return sMemoryPool;
	}*/

	//�t�m�@�ӫ��Ъ���A�j�p��size (byte)
	void* AllocateObject(int size)
	{
		return pArena->alloc(size);
	}

	//�t�m�@�Ӱ}�C�A���׬�len bytes
	void* AllocateArray(int len)
	{
		auto allocPair = pArena->allocArray<char>(len + 4);
#pragma warning(disable:4312)  
#pragma warning(disable:4311)  
#pragma warning(disable:4302)  
		//�j���end�g�b�e�|��bytes
		*((int*)allocPair.first) = (int)allocPair.second;
		return allocPair.first + 4;
#pragma warning(default:4302)  
#pragma warning(disable:4311)  
#pragma warning(disable:4312)  
	}

	//�N���w�� ptr (�@�Ӫ���)  �P��
	void DestructObject(void* ptr)
	{
		pArena->freeTop(ptr);
	}

	//�N���w�� ptr (�@�Ӱ}�C) �P���A�䤤�}�C���׺ݦ�m�O���b���w���Ъ��e�|��byte
	void DestructArray(void* ptr)
	{
		pArena->freeTopArray(((char*)((char*)ptr) - 4), (char*)(*(int*)(((char*)ptr) - 4)));
	}

	//����O�Ц��A�N�Ŷ��k�ٵ�OS
	void Release()
	{
		pArena->freeAllAllocsAndBackingMemory();
	}
};

//Memory Allocator for regular use.
extern MemoryPoolMan *stMemoryPoolMan;

//Used for WZ.
extern MemoryPoolMan *stWzMemoryPoolMan;

struct ArenaUniquePtrDeleter
{
	void operator()(unsigned char* ptr)
	{
		stMemoryPoolMan->DestructArray(ptr);
	}
};