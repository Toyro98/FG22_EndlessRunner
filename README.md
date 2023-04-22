# FG22_EndlessRunner
Endless runner avoiding blue boxes

# Part 1
### APlatform
Creates a few defaultsubobjects to be able to create the platform mesh in the BluePrint and use it for the APlatformManager to spawn it. Has a trigger that only works for the character and increases character speed by a set amount. It also call 2 functions in the APlatformManager.

### APlatformManager
Responsable for creating x amount of platforms at the start, moving them and setting visibility on a platforms obstacle. All variables are exposed to the editor and only a few can be changes. Uses the Reset() which is found in AActor.

### Obstacle
Used in a prefab and creates a StaticMeshComponent and a BoxComponent attached to the mesh. I added a OnOverlapBegin function to apply damage to player if condition is met.
