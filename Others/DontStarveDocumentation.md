# Dont Starve Documentation

> Dont starve Mods are written in Lua Language.

## Basic Creature Mod

A `modinfo.lua` file need to be in the mods folder. The name of the file should be as shown. This file contains the information about the mod that is shown in the mod configuration menu of the game.

```lua
--modinfo.lua

name = "Mod Name"
description = "Description Of the Mod"
author = "Author"
version = "1.0"
forumthread = "" --Link to the FromThread, could be left empty
api_version = 6
--Show which game dlc the mod is compatible with.
--All the options about compatibality are optional but help in avoiding crashes
dont_starve_compatible = true
reign_of_giants_compatible = true
shipwrecked_compatible = true
porkland_compatible = true --either or
hamlet_compatible = true
dst_compatible = false --If the mod is also compatible with the other game dont starve together
--Info about the icon that is show in the mod menu
--The file needs to be placed in the same root folder with the modinfo.lua file
icon_atlas = "modicon.xml" --both the options about icons are optional
icon = "modicon.tex"

--One of the option is configuration_options which is an object that contains options that can be used to configure the mod.
```

A `modmain.lua` is also the needed file. This is the file that contains the entry point for the mod to work in the game.

Sample `modmain.lua` file that spawns a buffalo at the players location.

```lua
--This function spawns a 'Beefalo' at the player's position.  The player parameter is a reference to the player in game.
function SpawnCreature(player)

    --[NEW] Get the player's current position.
    local x, y, z = player.Transform:GetWorldPosition()

    --Spawn a 'Beefalo' prefab at the world origin.  Prefabs are basically a fancy game development term for objects.
    --creature, item and character in 'Don't Starve' is a prefab.

    -- Every creature, item and character in 'Don't Starve' is a prefab.
    local creature = GLOBAL.SpawnPrefab("forest/animals/beefalo")

    --Move the creature to the player's position.
    creature.Transform:SetPosition( x, y, z )
end


--Tell the engine to run the function "SpawnCreature" as soon as the player spawns in the world.
AddSimPostInit(SpawnCreature)
```
