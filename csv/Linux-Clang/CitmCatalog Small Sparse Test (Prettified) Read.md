
----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7605.61 | 0.107648 | 843.581ms | 9739 | 2560 | 4423.98 | 1221.18 | 0.00729367 | 0.700197 | 3.0192 | 0.405381 | 0.00072241 | 2.03756e-05 | 7.46034e-06 | 1(Win) | true |
| simdjson (ondemand) | 7066.03 | 0.0443109 | 849.321ms | 9739 | 640 | 217.11 | 1314.43 | 0.191256 | 0.751957 | 3.34726 | 0.372934 | 0.000576612 | 1.29954e-05 | 4.81312e-06 | 2(Loss) | true |
