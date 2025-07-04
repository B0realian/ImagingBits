# Imaging to Bits
A small command-line program I wrote to inline text bitmap into another project. It uses the ubiquitous STB image library to load an image and will then create a .txt called array.txt containing the image's alpha, either in bits (default) or bytes (if specified).

PLEASE NOTE that I was too lazy to remove the last comma from array.txt in code, figuring it is far easier to do manually from a text editor or your IDE.

If you use default settings, alpha will be either 1 or 0, giving the resulting image a pixelated appearance (but also shrinking the image to 8 pixels per byte). If you want a smoother appearance, i.e. wanting more rounded glyphs, save the alpha in bytes instead. Please remember that if you save alpha in bits, you will have to unpack the data in your project (code example provided below).

## Example case
Using a monospaced font is highly recommended for ease of integration into your project. I picked Cascadia and made a .png with GIMP

![Symbols](bmtxt-cascadia.png "ASCII 32 - 128.")

in ASCII-order (definitely recommended). Although it is simpler to have all glyphs in one line instead of three, I wanted to stress-test my setup to make sure everything worked as I imagined it would. To see the result of Cascadia and scrutinize the code using the array, have a look at Mesh2Image [github.com/B0realian/MeshToImage/](https://github.com/B0realian/MeshToImage).
To see what the resulting array.txt looks like for the image above, look at cascadia-array.txt in the root of this repo. Incidentally, I save the alpha as represented by bits in a separate .txt for debugging purposes, which you can see in bytes_blueprint.txt.

More to come.
