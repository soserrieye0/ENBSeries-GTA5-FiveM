//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//ENBSeries is a set of graphical modifications for games
//Description on the web page may not be equal to this info.
//created by Boris Vorontsov http://enbdev.com
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

PUBLISHING BINARY FILES OF ENBSERIES ON NEXUS SITES (TES NEXUS, SKYRIM NEXUS, ETC)
IS STRICTLY PROHIBITED. ONLY PRESETS AND SHADERS CAN BE HOSTED THERE.



ENBSeries v0.492 for GTA 5.

Increased quality of skylighting and denoiser of ambient occlusion. Slightly increased
performance of them.


WARNING!
Set game video options to DirectX11 mode. Also mod is tested for almost maxed graphics
setting, so it may fail to work properly otherwise. Frame scaling in game video options
is not supported.
Do not run the game in online mode with ENBSeries installed, i'm not sure if you will
be banned or not.

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//CHANGES LOG
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Version 0.486:
Added street lights color tweaking parameters. Many minor fixes and improvements from
previous silent updates.

Version 0.471:
Added fixes for AltV multiplayer 9.5 or above.
Added dropdown box support for shader variables, example for it added to the enbeffect.fx.
Added support of changing quality and dropbox variables via enb sdk.

Version 0.456:
Optimized CPU based performance of the mod. Fixed compatibility issue with some overlay
tools. Improved quality of ssao/ssil effect and it's filtering.
Added workaround for blocked input functions by FiveM.
Fixed GUI scrolling bug after preset is reloaded.

Version 0.447:
Added enbhelper.dll plugin to enbseries folder which require ScriptHook installed.
Added multiple weathers support. Added some statistics from helper plugin.
Removed obsolette adaptive adaptation parameters and bit increased performance.
Fixed subdermal color cropping bug of subsurface scattering.

Version 0.446:
Updated enbbloom.fx shader to higher quality version with tweakable parameters.
Added bloom and lens textures to original post processing of enbeffect.fx shader.
Added subsurface scattering effect, when enabled it replace game one.
Added DirectLighting intensity, curve, desaturation, color filter parameters
for natural light ambient. Added UseOriginalBloom parameter.

Version 0.443:
Added water displacement for missing shader, added displacement amount parameter for water.
Changed wetness parameter to be time of the day dependent. Added emergency light intensity
parameter to control firetruck, ambulance and police vehicles.

Version 0.438:
Added test of tesselation for ocean water. Fixed crash when changing display mode
and skylighting is enabled.

Version 0.432:
Added sand of ocean shore wetness depending on waves. Added foam shift at collisions
with vehicles and spread of wetness on sand. Added foam shader with multilayer bubbles,
foam shadows, parallax and caustics. Added FixDecalsBias parameter to reduce z-fighting
for tires and feet decals which looks wrong at the shore (other decals not modified yet).
Added wetness properties for rain reflection.

Version 0.429:
Added detailed shadows and normal mapping shadows effects. Added compatibility of rain
reflections with VisualV mod.

Version 0.425:
Decreased loading times of presets. Added HighResolutionScaling parameter to enblocal.ini
for increasing size of editor if using very high resolutions.

Version 0.387:
Added rain reflections effect. Added int UIHidden=1 annotation support to parameters of
shaders to not display them in editor, but access via enbseries sdk.

Version 0.351:
Added skylighting effect, parameters for natural ambient light, sun rays, game bloom
and lens effects. Fixed various bugs.
Added higher quality ssao/ssil effect switched by new parameter. Increased performance
of ssao effect.

Version 0.350:
Added external shaders for post processing effects like in Skyrim SE or Fallout 4 mod.
Added game bloom and game lens effects parameters for tweaking to enbseries.ini.
Fixed no antialiasing for post processing shaders.

Version 0.275:
Added high quality antialiasing for vehicles as new parameter in enblocal.ini and it's
require msaa to be enabled in game video options. Fixed bug with midnight time of the
day reading.

Version 0.274:
Added programmable external shader for light sprites enblightsprite.fx, check shader
editor window for parameters of example. Added two types of light sprites which
works only when external shader is disabled. Added IgnoreDamageLimits parameter
to enblocal.ini.

Version 0.273:
Added parameters for spot and vehicle lights. Added patched compiler library for
upcoming features of the mod.

Version 0.272:
Added parameters for clouds and vehicles. Added time of the day separation to
split parameters in to dawn, sunrise, day, sunset, dusk and night modes. Weather
parameters are not used yet, so ignore them.

Version 0.271:
Added controls of night sprites and some others. Added parameter to turn on high
quality antialiasing, which require msaa to be active in game video options.

Version 0.270:
Added fps limiter, forcing vsync, fix for moon lit direction, some sky and lights parameters.



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//INSTALL
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Extract files from folder WrapperVersion to your game folder, where game execution file exist.



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PROBLEMS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
If game crashing or work not as expected, make sure you are not running XFire, Afterburner,
EVGA, other kind of tools and overlays (crapware). Antiviruses and various fake boosters
also affect mod wrong way. NVidia GeForce Experience can produce issues with the mod,
same with Steam Overlay enabled in-game.



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
http://enbdev.com
Copyright (c) 2007-2018 Vorontsov Boris (ENB developer)



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//USED THIRD PARTY CODE/MIDDLEWARE AND THEIR LICENSES (THESE ARE NOT MOD LICENSES)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Using AntTweakBar
Copyright (C) 2005-2018 Philippe Decaudin
AntTweakBar web site: http://www.antisphere.com



Using 3Dmigoto
3Dmigoto authors: Chiri, Bo3b Johnson, Ulf Jalmgrant (AKA Flugan), Ian Munsie (AKA DarkStarSword)

The MIT License (MIT)

Copyright (c) 2014-2018 the 3Dmigoto project authors (see the file AUTHORS.txt
for a complete list)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
