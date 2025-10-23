Metis 5.1.0 with various modifications to be used by HiGHS.

The following changes were made by Alexis Montoison, Ivet Galabova and Filippo Zanetti.

- Changes to simplify the build on Windows. They are listed in the folder patches.

- The original random number generator is not thread-safe because it relies on a static state variable.
  The random number generator rand() has been replaced with rand_r, which stores the state in a local variable.
  Since rand_r is not defined in all C implementations, a local version my_rand_r has been added, similar to the GNU reference implementation of rand_r.
  Storing the random number generator state locally required changing the signature of many Metis functions to accomodate an extra parameter, including in the API.
  A suffix "_ts" has been added to the API to avoid conflicts with other potential Metis installations.
