xcopy "$(SolutionDir)\dlls\*" "$(OutDir)" /K /D /H /Y
xcopy "$(SolutionDir)\TeslaGamesEngine\audioFiles\*" "$(OutDir)audioFiles\" /K /D /H /Y /S /I
xcopy "$(SolutionDir)\TeslaGamesEngine\ImGui\*" "$(OutDir)ImGui\" /K /D /H /Y /S /I
xcopy "$(SolutionDir)\TeslaGamesEngine\Models\*" "$(OutDir)Models\" /K /D /H /Y /S /I
xcopy "$(SolutionDir)\TeslaGamesEngine\Shaders\*" "$(OutDir)Shaders\" /K /D /H /Y /S /I
xcopy "$(SolutionDir)\TeslaGamesEngine\Textures\*" "$(OutDir)Textures\" /K /D /H /Y /S /I