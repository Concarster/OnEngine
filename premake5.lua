workspace "OnEngine"

     architecture "x86"
     architecture "x64"
     --architecture "x86_64"
                  
platforms {       -- Dropdown Solution Confg Platforms section in VS
    
     "Win32",
     "x64"
} 
    
configurations {   -- Dropdown Solution Configurations
     "Debug",
     "Release",
     "Dist"
}

outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "OnEngine/Deps/GLFW/include"

include "OnEngine/Deps/GLFW"

project "OnEngine" 
    location "OnEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bint/" .. outputdir .. "/%{prj.name}")

    pchheader "OnPCH.h"
    pchsource "OnEngine/src/OnPCH.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/Deps/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links 
	{ 
		"GLFW",
		"opengl32.lib"
	}

    filter"system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
             "ON_ENGINE",
             "ON_WINDOW",
             "ON_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/App")
        }

        filter "configurations:Debug"
        --buildoptions "/MTd"
        defines "ON_DEBUG"
        symbols "On"

        filter "configurations:Release"
        --buildoptions "/MT"
        defines "ON_RELEASE"
        optimize "On"

        filter "configurations:Dist"
        --buildoptions "/MT"
        defines "ON_DIST"
        optimize "On"

        --filter { "system:windows", "configurations:Release" }
        --buildoptions "/MT"


-----------------------------------
-----     PROJECT # 1 App     -----
-----------------------------------

project "App" 
    location "App"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bint/" .. outputdir .. "/%{prj.name}")


    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Onengine/Deps/spdlog/include",
        "Onengine/src"
    }

    links {
        "OnEngine"
    }

    filter"system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
             "ON_ENGINE",
             "ON_WINDOW"
        }

        --[[
        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/App")
        }
        ]]

        filter "configurations:Debug"
        --buildoptions "/MTd"
        defines "ON_DEBUG"
        symbols "On"

        filter "configurations:Release"
        --buildoptions "/MT"
        defines "ON_RELEASE"
        optimize "On"

        filter "configurations:Dist"
        --buildoptions "/MT"
        defines "ON_DIST"
        optimize "On"

        --filter { "system:windows", "configurations:Release" }
        --buildoptions "/MT"