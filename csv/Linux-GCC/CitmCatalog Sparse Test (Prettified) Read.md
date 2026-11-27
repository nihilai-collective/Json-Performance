
----
### CitmCatalog Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9121.08 | 0.0614082 | 6552.93ms | 1151920 | 1280 | 7.00189e+06 | 120441 | 0.0821819 | 0.557856 | 2.86119 | 0.358334 | 0.000718729 | 0.00411291 | 1.32706e-05 | 1(Win) | true |
| simdjson (ondemand) | 7952.73 | 0.500114 | 7416.03ms | 1151920 | 2560 | 1.22177e+09 | 138136 | 0.610239 | 0.64207 | 3.21265 | 0.348681 | 0.000985982 | 0.0113226 | 6.15989e-06 | 2(Loss) | true |
