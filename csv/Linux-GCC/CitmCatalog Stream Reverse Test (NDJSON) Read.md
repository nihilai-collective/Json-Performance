
----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 855.354 | 0.146346 | 8144.06ms | 4525120 | 40 | 2.18068e+09 | 5.04527e+06 | 0.264575 | 5.95488 | 30.1097 | 6.04114 | 0.015385 | 0.077707 | 0.00491607 | 1(Win) | true |
| simdjson (ondemand) | 594.918 | 0.715874 | 5298.85ms | 4525120 | 30 | 8.08986e+10 | 7.25393e+06 | 0.0214798 | 8.52668 | 41.2329 | 8.13681 | 0.0254736 | 0.0767877 | 0.00884657 | 2(Loss) | true |
