
----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7716.1 | 0.0545446 | 832.606ms | 9739 | 4890 | 2107.88 | 1203.7 | 0.0928485 | 0.6883 | 3.08286 | 0.373139 | 0.000665488 | 1.14019e-05 | 9.86903e-07 | 1(Win) | true |
| simdjson (ondemand) | 6977.17 | 0.0257416 | 848.072ms | 9739 | 1280 | 150.298 | 1331.17 | 0.0497928 | 0.760423 | 3.47633 | 0.374987 | 0.000665334 | 7.13947e-06 | 8.02187e-07 | 2(Loss) | true |
