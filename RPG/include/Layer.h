#pragma once
#include <string>

class Layer
{
public:
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual std::string GetName() const = 0;
};