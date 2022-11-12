# Ogre3D-FPS
## Description
A small FPS demo made with Ogre3D rendering engine in C++.

## Controls
<b>W-A-S-D</b> to move around.<br/>
<b>Space</b> to shoot the projectile.

## Set-up
In order to run the source code, you will first need to build Ogre3D engine from source and set it up and then proceed to place both, the engine folder and the Ogre3D FPS project folder, within the same folder.
To avoid any further linking issues make sure to rename your Ogre3D engine folder to OGRE or manually adjust the paths to dependencies within the Ogre3D FPS project settings. You're now all set, but make sure to run the Ogre3D FPS in Release configuration. This is due to a Ogre3D issue that prevents you from being able to run both, Release and Debug configurations, within the same project.
