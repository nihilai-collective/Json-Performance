
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1417.22 | 0.0620774 | 9596.12ms | 500299 | 160 | 6.98827e+06 | 336660 | 0.129165 | 3.56853 | 16.8416 | 3.12307 | 0.0118254 | 0.00646688 | 1.53033e-05 | 1(Win) | true |
| simdjson (ondemand) | 1273.17 | 0.17178 | 5255.9ms | 500299 | 30 | 1.24324e+07 | 374752 | 0.148358 | 3.97057 | 17.5034 | 2.72464 | 0.0157612 | 0.00938472 | 1.51909e-05 | 2(Loss) | true |
