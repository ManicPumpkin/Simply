xcopy ".\..\..\..\GooseBerry\GooseBerry\inc" ".\ext\gooseberry\" /S /E /Y 
xcopy ".\..\..\..\GooseBerry\GooseBerry\ext" ".\ext\" /E /Y /I
xcopy ".\ext\libpng-1.6.8\libpng16.dll" ".\" /I /Y