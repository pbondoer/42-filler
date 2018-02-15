# Filler @ 42
 Will you be the best?

The goal of this project is to code an AI for the game of Filler, for which we
have a virtual machine.

The attached Makefile will compile my player `free_hugs`.

## Compiling and running
First of all run `git submodule init`. Then run `make` to obtain the player.
To see it in action, run the VM (you will need to download it):

```
./res/filler_vm -f res/maps/map00 -p1 filler -p2 res/players/superjeannot.filler
```

## VM GUI wrapper
There's a GUI wrapper included in the subfolder `gui`.
See `gui/README.md`.

## Improvements
This isn't perfect. Some improvements I could do in the future:

* Filler's VM wraps the map around, so there's ways to take advantage of that
* A heatmap distance algorithm would probably work better than the naive
  implementation I did

## License
`free_hugs` is under the **GNU General Public License 3.0**.
