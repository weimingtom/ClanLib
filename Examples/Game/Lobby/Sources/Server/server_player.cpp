
#include "precomp.h"
#include "server_player.h"

ServerPlayer::ServerPlayer(clan::NetGameConnection *connection)
: connection(connection), id(0)
{
	if(connection)
		connection->set_data("serverplayer", this);
}

ServerPlayer *ServerPlayer::get_player(clan::NetGameConnection *connection)
{
	if(connection)
		return reinterpret_cast<ServerPlayer *>(connection->get_data("serverplayer"));
	else
		return 0;
}

void ServerPlayer::send_event(const clan::NetGameEvent &game_event)
{
	if(connection)
		connection->send_event(game_event);
}

bool ServerPlayer::login(int player_id, const std::string &player_name)
{
	if(id != 0)
		return false;

	id = player_id;
	name = player_name;

	return true;
}
