
workspace "PongClone"
   configurations { "Debug", "Release" }
   platforms { "Win64" }
   architecture "x86_64"
  
   startproject "PongClone"
    
   outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

   include "PongClone"


   newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.remove("./bin/**.exe")
        os.remove("./bin/**.pdb")
        print("Removing intermediate binaries")
        os.rmdir("./bin-int")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
    }
