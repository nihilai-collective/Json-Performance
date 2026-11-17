
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2551.85 | 0.0628612 | 5539.13ms | 94653 | 320 | 158225 | 35373.6 | 0.120654 | 1.96476 | 9.86479 | 1.56058 | 0.00580568 | 5.97577e-06 | 2.83932e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2067.07 | 0.0295819 | 6374.46ms | 94653 | 4890 | 816054 | 43669.5 | 0.0589885 | 2.43379 | 11.7149 | 1.85192 | 0.00669088 | 8.51242e-06 | 4.79202e-06 | 2(Loss) | true |
| Glaze | 1981.23 | 0.220178 | 6569.64ms | 94653 | 320 | 3.22031e+06 | 45561.6 | 0.0125501 | 2.54151 | 11.754 | 2.2347 | 0.00901319 | 8.28685e-06 | 3.86279e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1924.93 | 0.0217991 | 6667.49ms | 94653 | 1280 | 133759 | 46894.1 | 0.103481 | 2.62833 | 10.6729 | 2.02225 | 0.0072699 | 2.01063e-05 | 1.59547e-05 | 4(Loss) | true |
| simdjson (reflection) | 1827.32 | 0.120787 | 6954.96ms | 94653 | 80 | 284819 | 49399.3 | 0.0614004 | 2.76767 | 11.1051 | 1.90139 | 0.0044263 | 1.67718e-05 | 1.28099e-05 | 5(Loss) | true |
