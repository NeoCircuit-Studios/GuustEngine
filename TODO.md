# GuustEngine Dev NeoCircuit-Studios (internal dev copy)
#### using KNOWN_ISSUES.md ID

# TODO:

## sdl3errorgameinput
- Windows x86/Win32 Release
- Engine will crash because of GameInput error in SDL3 
#### fix:
- Update SDL3:
- https://discourse.libsdl.org/t/sdl-fix-gameinputinitialize-crash-on-32bit/69624

## Add FakeNX
- the build tools and runtime for the switch 1 running homebrew.

## Add an timer to use
- an timer based on dt

## Color struct with pre-sets for drawing etc instead hardcoded nummers
- a struct for color e.g:
-                   Update(Color.Blue)
- but keep the option to use int's instead.

## add buildin math lib / func ..