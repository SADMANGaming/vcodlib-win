#ifndef _DECLARATIONS_HPP_
#define _DECLARATIONS_HPP_

#include <setjmp.h>

#define QDECL __attribute__((cdecl))

#define qboolean int
#define qtrue 1
#define qfalse 0


// 3D vectors
#define VectorCopy( a, b )          ( ( b )[0] = ( a )[0],( b )[1] = ( a )[1],( b )[2] = ( a )[2] )
#define VectorScale( v, s, o )      ( ( o )[0] = ( v )[0] * ( s ),( o )[1] = ( v )[1] * ( s ),( o )[2] = ( v )[2] * ( s ) )
#define VectorCross( a, b, c )      ( ( c )[0] = ( a )[1] * ( b )[2] - ( a )[2] * ( b )[1],( c )[1] = ( a )[2] * ( b )[0] - ( a )[0] * ( b )[2],( c )[2] = ( a )[0] * ( b )[1] - ( a )[1] * ( b )[0] )
#define VectorSubtract( a, b, c )   ( ( c )[0] = ( a )[0] - ( b )[0],( c )[1] = ( a )[1] - ( b )[1],( c )[2] = ( a )[2] - ( b )[2] )


#define BIG_INFO_STRING             0x2000
//#define GENTITYNUM_BITS             10
#define PACKET_BACKUP               32

#define SNAPFLAG_SERVERCOUNT        4

#define GAME_INIT_FRAMES            3
#define FRAMETIME                   100

#define MAX_CHALLENGES              1024
#define MAX_CLIENTS                 64
#define MAX_CONFIGSTRINGS           2048
#define MAX_DOWNLOAD_BLKSIZE        2048
#define MAX_DOWNLOAD_WINDOW         8
//#define MAX_GENTITIES               ( 1 << GENTITYNUM_BITS )
#define MAX_INFO_STRING             0x400
#define MAX_MSGLEN                  0x4000
#define MAX_OSPATH                  256
#define MAX_QPATH                   64
#define	MAX_NAME_LENGTH             32
#define MAX_RELIABLE_COMMANDS       64
#define MAX_STRINGLENGTH            1024
#define MAX_NETNAME                 36

#define CVAR_NOFLAG             0               // 0x0000
#define CVAR_ARCHIVE            (1 << 0)        // 0x0001
#define CVAR_SERVERINFO         (1 << 2)        // 0x0004
#define CVAR_SYSTEMINFO         (1 << 3)        // 0x0008
#define CVAR_CHEAT              (1 << 9)        // 0x0200

#define SVF_SINGLECLIENT        0x800

#define KEY_MASK_NONE           0
#define KEY_MASK_FORWARD        127
#define KEY_MASK_BACK           -127
#define KEY_MASK_MOVERIGHT      127
#define KEY_MASK_MOVELEFT       -127
#define KEY_MASK_JUMP           127 // upmove. prone and jump = -KEY_MASK_JUMP

#define KEY_MASK_FIRE           0x1
#define KEY_MASK_RELOAD         0x8
#define KEY_MASK_LEANLEFT       0x10
#define KEY_MASK_ADS_MODE       0x10
#define KEY_MASK_LEANRIGHT      0x20
#define KEY_MASK_MELEE          0x20
#define KEY_MASK_USE            0x40
#define KEY_MASK_PRONE          0x40 // wbuttons
#define KEY_MASK_CROUCH         0x80 // wbuttons

#define EF_CROUCHING    0x20
#define EF_PRONE        0x40

#define PMF_PRONE       0x1
#define PMF_CROUCH      0x2
#define PMF_LADDER      0x10
#define PMF_SLIDING     0x100


#define PACKET_MASK (PACKET_BACKUP - 1)
#define HEADER_RATE_BYTES 48
#define MAX_MASTER_SERVERS          5


/*
#define KEY_MASK_PRONE          0x100
#define KEY_MASK_CROUCH         0x200
#define KEY_MASK_JUMP           0x400
*/
// playerState_t->eFlags
// entityState_t->eFlags


typedef void (*xcommand_t)(void);

typedef unsigned char byte;
typedef signed char sbyte;
typedef struct gclient_s gclient_t;
typedef struct gentity_s gentity_t;


typedef struct scr_entref_s
{
    uint16_t entnum;
    uint16_t classnum;
} scr_entref_t;

typedef enum
{
    ERR_FATAL = 0x0,
    ERR_VID_FATAL = 0x1,
    ERR_DROP = 0x2,
    ERR_SERVERDISCONNECT = 0x3,
    ERR_DISCONNECT = 0x4,
    ERR_NEED_CD = 0x5,
    ERR_AUTOUPDATE = 0x6,
} errorParm_t;

enum svc_ops_e
{
    svc_bad,
    svc_nop,
    svc_gamestate,
    svc_configstring,
    svc_baseline,
    svc_serverCommand,
    svc_download,
    svc_snapshot,
    svc_EOF
};

typedef enum
{
    ET_GENERAL = 0x0,
    ET_PLAYER = 0x1,
    ET_PLAYER_CORPSE = 0x2,
    ET_ITEM = 0x3,
    ET_MISSILE = 0x4,
    ET_INVISIBLE = 0x5,
    ET_SCRIPTMOVER = 0x6,
    ET_FX = 0x7,
    ET_LOOP_FX = 0x8,
    ET_TURRET = 0x9,
    ET_EVENTS = 0xA
} entityType_t;

typedef enum
{
    TEAM_FREE = 0x0,
    TEAM_NONE = 0x0,
    TEAM_BAD = 0x0,
    TEAM_AXIS = 0x1,
    TEAM_ALLIES = 0x2,
    TEAM_SPECTATOR = 0x3,
    TEAM_NUM_TEAMS = 0x4,
} team_t;

typedef enum
{
    CS_FREE,
    CS_ZOMBIE,
    CS_CONNECTED,
    CS_PRIMED,
    CS_ACTIVE
} clientConnectState_t;

typedef enum
{
    STATE_PLAYING,
    STATE_DEAD,
    STATE_SPECTATOR,
    STATE_INTERMISSION
} sessionState_t;

typedef enum
{
    CON_DISCONNECTED,
    CON_CONNECTING,
    CON_CONNECTED
} clientConnected_t;

typedef enum
{
    NA_BOT = 0,
    NA_BAD = 0,
    NA_LOOPBACK = 2,
    NA_BROADCAST = 3,
    NA_IP = 4,
    NA_IPX = 5,
    NA_BROADCAST_IPX = 6
} netadrtype_t;

typedef struct
{
    netadrtype_t type;
    byte ip[4];
    unsigned short port;
    byte ipx[10];
} netadr_t;

typedef enum
{
    NS_CLIENT,
    NS_SERVER
} netsrc_t;

typedef struct
{
    qboolean overflowed;
    byte *data;
    int maxsize;
    int cursize;
    int readcount;
    int bit;
} msg_t;

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];

typedef struct cvar_s
{
    char *name;
    char *string;
    char *resetString;
    char *latchedString;
    int flags;
    qboolean modified;
    int modificationCount;
    float value;
    int integer;
    struct cvar_s *next;
    struct cvar_s *hashNext;
} cvar_t;

union VariableUnion
{
    int intValue;
    float floatValue;
    unsigned int stringValue;
    const float *vectorValue;
    const char *codePosValue;
    unsigned int pointerValue;
    //...
};

typedef struct
{
    union VariableUnion u;
    int type;
} VariableValue;

typedef struct
{
    const char *fieldBuffer;
    byte pad[0x4176];
    unsigned int levelId;
    // ...
    const char *programBuffer;
    // ... 
} scrVarPub_t; // TODO: finish setup

typedef struct
{
    unsigned int *localVars;
    byte pad[356];
    VariableValue *top;
    //...
} scrVmPub_t; // TODO: verify

typedef int fileHandle_t;
typedef void *unzFile;
typedef void (*xfunction_t)();
typedef void (*xmethod_t)(scr_entref_t);

typedef struct scr_function_s
{
    const char      *name;
    xfunction_t     call;
    qboolean        developer;
} scr_function_t;

typedef struct scr_method_s
{
    const char     *name;
    xmethod_t      call;
    qboolean       developer;
} scr_method_t;

struct directory_t
{
    char path[MAX_OSPATH];
    char gamedir[MAX_OSPATH];
};

enum fsMode_t
{
    FS_READ,
    FS_WRITE,
    FS_APPEND,
    FS_APPEND_SYNC
};


typedef struct leakyBucket_s leakyBucket_t;
struct leakyBucket_s
{
    netadrtype_t type;
    unsigned char adr[4];
    uint64_t lastTime;
    signed char	burst;
    long hash;
    leakyBucket_t *prev, *next;
};

typedef struct usercmd_s
{
    int serverTime;
    byte buttons; // console, chat, ads, attack, use
    byte wbuttons; // lean left, lean right, reload
    byte weapon;
    byte flags;
    int angles[3];
    signed char forwardmove, rightmove, upmove;
    byte unknown;
} usercmd_t;

typedef void netProfileInfo_t;

typedef struct
{
    netsrc_t sock;
    int dropped;
    netadr_t remoteAddress;
    int qport;
    int incomingSequence;
    int outgoingSequence;
    int fragmentSequence;
    int fragmentLength;
    byte fragmentBuffer[MAX_MSGLEN];
    qboolean unsentFragments;
    int unsentFragmentStart;
    int unsentLength;
    byte unsentBuffer[MAX_MSGLEN];
    netProfileInfo_t *netProfile;
} netchan_t;

typedef struct
{
    char command[MAX_STRINGLENGTH];
    int cmdTime;
    int cmdType;
} reliableCommands_t;

typedef struct
{
    netadr_t adr;
    int challenge;
    int time;
    int pingTime;
    int firstTime;
    int firstPing;
    qboolean connected;
    int guid;
} challenge_t;

typedef enum
{
    TR_STATIONARY = 0,
    TR_INTERPOLATE = 1,
    TR_LINEAR = 2,
    TR_LINEAR_STOP = 3,
    TR_SINE = 4,
    TR_GRAVITY = 5,
    TR_GRAVITY_PAUSED = 6,
    TR_ACCELERATE = 7,
    TR_DECCELERATE = 8
} trType_t;

typedef struct
{
    trType_t trType;
    int trTime;
    int trDuration;
    vec3_t trBase;
    vec3_t trDelta;
} trajectory_t;

typedef struct entityState_s
{
    int number;
    entityType_t eType;
    int eFlags;
    trajectory_t pos;
    trajectory_t apos;
    int time;
    int time2;
    vec3_t origin2;
    vec3_t angles2;
    int otherEntityNum;
    int attackerEntityNum;
    int groundEntityNum;
    int constantLight;
    int loopSound;
    int surfType;
    int index; // modelIndex
    int clientNum;
    int iHeadIcon;
    int iHeadIconTeam;
    int solid;
    int eventParm;
    int eventSequence;
    int events[4];
    unsigned int eventParms[4];
    int weapon;
    int legsAnim;
    int torsoAnim;
    int leanf;
    int scale; // used as loopfxid, hintstring, ... and doesn't actually scale a player's model size
    int dmgFlags;
    int animMovetype;
    float fTorsoHeight;
    float fTorsoPitch;
    float fWaistPitch;
} entityState_t;

typedef struct
{
    byte pad[4];
    int svFlags;
    int singleClient;
    byte pad2[4];
    vec3_t mins;
    vec3_t maxs;
    int contents;
    vec3_t absmin;
    vec3_t absmax;
    vec3_t currentOrigin;
    vec3_t currentAngles;
    int ownerNum;
    int eventTime;
} entityShared_t;


typedef enum
{
    PM_NORMAL = 0x0,
    PM_NORMAL_LINKED = 0x1,
    PM_NOCLIP = 0x2,
    PM_UFO = 0x3,
    PM_SPECTATOR = 0x4,
    PM_INTERMISSION = 0x5,
    PM_DEAD = 0x6,
    PM_DEAD_LINKED = 0x7,
} pmtype_t;



typedef enum
{
    WEAPON_READY = 0x0,
    WEAPON_RAISING = 0x1,
    WEAPON_DROPPING = 0x2,
    WEAPON_FIRING = 0x3,
    WEAPON_RECHAMBERING = 0x4,
    WEAPON_RELOADING = 0x5,
    WEAPON_RELOADING_INTERUPT = 0x6,
    WEAPON_RELOAD_START = 0x7,
    WEAPON_RELOAD_START_INTERUPT = 0x8,
    WEAPON_RELOAD_END = 0x9,
    WEAPON_MELEE_INIT = 0xA,
    WEAPON_MELEE_FIRE = 0xB,
    WEAPONSTATES_NUM = 0xC,
} weaponstate_t;

typedef struct playerState_s
{
    int commandTime;
    pmtype_t pm_type;
    int bobCycle;
    int pm_flags;
    int pm_time;
    vec3_t origin;
    vec3_t velocity;
    vec2_t oldVelocity;
    int weaponTime;
    int weaponDelay;
    int gravity;
    float leanf;
    int speed;
    vec3_t delta_angles;
    int groundEntityNum;
    vec3_t vLadderVec;
    int jumpTime;
    float jumpOriginZ;
    int legsTimer;
    int legsAnim;
    int torsoTimer;
    int torsoAnim;
    int movementDir;
    int eFlags;
    int eventSequence;
    int events[4];
    unsigned int eventParms[4];
    int oldEventSequence;
    int clientNum;
    unsigned int weapon;
    weaponstate_t weaponstate;
    float fWeaponPosFrac;
    int viewmodelIndex;
    vec3_t viewangles;
    int viewHeightTarget;
    float viewHeightCurrent;
    byte pad[8188];
} playerState_t;

typedef struct
{
    sessionState_t sessionState;
    int forceSpectatorClient;
    int statusIcon;
    int archiveTime;
    int score;
    int deaths;
    byte pad[4];
    clientConnected_t connected;
    usercmd_t cmd;
    usercmd_t oldcmd;
    qboolean localClient;
    byte pad2[8];
    char netname[MAX_NETNAME];
    int maxHealth;
    byte pad3[128];
} clientSession_t;


struct gclient_s
{
    playerState_t ps;
    clientSession_t sess;
    int spectatorClient;
    qboolean noclip;
    qboolean ufo;
    byte pad2[228];
    //...
};

struct gentity_s
{
  entityState_t s;
  entityShared_t r;
  byte pad[4];
  gclient_t *client;
  byte pad2[440];
};

typedef struct
{
    playerState_t ps;
    int num_entities;
    int num_clients;
    int first_entity;
    int first_client;
    unsigned int messageSent;
    unsigned int messageAcked;
    int messageSize;
} clientSnapshot_t;


typedef struct client_s
{
    clientConnectState_t state;
    qboolean sendAsActive;
    const char *dropReason;
    char userinfo[MAX_INFO_STRING];
    reliableCommands_t	reliableCommands[MAX_RELIABLE_COMMANDS];
    int reliableSequence;
    int reliableAcknowledge;
    int reliableSent;
    int messageAcknowledge;
    int gamestateMessageNum;
    int challenge;
    usercmd_t lastUsercmd;
    int lastClientCommand;
    char lastClientCommandString[MAX_STRINGLENGTH];
    gentity_t *gentity;
    char name[MAX_NAME_LENGTH];
    char downloadName[MAX_QPATH];
    fileHandle_t download;
    int downloadSize;
    int downloadCount;
    int downloadClientBlock;
    int downloadCurrentBlock;
    int downloadXmitBlock;
    unsigned char *downloadBlocks[MAX_DOWNLOAD_WINDOW];
    int downloadBlockSize[MAX_DOWNLOAD_WINDOW];
    qboolean downloadEOF;
    int downloadSendTime;
    int deltaMessage;
    int nextReliableTime;
    int lastPacketTime;
    int lastConnectTime;
    int nextSnapshotTime;
    qboolean rateDelayed;
    int timeoutCount;
    clientSnapshot_t frames[PACKET_BACKUP];
    int ping;
    int rate;
    int snapshotMsec;
    int pureAuthentic;
    netchan_t netchan;
    unsigned short clscriptid;
    int bIsTestClient;
    int serverId;
} client_t;

typedef struct
{
    qboolean initialized;
    int time;
    int snapFlagServerBit;
    client_t *clients;
    //...
} serverStatic_t;

typedef struct
{
    gclient_t *clients;
    gentity_t *gentities;
    int gentitySize;
    int num_entities;
    gentity_t *firstFreeEnt;
    gentity_t *lastFreeEnt;
    fileHandle_t logFile;
    int initializing;
    byte pad[0x1C0];
    int maxclients;
    int framenum;
    int time;
    int previousTime;
    int frameTime;
    int startTime;
    int teamScores[TEAM_NUM_TEAMS];
    int lastTeammateHealthTime;
    qboolean bUpdateScoresForIntermission;
    int manualNameChange;
    int numConnectedClients;
    int sortedClients[MAX_CLIENTS];
    char voteString[1024];
    // ...
} level_locals_t;

typedef enum
{
    SS_DEAD,
    SS_LOADING,
    SS_GAME
} serverState_t;

typedef struct
{
    serverState_t state;
    qboolean restarting;
    int start_frameTime;
    byte pad[0x6141C];
    playerState_t *gameClients;
    int gameClientSize;
    int	skelTimeStamp;
    int	bpsWindowSteps;
    int	bpsTotalBytes;
    int	bpsMaxBytes;
    int	ubpsTotalBytes;
    int	ubpsMaxBytes;
    float ucompAve;
    int	ucompNum;
} server_t;

enum clc_ops_e
{
    clc_move,
    clc_moveNoDelta,
    clc_clientCommand,
    clc_EOF
};

enum svscmd_type
{
    SV_CMD_CAN_IGNORE = 0x0,
    SV_CMD_RELIABLE = 0x1,
};

typedef enum
{
    EXEC_NOW,
    EXEC_INSERT,
    EXEC_APPEND
} cbufExec_t;

typedef struct WeaponDef_t
{
    int number;
    char* name;
    char* displayName;
    byte pad[0x1E4];
    int reloadAddTime;
    byte pad2[0x1C];
    int fuseTime;
    float moveSpeedScale;
    float adsZoomFov;
    float adsZoomInFrac;
    float adsZoomOutFrac;
    byte pad3[0x44];
    int adsTransInTime;
    int adsTransOutTime;
    byte pad4[0x8];
    float idleCrouchFactor;
    float idleProneFactor;
    byte pad5[0x50];
    int cookOffHold;
    int clipOnly;
    //...
} WeaponDef_t;

struct pmove_t
{
    playerState_t *ps;
    usercmd_t cmd;
    //...
};

typedef struct
{
    byte pad[4];
    unsigned short allies;
    byte pad2[2];
    unsigned short axis;
    byte pad3[114];
    unsigned short spectator;
    byte pad4[122];
    unsigned short none;
    // ...
} stringIndex_t;



extern gentity_t *g_entities;
//extern gclient_t *g_clients;
extern stringIndex_t *scr_const;


static const int svs_offset = 0x16B2AA0;
static const int varpub_offset = 0x976468;
static const int vmpub_offset = 0xA7A508;


#define scrVarPub (*((scrVarPub_t*)( varpub_offset )))
#define scrVmPub (*((scrVmPub_t*)( vmpub_offset )))
#define svs (*((serverStatic_t*)( svs_offset )))

// Check for critical structure sizes and fail if not match
/*
#if __GNUC__ >= 6

static_assert((sizeof(netchan_t) == 32832), "ERROR: netchan_t size is invalid!");
static_assert((sizeof(entityState_t) == 240), "ERROR: entityState_t size is invalid!");
static_assert((sizeof(client_t) == 370940), "ERROR: client_t size is invalid!");
static_assert((sizeof(playerState_t) == 8400), "ERROR: playerState_t size is invalid!");
static_assert((sizeof(entityShared_t) == 96), "ERROR: entityShared_t size is invalid!");
static_assert((sizeof(gentity_t) == 788), "ERROR: gentity_t size is invalid!");
static_assert((sizeof(gclient_t) == 8900), "ERROR: gclient_t size is invalid!");

#endif
*/

#endif

// Custom data types

#define MAX_ERROR_BUFFER 64

typedef struct src_error_s
{
    char internal_function[64];
    char message[1024];
} scr_error_t;

typedef struct customPlayerState_s
{
    int speed;
    int gravity;
    int fps;
    int frames;
    uint64_t frameTime;
    int ufo;
    qboolean overrideJumpHeight;
    int jumpHeight;

    int botButtons;
    int botWButtons;
    int botWeapon;
    char botForwardMove;
    char botRightMove;
    char botUpMove;
    
    int airJumpsAvailable;
    qboolean overrideJumpHeight_air;
    bool hiddenFromScoreboard;
} customPlayerState_t;

typedef struct callback_s
{
    int *pos;
    const char *name;
} callback_t;

typedef enum
{
	VAR_UNDEFINED,
	VAR_OBJECT,
	VAR_STRING,
	VAR_ISTRING,
	VAR_VECTOR,
	VAR_FLOAT,
	VAR_INTEGER,
	VAR_CODEPOS,
	VAR_PRECODEPOS,
	VAR_FUNCTION,
	VAR_STACK,
	VAR_ANIMATION,
	VAR_DEVELOPER_CODEPOS,
	VAR_INCLUDE_CODEPOS,
	VAR_THREAD_LIST,
	VAR_THREAD,
	VAR_NOTIFY_THREAD,
	VAR_TIME_THREAD,
	VAR_CHILD_THREAD,
	VAR_STRUCT,
	VAR_REMOVED_ENTITY,
	VAR_ENTITY,
	VAR_ARRAY,
	VAR_REMOVED_THREAD,
	VAR_COUNT
} var_type_t;
