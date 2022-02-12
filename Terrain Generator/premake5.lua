project "Terrain Generator"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   staticruntime "on"

   targetdir "bin/%{cfg.buildcfg}"
   objdir("bin/Obj/%{cfg.buildcfg}")

   pchheader "ispch.h"
   pchsource "pch/ispch.cpp"

   files {
      "**.h", 
      "**.hpp", 
      "**.cpp",
      "*.lua",
      "*.dll"
   }

   includedirs {
      "../include/Heavy",
      "../include",
      "pch",
   }
   
   defines { 
      "SFML_STATIC" 
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      
      libdirs {
         "../libs/Heavy/Debug"
      }
     
      links { 
         "Heavy.lib",
      }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      libdirs {
         "../libs/Heavy/Release"
      }

      links { 
         "Heavy.lib",
      }
