# Font-extractor

Semi-automatic extraction of characters for the generation of images and old documents


## Manual installation
```
// Opencv installation
#Ubuntu Linux distribution
sudo apt-get install libopencv-dev
    
#MAC distribution (with Homebrew)
brew install opencv

// Libnavajo installation
git clone https://github.com/titi38/libnavajo.git
cd libnavajo
cmake .
make
sudo make install
    
// Font-extractor installation
git clone https://github.com/rtisne/Pdp.git
cd Pdp/server
make
```

## Docker installation
// TO DO

## How to use
To lauch the server, go into the server folder and make:
```    
./main
```
The server will be run by default on port 8080.
You can change the port in the file libnavajo/src/WebServer.cc of libnavajo

```#define DEFAULT_HTTP_PORT 8080```

If you are in local, you can access to the server throught: http://localhost:8080

## Demo
The application is host online :\s\s
https://intranet.iut.u-bordeaux.fr/navajo/

## Development
Developing by:
* [Tristan Autret](https://github.com/tautret)
* [Anthony Boschet](https://github.com/aboschet)
* [Thomas Labrousse](https://github.com/Shqrk)
* [Romain Tisné](https://github.com/rtisne)

[Report link]()