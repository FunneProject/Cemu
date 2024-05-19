#include "DiscordPresence.h"

#ifdef ENABLE_DISCORD_RPC

#include <discord_rpc.h>
#include "Common/version.h"
#include "Cafe/TitleList/GameInfo.h"

DiscordPresence::DiscordPresence()
{
	DiscordEventHandlers handlers{};
	Discord_Initialize("460807638964371468", &handlers, 1, nullptr);
	UpdatePresence(Idling);
}

DiscordPresence::~DiscordPresence()
{
	ClearPresence();
	Discord_Shutdown();
}

void DiscordPresence::UpdatePresence(State state, const std::string& text) const
{
	DiscordRichPresence discord_presence{};

	std::string state_string, details_string, large_image, small_image;
	switch (state)
	{
	case Idling:
		details_string = "Idling";
		large_image = "logo_icon_big_png";
		break;
	case Playing:
		details_string = "Ingame";
		large_image = "https://raw.githubusercontent.com/FunneProject/cemu-icons/main/icons/" + gameInfo.GetBaseTitleId() + ".png";
		state_string = "Playing " + text;
		break;
	default:
		assert(false);
		break;
	}

	discord_presence.details = details_string.c_str();
	discord_presence.state = state_string.c_str();
	discord_presence.startTimestamp = time(nullptr);
	discord_presence.largeImageText = BUILD_VERSION_WITH_NAME_STRING;
	discord_presence.largeImageKey = large_image.c_str();
	Discord_UpdatePresence(&discord_presence);
}

void DiscordPresence::ClearPresence() const
{
	Discord_ClearPresence();
}

#endif
