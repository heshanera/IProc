# IProc

A dynamic library for image processing. To Extract the pixel map of the image. Support PNG, JPG, TIF and BMP image file formats. Inbuilt methods for resizing, croppping, generating grayscale and binary images.

### Data Structures
`RGBAPixel` 
`ImageDataStruct`
```
struct RGBApixel {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 0;
};
```
```
struct ImageDataStruct {
    RGBApixel * imgPixArray;
    int imgWidth;
    int imgHeight;
};
```

### Methods
`int readImage(std::string);`<br>
`int writeImage(std::string);`<br>
`RGBApixel getPixel(int,int);`<br>
`ImageDataStruct getImageDataStruct();`<br>
`int setPixel(int,int,RGBApixel);`<br>
`int setImageDataStruct(ImageDataStruct);`<br>
`int resizeImage(int, int);`<br>
`int crop(int, int, int, int);`<br>
`int binary(int);`<br>
`int grayscale();`<br>



*reading the image file*
```
IProc ip;
ip.readImage("path/to/source/file.jpg");
```
*getting the pixel value*
```
// pixel in the position (x, y)
RGBApixel pix = ip.getPixel(10,10);
```
*set a pixel value*
```
// set the pixel at position (x, y)
RGBApixel pix;
pix.r = 100;
pix.g = 100;
pix.b = 100;
pix.a = 255;
ip.setPixel(10,15,pix);
```
*get the pixel map of the image*
```
ImageDataStruct imgData;
imgData = ip.getImageDataStruct();
// printing the height and width of the image
std::cout<<"Image height: "<<imgData.imgHeight;
std::cout<<"Image width: "<<imgData.imgWidth;
```
*resize the image*
```
// resize the image (width, height)
imgData.resizeImage(100,20);

// resize the image (width, auto)
imgData.resizeImage(100,-1);

// resize the image (auto, height)
imgData.resizeImage(-1,20);
```
*crop the image*
```
// crop the image (row1, col1, row2, col2);
imgData.crop(20,30,80,100);
```
*get the grayscale pixels of the image*
```
// convert the RGB values to grayscale intensity values
imgData.grayscale();
```
*get the binary pixel map of the image*
```
// convert the image in to a binary image (grayscale intensity value)
imgData.binary(125);
```
*write image to a target file*
```
// write image to a given path
imgData.writeImage("path/to/target/file.png");
```
