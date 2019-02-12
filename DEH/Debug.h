#pragma once
#include "DEH.h"

class Debug {
private:
	bool debugInfoEnabled = true;
public:
	static Debug debug;

	struct debugInfo {
		char* debugName;
		std::string debugText;

		debugInfo(std::string Text)
		{
			debugName = "";
			debugText = Text;
		}
	};
	void drawDebugInfo();
	void addDebugInfoItem(std::string InfoStr) noexcept;

	std::vector<debugInfo> debugInfoVec;
};