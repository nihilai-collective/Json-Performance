
----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7739.43 | 0.128717 | 836.077ms | 9739 | 30 | 71.5816 | 1200.07 | 0.0250049 | 0.678865 | 2.95379 | 0.391519 | 0.000554472 | 1.36907e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 7202.61 | 0.0527972 | 852.333ms | 9739 | 4890 | 2266.62 | 1289.51 | 0.149134 | 0.737485 | 3.2834 | 0.359585 | 0.000952803 | 8.10521e-06 | 2.30977e-06 | 2(Loss) | true |
