# Pattern-Recognition-and-Image-Reader

This project is split in two parts:

* **2D Pattern Recognition** - We have developed the 2D Pattern Recognition algorithm in two different implementations:
the first one written in C++ using OpenMP for enabling parallel execution, the second one based on GPU written with CUDA.  
    - The CUDA implementation is in directory ```CUDA src```.
    - The C++ (with OpenMP) implementaiton is the executable ```Pattern_Recognition``` in the directory ```C++ src```\
    For this project the source files are ```mainPR.cpp``` ```Matrix.h```
```Utils.h``` ```PatternRecognition.h```.

    For more details about algorithm and performance comparison see [Pattern Recognition paper](https://github.com/ABaldrati/Pattern-Recognition-and-Image-Reader/blob/master/Paper/Image_Reader_paper.pdf)

* **Image Reader and Asynchronous execution** - Firstly we have developed a simple Image Reader and then we have tried to exploit the power of asynchronous execution chaining together such Image Reader and the 2D Pattern Recognition algorithm.

     - The Image Reader implementation is the executable ```Image_Reader``` in ```C++ src``` \
    For this project the source files are ```mainIM.cpp``` ```ImageReader.h``` ```ImageReader.cpp```
    - The Full exectuion (which chains together the Image Reader and the 2D Pattern Recognition) is the executable
    ```Full_Execution``` in ```C++ src```.\
    For this project the sources files are all the files contained in ```C++ src```
    
    For more details about algorithm and performance comparison see [Image Reader paper](https://github.com/ABaldrati/Pattern-Recognition-and-Image-Reader/blob/master/Paper/Image_Reader_paper.pdf)


## Built With

* [OpenCV](https://opencv.org/) - For managing images
* [Boost](https://www.boost.org/) - Used for asynchronous managment of threads
* [OpenMP](https://www.openmp.org/) - Used for enabling parallelism
* [CUDA](https://developer.nvidia.com/cuda-zone) - used for enabling GPGPU programming

## Authors

* **Alberto Baldrati**

## Acknowledgments
* Project developed for *Parallel Computing* Informatic Engineering master degree course taught by professor [Marco Bertini](http://www.micc.unifi.it/bertini/) at the [University of Florence](https://www.unifi.it/changelang-eng.html), 
