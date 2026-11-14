
----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7831.72 | 0.058654 | 833.219ms | 9739 | 160 | 77.4157 | 1185.92 | 0.0410903 | 0.681198 | 3.2068 | 0.390492 | 0.000576933 | 2.567e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 7071.26 | 0.0388231 | 843.167ms | 9739 | 2560 | 665.665 | 1313.46 | 0.0682367 | 0.751251 | 3.34665 | 0.373344 | 0.000612309 | 9.0246e-06 | 1.52416e-06 | 2(Loss) | true |
