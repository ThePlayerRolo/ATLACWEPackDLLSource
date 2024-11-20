#include "pch.h"
#include "cwe_api.h"
#include "ModelInfo.h" //Not needed for FTNames.
#include "AnimationFile.h"

extern "C"
{
    //registering data functions. - Needs to exist.
    void (*RegisterDataFunc)(void* ptr);
    //Lens function - Needed for CWE to recognize the lens.
    __declspec(dllexport) void(__cdecl* ALS_LensSpecial)(ObjectMaster*, ObjectMaster*);
    NJS_TEXNAME ATLATEX[2];
    NJS_TEXLIST ATLATEXLIST = { arrayptrandlength(ATLATEX) };
    NJS_TEXNAME AVATARSTATELENSETEX[8];
    NJS_TEXLIST AVATARSTATELENSET_TEXLIST = { arrayptrandlength(AVATARSTATELENSETEX) };
    BlackMarketItemAttributes BMAangHeadBand = { 250, 100, 0, -1, -1, 0 };
    BlackMarketItemAttributes BMSeaPrunes = { 350, 200, 0, -1, -1, 0 };
    BlackMarketItemAttributes BMAvatarStateLense = { 10, 100, 0, -1, -1, 0 };;
    ModelInfo* MDLAvatarStateLense;
    ChaoItemStats SeaPruneStats = { 10, 0, 100, 0, 0, 0, 100, 0, 0, 0 };
    ModelInfo* MDLSeaPrunes;
    ModelInfo* MDLAangHeadBand;
    int AangHeadBandID;
    int ATLASeaPrunesID;
    int AvatarStateLenseID;


    void __cdecl SeaPrunesFunction(ChaoData* data, ObjectMaster* fruit)
    {
        data->data.Happiness += 1;
    }

    //main CWE Load function -- Important stuff like adding your CWE mod goes here
    void CWELoad(CWE_REGAPI* cwe_api)
    {
        //al_eye_1
        cwe_api->RegisterChaoTexlistLoad("HeadBandTextures", &ATLATEXLIST);
        cwe_api->RegisterChaoTexlistLoad("AvatarStateLense", &AVATARSTATELENSET_TEXLIST);
        AangHeadBandID = cwe_api->RegisterChaoAccessory(Head, MDLAangHeadBand->getmodel(), &ATLATEXLIST, &BMAangHeadBand, "The Headband", "\"Hotmen. Hotmen. Hotmen. Hotmen. Hotmen.\" \" Its over, we caught you! \" \" Who, me?\"");
        ATLASeaPrunesID = cwe_api->RegisterChaoFruit(MDLSeaPrunes->getmodel(), &ATLATEXLIST, &SeaPruneStats, &BMSeaPrunes, SeaPrunesFunction, "Sea Prunes", "Normal Chao like this food all the same, Sokka and Katara enjoy it, and Aang HATES it.");
        AvatarStateLenseID = cwe_api->RegisterChaoSpecial(MDLAvatarStateLense->getmodel(), &AVATARSTATELENSET_TEXLIST, &BMAvatarStateLense, ALS_LensSpecial, NULL, "Avatar State Lenses", "Let your chao become the Avatar and enter the Avatar State!", false);
        cwe_api->RegisterEyeColor("al_eye_1_avatar", &AVATARSTATELENSET_TEXLIST, AvatarStateLenseID);
        cwe_api->RegisterBlackMarketGeneralFruit(ATLASeaPrunesID, 50);
        
    }

    //initialization function - MUST exist in order to have CWE and SA2 see your mod
    __declspec(dllexport) void Init(const char* path)
    {
        HMODULE h = GetModuleHandle(L"CWE");
        std::string pathStr = std::string(path) + "\\";
        //Lens function - This talks to CWE to get the lens to work when registering it as a special object.
        ALS_LensSpecial = (decltype(ALS_LensSpecial))GetProcAddress(GetModuleHandle(L"CWE"), "ALS_LensSpecial");
        MDLAangHeadBand = new ModelInfo(pathStr + "The Headband.sa2mdl");
        MDLSeaPrunes = new ModelInfo(pathStr + "SeaPrunes.sa2mdl");
        MDLAvatarStateLense = new ModelInfo(pathStr + "Avatar State Lense.sa2mdl");
        RegisterDataFunc = (void (*)(void* ptr))GetProcAddress(h, "RegisterDataFunc");
        RegisterDataFunc(CWELoad);
    }
    __declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}

