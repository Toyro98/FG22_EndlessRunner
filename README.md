# FG22_EndlessRunner
Endless runner avoiding blue boxes

# Part 1
### APlatform
Creates a few defaultsubobjects to be able to create the platform mesh in the BluePrint and use it for the APlatformManager to spawn it. Has a trigger that only works for the character and increases character speed by a set amount. It also call 2 functions in the APlatformManager.

### APlatformManager
Responsable for creating x amount of platforms at the start, moving them and setting visibility on a platforms obstacle. All variables are exposed to the editor and only a few can be changes. Uses the Reset() which is found in AActor.

### Obstacle
Used in a prefab and creates a StaticMeshComponent and a BoxComponent attached to the mesh. I added a OnOverlapBegin function to apply damage to player if condition is met.

# Part 2
I added the parts that I still had to implement. Which was the scoring system shown at the startup. What has been improved the most is at the start of the game, you would take damage randomly. I changed from using `AActor*` to `TObjectPtr<AActor>`. Not sure if that makes any difference. Other than that, there has been small fixes here and there while learning how unreal engine and c++ works.

## Changelog
[6f288e0](https://github.com/Toyro98/FG22_EndlessRunner/commit/6f288e031700cab0a97c9131928996ff01bd23f5) - Fixed a "bug" where the platforms did not spawn correctly at the start on a shipped build<br>
[2b61947](https://github.com/Toyro98/FG22_EndlessRunner/commit/2b61947eded7c98810b0846cadf729fac276e3ed) - Fixed an issue where you would take damage randomly at the start of the game<br>
[25b0484](https://github.com/Toyro98/FG22_EndlessRunner/commit/25b048440d0e2bbbe4c2fc38306be3e59899c8d3) - Added a mainmenu<br>
[03cb284](https://github.com/Toyro98/FG22_EndlessRunner/commit/03cb28433a4658d0962bb821697fbf1dddafbd03) - Added saving and loading the score<br>
[ff01b0c](https://github.com/Toyro98/FG22_EndlessRunner/commit/ff01b0c626acf93f72a84f7b224e8e8265a2dc87) - Changed the way I save the highscore and sort it<br>
