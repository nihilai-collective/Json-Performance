
----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1693.55 | 0.128102 | 8757.08ms | 4525120 | 80 | 8.52435e+08 | 2.54819e+06 | 0.374522 | 2.9748 | 14.9125 | 2.63894 | 0.00995906 | 0.0769634 | 0.00229837 | 1(Win) | true |
| simdjson (ondemand) | 1348.83 | 0.115769 | 5176.89ms | 4525120 | 80 | 1.09754e+09 | 3.19944e+06 | 0.275134 | 3.73654 | 16.265 | 2.70299 | 0.0148897 | 0.0765659 | 0.00492462 | 2(Loss) | true |
