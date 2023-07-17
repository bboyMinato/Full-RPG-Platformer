#include "..\include\CStateManager.h"
#include <iostream>

CStateManager::CStateManager()
{
}

void CStateManager::AddState(CGameStateRef toAdd, bool replace)
{	 
	_isAdding = true;
	_isReplacing = replace;

	_newState = std::move(toAdd);		
}

void CStateManager::PopCurrentState()
{
	_isRemoving = true;
}

void CStateManager::ProccessStateChange()
{
	if (_isRemoving && !_states.empty())
	{
		_states.pop();

		if (!_states.empty());		
			_states.top()->Resume();		

		_isRemoving = false;
	}

	if (_isAdding)
	{
		if (_isReplacing && (!_states.empty()))		
			_states.pop();
			
		if (!_states.empty())
			_states.top()->Pause();
	
		_states.push(std::move(_newState));
		_states.top()->Init();

		_isAdding = false;
	}	
}

CGameStateRef& CStateManager::GetCurrentState()
{
	return _states.top();
}
