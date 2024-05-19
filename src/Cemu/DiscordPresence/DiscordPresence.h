#pragma once

#ifdef ENABLE_DISCORD_RPC
#include <Cafe/TitleList/GameInfo.h>

class DiscordPresence
{
public:
	enum State
	{
		Idling,
		Playing,
	};

	DiscordPresence();
	~DiscordPresence();

	void UpdatePresence(State state, const std::string& text = {}) const;
	void ClearPresence() const;

#if BOOST_OS_LINUX || BOOST_OS_WINDOWS
    void CreateShortcut(GameInfo2& gameInfo);
#endif

};

#endif
