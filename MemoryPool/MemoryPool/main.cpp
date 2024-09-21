#include <iostream>
#include "MemoryPoolManager.h"
#include <crtdbg.h>

#define SIZE 300

#pragma region SAMPLE CLASS
class Object abstract
{
public:
	Object() = default;
	virtual ~Object() = default;
};

class Player : public Object
{
public:
	Player() = default;
	virtual ~Player() = default;

public:
	int mData;
};

class Monster : public Object
{
public:
	Monster() = default;
	virtual ~Monster() = default;

public:
	float mData;
};
#pragma endregion

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(5900);

#pragma region Player Pool
	CMemoryPoolManager::GetInst()->CreatePool<Player>(100);
	Player* playerPtr[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		playerPtr[i] = CMemoryPoolManager::GetInst()->Allocate<Player>();
		playerPtr[i]->mData = i;
	}
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << playerPtr[i]->mData << " ";
	}
	CMemoryPoolManager::GetInst()->Deallocate<Player>(playerPtr[SIZE / 2]);
#pragma endregion

#pragma region Monster Pool
	CMemoryPoolManager::GetInst()->CreatePool<Monster>(10);
	CMemoryPoolManager::GetInst()->DeletePool<Monster>();
#pragma endregion

	CMemoryPoolManager::DestroyInst();
	std::cout << "\n\n\n";

	return 0;
}