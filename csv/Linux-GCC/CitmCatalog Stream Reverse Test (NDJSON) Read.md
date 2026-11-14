
----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 829.329 | 0.0608545 | 8142.32ms | 4525120 | 80 | 8.02199e+08 | 5.20359e+06 | 0.0991124 | 6.13616 | 30.6981 | 6.25099 | 0.0150874 | 0.0781591 | 0.00257119 | 1(Win) | true |
| simdjson (ondemand) | 633.045 | 0.0640905 | 10638.3ms | 4525120 | 80 | 1.5271e+09 | 6.81704e+06 | 0.149282 | 8.03196 | 41.2294 | 8.08443 | 0.0231619 | 0.0775056 | 0.00410365 | 2(Loss) | true |
