
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8574.56 | 0.102506 | 767.818ms | 3223 | 30 | 4.05057 | 358.467 | 0.287436 | 0.670483 | 1.96153 | 0.318027 | 0.00031027 | 9.3081e-05 | 6.2054e-05 | 1(Win) | true |
| simdjson (reflection) | 6552.67 | 0.0420783 | 780.296ms | 3223 | 160 | 6.23333 | 469.075 | 0.165492 | 0.838729 | 2.52249 | 0.283276 | 0.00031027 | 2.13311e-05 | 0 | 2(Loss) | true |
| Glaze | 4104.41 | 0.0727343 | 803.793ms | 3223 | 4890 | 1450.79 | 748.875 | 0.0682012 | 1.29932 | 4.40242 | 0.633571 | 0.000310841 | 4.77143e-05 | 2.0304e-05 | 3(Loss) | true |
