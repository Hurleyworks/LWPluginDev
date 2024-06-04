local LWROOT = "../../../"
local ROOT = "../../../../"

project  "SimpleGeneric"

	if _ACTION == "vs2019" then
		cppdialect "C++17"
		location (ROOT .. "builds/VisualStudio2019/projects")
    end
	if _ACTION == "vs2022" then
		cppdialect "C++20"
		location (ROOT .. "builds/VisualStudio2022/projects")
    end
	
	kind "SharedLib"
	
	local THIRD_PARTY_DIR = ROOT .. "thirdparty/"
	local MODULES = ROOT .. "modules/"
	local SOURCE_DIR = "source/*"
    files
    { 
      SOURCE_DIR .. "**.h", 
      SOURCE_DIR .. "**.hpp", 
      SOURCE_DIR .. "**.c",
      SOURCE_DIR .. "**.cpp",
    }
	
	includedirs
	{
		ROOT,
		MODULES,
		THIRD_PARTY_DIR .. "lightwaveSDK/LW2020/sdk/include",
		LWROOT .. "core/source/jahley",
		LWROOT .. "core/source",
		LWROOT .. "core/source/framework"
	}
	linkoptions ("/DEF:../../../thirdparty/lightwaveSDK/LW2023/sdk/source/serv.def")
	links 
	{ 
		LWCore,
		
    }
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		defines {"_CRT_SECURE_NO_WARNINGS", "__WINDOWS_WASAPI__", "_MSWIN"}
		disablewarnings { "5030" , "4305", "4316", "4267"}
		vpaths 
		{
		  ["Header Files/*"] = { 
			SOURCE_DIR .. "**.h", 
			SOURCE_DIR .. "**.hxx", 
			SOURCE_DIR .. "**.hpp",
		  },
		  ["Source Files/*"] = { 
			SOURCE_DIR .. "**.c", 
			SOURCE_DIR .. "**.cxx", 
			SOURCE_DIR .. "**.cpp",
		  },
		}
		

-- add settings common to all project
dofile(LWROOT .. "premake/lwcommon.lua")
