#include <iostream>
#include "MemoryPoolManager.h"
#include <crtdbg.h>
#include "SharedPtr.h"
#include "RefCounter.h"

#define SIZE 100

// 스마트 포인터를 사용한 메모리 풀링 샘플 //

#pragma region SAMPLE CLASS
class Object abstract : public CRefCounter
{
public:
	Object() = default;
	virtual ~Object() = default;

private:
	virtual void Release() = 0;
};

class Player : public Object
{
public:
	Player() = default;
	virtual ~Player() = default;

public:
	virtual void Release() final
	{
		CMemoryPoolManager::GetInst()->Deallocate<Player>(this);
	}
};
#pragma endregion

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(5900);

#pragma region Player Pool - using SharedPtr
	CMemoryPoolManager::GetInst()->CreatePool<Player>(1);

	CSharedPtr<Player> playerPtr = CMemoryPoolManager::GetInst()->Allocate<Player>();

	playerPtr = nullptr;
#pragma endregion

	CMemoryPoolManager::DestroyInst();

	return 0;
}