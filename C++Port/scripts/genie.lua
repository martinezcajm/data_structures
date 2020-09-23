solution "DataStructures"
	location "../build"
	
	configurations {
		"Debug",
		"Release",
	}
	
	platforms {
		"x32",
		"x64",
		"Native",
	}
	
	language "C++"
	
	PROJ_DIR = path.getabsolute("..")
	
	project "DataStructures"
		kind "ConsoleApp"
		
		includedirs {
			path.join(PROJ_DIR, "include"),
		}
		
		files {
			path.join(PROJ_DIR,"src/**.c*"),
			path.join(PROJ_DIR, "include/**.h*")
		}
		
		configuration "windows"

		  
		configuration "vs2015"
			windowstargetplatformversion "8.1"
		  
		configuration "vs2017"
		  windowstargetplatformversion "10.0.17134.0"
	   
		configuration "Debug"
		  targetdir "../bin/debug"
		  flags { "Symbols" }
		  implibsuffix "-d"
		  defines {"DEBUG" }

		configuration "Release"
		  targetdir "../bin/release"
		  flags { "OptimizeSpeed", "No64BitChecks" }