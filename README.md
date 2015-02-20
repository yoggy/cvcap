cvcap
====
simple capture program.

install
----
    $ sudo apt-get install libopencv-dev libboost-all-dev build-essential cmake
    $ cd ~
    $ mkdir work
    $ cd work
    $ git clone https://github.com/yoggy/cvcap.git
    $ cd cvcap
    $ cmake .
    $ make
    $ sudo make install
    
usage
----
    $ ./cvcap --help
    cvcap options:
      -h [ --help ]                      show help
      -r [ --resolution ] arg (=640x480) resolution
      -c [ --camera ] arg (=0)           capture device number
      -f [ --filename ] arg (=image.jpg) capture image filename

