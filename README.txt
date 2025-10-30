Metis 5.2.1 with various modifications to be used by HiGHS.

The following changes were made by Alexis Montoison, Ivet 
Galabova and Filippo Zanetti.

- Include GKlib source code to simplify the build for HiGHS 
  users. Build system modified accordingly.

- Various changes to improve the build system on Windows.

- The original random number generator is not thread-safe 
  because it relies on a static state variable. The random 
  number generator rand has been replaced with rand_r, 
  which stores the state in a local variable. Since rand_r 
  is not defined in all C implementations, a  local version 
  my_rand_r has been added, similar to the GNU reference 
  implementation of rand_r. The randon number generator state
  is stored in the ctrl struct and passed as an argument to 
  the GKlib functions that need it.

- Any `static __thread` variable has been removed, to avoid
  potential issues with thread safety. This required to 
  remove `gkmcore` in GKlib/memory.c and to remove the signal 
  handling in GKlib/error.c.