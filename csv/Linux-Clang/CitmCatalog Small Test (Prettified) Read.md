
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2046 | 0.0790437 | 1194.63ms | 9739 | 160 | 2060.03 | 4539.51 | 0.0316764 | 2.4938 | 10.2014 | 1.63833 | 0.00182706 | 8.34275e-06 | 2.567e-06 | 1(Win) | true |
| Jsonifier (generic) | 2024.33 | 0.117065 | 1197.4ms | 9739 | 320 | 9231.45 | 4588.11 | 0.0876499 | 2.51747 | 10.3433 | 1.86332 | 0.00185305 | 1.50811e-05 | 1.60437e-06 | 2(Loss) | true |
