#include "gsc_player.hpp"
//extern customPlayerState_t customPlayerState[MAX_CLIENTS];

void gsc_player_getping(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_getping() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    stackPushInt(client->ping);
}

void gsc_player_getip(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_getip() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    char tmp[16];
    snprintf(tmp, sizeof(tmp), "%d.%d.%d.%d", client->netchan.remoteAddress.ip[0], client->netchan.remoteAddress.ip[1], client->netchan.remoteAddress.ip[2], client->netchan.remoteAddress.ip[3]);

    stackPushString(tmp);
}

void gsc_player_dropclient(scr_entref_t ref)
{
    int self = ref.entnum;
    char *reason;

    if (Scr_GetNumParam() > 0 && !stackGetParams("s", &reason)) {
        Com_Printf("gsc_player_dropclient() argument has a wrong type");
        stackPushUndefined();
        return;
    }

    if (self >= MAX_CLIENTS) {
        Com_Printf("gsc_player_dropclient() entity %i is not a player", self);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[self];

    if (Scr_GetNumParam() > 0)
        SV_DropClient(client, reason);
    else
        SV_DropClient(client, NULL);
    stackPushBool(qtrue);
}

void gsc_player_testf2(scr_entref_t ref)
{
    int self = ref.entnum;
    char *reason;

    Com_Printf("testf2:   self == %i\n", self);

    client_t *client = &svs.clients[self];

    Com_Printf("testf2:   client == %i\n", client);

    stackPushBool(qtrue);
}

void gsc_player_setspeed(scr_entref_t ref)
{
    int id = ref.entnum;
    int speed;

    if ( !stackGetParams("i", &speed) )
    {
        stackError("gsc_player_setspeed() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_setspeed() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    if ( speed < 0 )
    {
        stackError("gsc_player_setspeed() param must be equal or above zero");
        stackPushUndefined();
        return;
    }

//    customPlayerState[id].speed = speed;

    stackPushBool(qtrue);
}

/*
extern customPlayerState_t customPlayerState[MAX_CLIENTS];

void gsc_bots_setbotstance(scr_entref_t ref)
{
    int id = ref.entnum;
    char *stance;

    if (!stackGetParams("s", &stance))
    {
        stackError("gsc_bots_setbotstance() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_bots_setbotstance() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    if (client->netchan.remoteAddress.type != NA_BOT)
    {
        stackError("gsc_bots_setbotstance() player %i is not a bot", id);
        stackPushUndefined();
        return;
    }

    if (!strcmp(stance, "stand"))
    {
        customPlayerState[id].botUpMove &= ~(-KEY_MASK_JUMP | KEY_MASK_JUMP);
        customPlayerState[id].botWButtons &= ~(KEY_MASK_CROUCH | KEY_MASK_PRONE);
    }
    else if(!strcmp(stance, "crouch"))
        customPlayerState[id].botWButtons |= KEY_MASK_CROUCH;
    else if(!strcmp(stance, "prone"))
        customPlayerState[id].botWButtons |= KEY_MASK_PRONE;
    else if(!strcmp(stance, "jump"))
        customPlayerState[id].botUpMove |= KEY_MASK_JUMP;
    else
    {
        stackError("gsc_bots_setbotstance() invalid argument '%s'. Valid arguments are: 'stand' 'crouch' 'prone' 'jump'", stance);
        stackPushUndefined();
        return;
    }

    stackPushBool(qtrue);
}
*/