solution "Rechargeable Libraries"
	configurations { "Debug", "Release" }
	includedirs
	{
		"./"
	}
	
	configuration "Debug"
		targetdir "bin/Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
		
	configuration "Release"
		targetdir "bin/Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
		
	project "hash"
		language "C++"
		kind "StaticLib"
		location "libs/hash/build"
		files
		{
			-- Header Files
			"rechargeable/hash/**.hpp",
			"rechargeable/hash/**.inl",
			"rechargeable/hash/detail/**.hpp",
			"rechargeable/hash/detail/**.inl",
			-- Source Files
			"libs/hash/src/*.hpp",
			"libs/hash/src/*.cpp",
		}
		
	project "fnv1a_example"
		language "C++"
		kind "ConsoleApp"
		location "libs/hash/build"
		files
		{
			-- Source Files
			"libs/hash/examples/fnv1a_example.cpp"
		}
		links
		{
			"hash"
		}

	project "md5_example"
		language "C++"
		kind "ConsoleApp"
		location "libs/hash/build"
		files
		{
			-- Source Files
			"libs/hash/examples/md5_example.cpp"
		}
		links
		{
			"hash"
		}
		