
----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 696.037 | 0.0745847 | 8825.62ms | 500299 | 160 | 4.18229e+07 | 685484 | 0.0207698 | 7.36826 | 35.7032 | 7.46815 | 0.0208237 | 0.0161188 | 2.13872e-05 | 1(Win) | true |
| simdjson (ondemand) | 433.659 | 0.117464 | 6990.39ms | 500299 | 40 | 6.68085e+07 | 1.10023e+06 | 0.010255 | 11.8203 | 63.4971 | 13.0607 | 0.0322536 | 0.0202036 | 2.13372e-05 | 2(Loss) | true |
