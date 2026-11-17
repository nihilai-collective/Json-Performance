
----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1478.55 | 0.11799 | 9618.48ms | 1151920 | 160 | 1.22965e+08 | 742996 | 0.218483 | 3.42934 | 16.281 | 3.30691 | 0.00882335 | 0.0397234 | 4.7551e-05 | 1(Win) | true |
| simdjson (ondemand) | 946.652 | 0.157464 | 7457.56ms | 1151920 | 30 | 1.00172e+08 | 1.16047e+06 | 0.1566 | 5.37337 | 28.3071 | 5.69846 | 0.0148778 | 0.080316 | 0.000118845 | 2(Loss) | true |
