#pragma once
#include <stack>
#include <memory>
#include "CGameState.h"

typedef std::unique_ptr<CGameState> CGameStateRef;

class CStateManager
{
public:
	CStateManager();
	~CStateManager() {}

	void AddState(CGameStateRef toAdd, bool replace = false);
	void PopCurrentState();
	void ProccessStateChange();
	CGameStateRef& GetCurrentState();

private:
	std::stack<CGameStateRef> _states;
	CGameStateRef _newState;	
	
	bool _isAdding = false;
	bool _isReplacing = false;
	bool _isRemoving = false;		
};