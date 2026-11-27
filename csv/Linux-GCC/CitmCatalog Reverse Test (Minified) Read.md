
----
### CitmCatalog Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 728.681 | 0.0878707 | 8469.69ms | 500299 | 640 | 2.11862e+08 | 654776 | 0.0801823 | 6.99314 | 34.7986 | 7.24304 | 0.021171 | 0.0195459 | 0.000199097 | 1(Win) | true |
| simdjson (ondemand) | 419.426 | 0.209927 | 7272.32ms | 500299 | 80 | 4.56223e+08 | 1.13756e+06 | 0.311136 | 12.1421 | 63.4939 | 13.1108 | 0.0361094 | 0.0305774 | 0.000114856 | 2(Loss) | true |
