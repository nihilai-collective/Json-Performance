
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16565.6 | 0.0691335 | 766.334ms | 6938 | 4890 | 372.856 | 399.418 | 0.0559789 | 0.337405 | 0.987028 | 0.148025 | 0.000144163 | 1.99547e-05 | 8.51833e-06 | 1(Win) | true |
| Glaze | 3470.9 | 0.361415 | 913.855ms | 6960 | 1280 | 61144.3 | 1912.35 | 0.722726 | 1.51006 | 3.91135 | 0.627299 | 0.000354256 | 3.62563e-05 | 1.77353e-05 | 2(Loss) | true |
| simdjson (reflection) | 502.075 | 0.0766491 | 2058.31ms | 6938 | 4890 | 498949 | 13178.5 | 0.0433204 | 10.0977 | 38.6877 | 7.24993 | 0.00725954 | 0.000180771 | 0.000102957 | 3(Loss) | true |
