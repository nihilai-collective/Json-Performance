
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2194.26 | 0.0895435 | 3663.4ms | 53331 | 4890 | 2.10649e+06 | 23178.8 | 0.391582 | 2.2972 | 7.62668 | 1.26677 | 0.00985683 | 0.000114284 | 7.86001e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2083.23 | 0.197075 | 3544.83ms | 53331 | 1280 | 2.96318e+06 | 24414.2 | 0.1131 | 2.43369 | 8.41381 | 1.38311 | 0.00874978 | 0.000152424 | 0.000102119 | 2(Loss) | true |
| Glaze | 1895.99 | 0.0882148 | 4036.55ms | 53331 | 2560 | 1.43354e+06 | 26825.2 | 0.0275653 | 2.6632 | 9.42793 | 1.73162 | 0.0175186 | 7.94713e-05 | 4.6672e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1141.99 | 0.104481 | 5770.45ms | 53331 | 1280 | 2.77154e+06 | 44536.8 | 0.256753 | 4.42366 | 13.4214 | 2.32271 | 0.0108977 | 3.01332e-05 | 1.22027e-05 | 4(Loss) | true |
