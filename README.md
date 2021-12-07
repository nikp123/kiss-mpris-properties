# KISS MPRIS2 properties

This library is intended for those who want to retrieve audio player data simply,
without having to deal with D-Bus or anything low-level.

## Well how do I use it then????
The included directory [demo](demo) provides an example of how the library is used,
while the code might be dauting (for formatting reasons), the bit you actually
care or need to know about is the included header file
[kiss-mpris.h](src/kiss-mpris.h)

In C it is included as ``#include <kiss-mpris.h>`` if you've installed the
library or properly set include directories to the [src](src) folder in this
repo.

All you have is basically one function ``get_mpris_player_status()`` that retrieves
MPRIS properties in the ``mpris_properties`` type and metadata about the current
track in the ``mpris_metadata`` type.

In order to get accurate output data out of ``get_mpris_player_status`` you need
to specify options via the ``kiss_mpris_options`` type.

In it, you'll find ``player_names`` and ``player_count`` which are basically a
string array and a counter that specifies the names of the players you want to
**specifically** target for media data, however this is completely optional as you
can leave ``player_count`` set to 0 for it to find the first available player.

However, the status property does offer you a bit more flexibility, where you can
specify one of three options: ``MPRIS_PLAYER_MUST_BE_PLAYING``,
``MPRIS_PLAYER_ANY_PLAYING`` or ``MPRIS_PLAYER_ANY``

``MPRIS_PLAYER_MUST_BE_PLAYING`` tells this library to fetch by name WHILST
MAKING SURE THAT SAID PLAYER IS PLAYING AS WELL.

``MPRIS_PLAYER_ANY_PLAYING`` tells it to find any player that is currently playing.

And ``MPRIS_PLAYER_ANY`` is reserved for any player that is playing.

You give it those parameters, run the function, and do with the output data
whatever you want. Bonus points for no memory management 😄

Now you link against ``kiss-mpris``, and you're done, the libraries CMake file
is located [here](src/CMakeLists.txt).

## Installation (in case you want that)

This library can either be built and installed on the system using CMake, aka: 
```
git clone https://github.com/nikp123/kiss-mpris-properties
cd kiss-mpris-properties
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make install
```

And uninstalled with a:
```
cat install_manifest.txt | sudo xargs rm -
```

# License
A good 90% of the code here is straight up stolen from
[mpris-ctl](https://github.com/mariusor/mpris-ctl), so this project will use MIT
as well.

```
MIT License

Copyright (c) 2017 Marius Orcsik and 2021 Nikola Pavlica

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

