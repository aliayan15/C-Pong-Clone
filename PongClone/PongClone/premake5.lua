
project "PongClone"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "on"

    targetdir("../bin/" .. outputdir .. "/")
    objdir("../bin-int/" .. outputdir .. "/")

    files {
        "Scr/**.cpp",
        "Scr/**.h"
    }
   
    includedirs { "../Dependencies/sfml/include" }

    libdirs { "../Dependencies/sfml/lib" }
    links { "opengl32.lib", "freetype.lib", "winmm.lib", "gdi32.lib", "openal32.lib", 
    "flac.lib", "vorbisenc.lib", "vorbisfile.lib", "vorbis.lib", "ogg.lib", "ws2_32.lib" }

    filter "system:windows"
        systemversion "latest"
        defines { "SFML_STATIC" }

    filter { "configurations:Debug" }
        buildoptions "/MDd"
        runtime "Debug"
        symbols "on"
        links { "sfml-audio-s-d.lib", "sfml-graphics-s-d.lib",
        "sfml-network-s-d.lib", "sfml-system-s-d.lib", "sfml-window-s-d.lib" }

    filter { "configurations:Release" }
        buildoptions "/MD"
        runtime "Release"
        optimize "on"
         links { "sfml-audio-s.lib", "sfml-graphics-s.lib",
         "sfml-network-s.lib", "sfml-system-s.lib", "sfml-window-s.lib" }

    

     

    