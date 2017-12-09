# IProc

A dynamic library for image processing. To Extract the pixel map of the image. Support PNG, JPG, TIF and BMP file formats. Inbuilt methods for resizing, croppping, grayscale, binary.

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
ip.readImage("");
```
*getting the pixel of position (x,y)*
```
RGBApixel pix = ip.getPixel(10,10);
```
*set a pixel at position (x,y)*
```
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
std::cout<<"Image height: "<<imgData.imgHeight;
std::cout<<"Image width: "<<imgData.imgWidth;
```
*resize the image*
```
imgData.resizeImage(100,20);
```
*get the grayscale pixels of the image*
```
imgData.grayscale();
```
*crop the image*
```
imgData.crop(20,30,80,100);
```
*get the binary pixel map of the image*
```
imgData.binary(100);
```
*write image to a target file*
```
imgData.writeImage("");
```
