-- premake5.lua
workspace "Isometric Terrain Generator"
   startproject "Terrain Generator"
   architecture "x64"
   configurations {
      "Debug", 
      "Release" 
   }

   filter { "platforms:Win64" }
      system "Windows"
      
include "Terrain Generator"