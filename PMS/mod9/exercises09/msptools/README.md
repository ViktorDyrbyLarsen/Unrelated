# MSP Tools

Data structures and routines for dynamic arrays, multidimensional arrays, and
sparse matrices.

## License

BSD 2-Clause License 

## Getting Started

```
$ cd msptools
$ make
$ make test
```

## Importing and exporting two-dimensional arrays 

### MSP Tools

```c
array2d_t *A = array2d_alloc((size_t []){4,5}, RowMajor);
if (!A) exit(EXIT_FAILURE);
/* ... fill array ... */
array2d_to_file("A.txt", A);                // export A to a text file
array2d_dealloc(A);

array2d_t *B = array2d_from_file("A.txt");  // import array from a text file
if (!B) exit(EXIT_FAILURE);
/* ... do something with array ... */
array2d_dealloc(B);
```

### Python/Numpy

```py
import numpy as np
A = np.random.randn(4,5)
np.savetxt('A.txt',A)      # export A to a text file

B = np.loadtxt('A.txt')    # import array from a text file
```

### MATLAB

```matlab
A = randn(4,5);
save('A.txt','A','-ascii','-double');  % export A to a text file

B = load('A.txt');                     % import array from a text file
```

### Julia

```julia
using Random, DelimitedFiles
A = Random.randn(4,5)
open("A.txt", "w") do io   # export A to a text file
    writedlm(io, A)
end;

B = readdlm("A.txt")       # import array from a text file
```


