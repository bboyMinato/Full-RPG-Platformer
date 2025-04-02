#pragma once

namespace Globals
{
	const int SCREEN_WIDTH = 1920;
	constexpr int SCREEN_HEIGHT = 1024;

	template<typename T>
	constexpr const T& Clamp(const T& val, const T& low, const T& high) {
		return (val < low) ? low : (val > high) ? high : val;
	}
}