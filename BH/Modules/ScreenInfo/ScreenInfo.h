#pragma once
#include "../../D2Structs.h"
#include "../Module.h"
#include "../../Config.h"
#include "../../Drawing.h"
#include <deque>

struct StateCode {
	std::string name;
	unsigned int value;
};

struct StateWarning {
	std::string name;
	ULONGLONG startTicks;
	StateWarning(string n, ULONGLONG ticks) : name(n), startTicks(ticks) {}
};

struct Buff {
	BYTE state;
	int index;
	BOOL isBuff;
};

class ScreenInfo : public Module {
	private:
		map<string, string> SkillWarnings;
		std::vector<std::string> automapInfo;
		std::map<DWORD, string> SkillWarningMap;
		std::deque<StateWarning*> CurrentWarnings;
		Drawing::Texthook* bhText;
		Drawing::Texthook* mpqVersionText;
		Drawing::Texthook* d2VersionText;
		DWORD gameTimer;
		DWORD endTimer;		

		int packetRequests;
		ULONGLONG warningTicks;
		ULONGLONG packetTicks;
		bool MephistoBlocked;
		bool DiabloBlocked;
		bool BaalBlocked;
		bool ReceivedQuestPacket;
		DWORD startExperience;
		int startLevel;
		string currentPlayer;
		DWORD currentExperience;
		int currentLevel;
		double currentExpGainPct;
		double currentExpPerSecond;
		char* currentExpPerSecondUnit;

		// used to keep track of runs over the course of a season. example cfg would look like:
		/*
		BoBarb[quickcs]: 250
		BoBarb[quickbaal]: 170
		BoBarb[mf]: 500
		*/
		//Config* cRunData;
		bool bFailedToWrite = false;
		int nTotalGames;
		string szGamesToLevel;
		string szTimeToLevel;
		string szLastXpGainPer;
		string szLastXpPerSec;
		string szLastGameTime;
		int aPlayerCountAverage[8];

		string szSavePath;
		string szColumnHeader;
		string szColumnData;

		map<string, string> automap;
		map<string, int> runcounter;
		vector<pair<string, string>> runDetailsColumns;
		map<string, unsigned int> runs;

		string SimpleGameName(const string& gameName);
		int	GetPlayerCount();
		void FormattedXPPerSec(char* buffer, double xpPerSec);
		string FormatTime(time_t t, const char* format);
		CellFile* cf;
		void* mpqH;
		BOOL manageBuffs;
		BOOL manageConv;
		int resTracker;
		BOOL cellLoaded;
		vector<Buff> activeBuffs;
		vector<BYTE> buffs;
		vector<wchar_t*> buffNames;
		BOOL msgBox;
		bool devTools;
	public:
		static map<std::string, Toggle> Toggles;

		ScreenInfo() :
			Module("Screen Info"), warningTicks(BHGetTickCount()), packetRequests(0),
			MephistoBlocked(false), DiabloBlocked(false), BaalBlocked(false), ReceivedQuestPacket(false),
			startExperience(0), startLevel(0), mpqH(NULL), cf(NULL), cellLoaded(false), msgBox(false), devTools(false) {};

		void OnLoad();
		void OnUnload();
		void LoadConfig();
		void MpqLoaded();
		void OnKey(bool up, BYTE key, LPARAM lParam, bool* block);
		void OnGameJoin();
		void OnGameExit();
	
		void OnRightClick(bool up, int x, int y, bool* block);
		void OnDraw();
		void OnOOGDraw();
		void OnAutomapDraw();
		void OnGamePacketRecv(BYTE* packet, bool *block);

		std::string ReplaceAutomapTokens(std::string& v);		
		void WriteRunTrackerData();
		void DrawPopup(wchar_t* buffName, int x, int y);
		vector<wstring> strBreakApart(wstring str, wchar_t delimiter);
		static void __stdcall CustomExpBar(int x1, int y1, int x2, int y2);
		static void __fastcall CustomExpBarHover(const wchar_t* wStr, int xPos, int yPos, int nColor, int centered);


		static void AddDrop(UnitAny* item);
		static void AddDrop(const string& name, unsigned int x, unsigned int y);
};

StateCode GetStateCode(unsigned int nKey);
StateCode GetStateCode(const char* name);
long long ExpByLevel[];
void ExpBar_Interception();
void ExpBarHover_Interception();