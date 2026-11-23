#pragma once
#include "../../D2Structs.h"
#include "../Module.h"
#include "../../Config.h"
#include "../../Drawing.h"

enum MaphackReveal {
	MaphackRevealGame = 0,
	MaphackRevealAct,
	MaphackRevealLevel
};

struct LevelList {
	unsigned int levelId;
	unsigned int x, y, act;
};

struct BaseSkill {
	WORD Skill;
	BYTE Level;
};

class Maphack : public Module {
	private:

		struct OriginalLavaBlock {
			BYTE* pDataOffset;
			vector<BYTE> originalPixels;
		};

		struct LavaBlockBackup {
			DT1SubBlock* subBlock;
			BYTE* originalDataOffset;
			BYTE customBuffers[2][256]; // Two 256-byte ping-pong buffers per sub-block
			int activeBuffer;
		};

		int monsterResistanceThreshold;
		int lkLinesColor;
		unsigned int prevA4LavaColor = 0;
		bool prevLavaEnabled = true;

		static unsigned int a4LavaColor;
		static vector<LavaBlockBackup> g_LavaBlocks;
		static vector<OriginalLavaBlock> originalLavaBlocks;
		

		ULONGLONG portalTimer;
		unsigned int revealType;
		unsigned int maxGhostSelection;
		unsigned int reloadConfig;
		bool revealedGame, revealedAct[6], revealedLevel[255];
		std::map<string, string> MonsterColors;
		std::map<string, string> SuperUniqueColors;
		std::map<string, string> MonsterLines;
		std::map<string, string> MonsterHides;
		std::map<string, unsigned int> TextColorMap; 
		std::map<string, unsigned int> monsterColors;
		std::vector<std::pair<unsigned int, unsigned int>> enhancementColors;
		std::vector<std::pair<unsigned int, unsigned int>> auraColors;
		std::map<string, unsigned int> missileColors;
		std::map<int, unsigned int> automapMonsterColors;
		std::map<int, unsigned int> automapSuperUniqueColors;
		std::map<int, unsigned int> automapMonsterLines;
		std::list<int> automapHiddenMonsters;
		std::list<LevelList*> automapLevels;
		map<std::string, Toggle> Toggles;
		Drawing::UITab* settingsTab;
		std::map<DWORD, std::vector<BaseSkill>> Skills;
		static TileHeader* pAct4LavaTilesHeader;

	public:
		Maphack();

	void ReadConfig();
	void OnLoad();
	void OnUnload();

	void LoadConfig();

	void OnLoop();
	void OnDraw();
	void OnAutomapDraw();
	void OnGameJoin();
	void OnGameExit();
	void OnGamePacketRecv(BYTE* packet, bool *block);

	void ResetRevealed();
	void ResetPatches();

	void OnKey(bool up, BYTE key, LPARAM lParam, bool* block);

	void RevealGame();
	void RevealAct(int act);
	void RevealLevel(Level* level);
	void RevealRoom(Room2* room);

	static Level* GetLevel(Act* pAct, int level);
	static AutomapLayer* InitLayer(int level);
	static void __stdcall CustomDrawDropBackdrop(UnitAny* pItem, const wchar_t* wStr, int x, int y, DWORD dwRectColor, DWORD dwTrans, DWORD dwColor);
	static void __stdcall CustomTileLoad(DWORD* outputPtr, char* fileName);
	static void ApplyAct4LavaColor(bool isEnabled);
	int CanUsePortal();
	void RestoreAct4LavaPointers();
};

void Weather_Interception();
void Lighting_Interception();
void Infravision_Interception();
void __stdcall Shake_Interception(LPDWORD lpX, LPDWORD lpY);
void HoverObject_Interception();
void PortalDelay_Interception();
void DropItemBackdrop_Interception();
void TileLoadPatch_Interception();

void  NPCMessageLoopPatch_ASM();
void  NPCQuestMessageStartPatch_ASM();
void  NPCQuestMessageEndPatch1_ASM();
void  NPCQuestMessageEndPatch2_ASM();

