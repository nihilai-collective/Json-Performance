
----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8000.47 | 0.0454088 | 828.975ms | 9739 | 4890 | 1358.9 | 1160.91 | 0.276668 | 0.667262 | 3.14262 | 0.376836 | 0.000660784 | 1.54125e-05 | 4.49356e-06 | 1(Win) | true |
| simdjson (ondemand) | 7270.3 | 0.0274844 | 841.67ms | 9739 | 2560 | 315.6 | 1277.5 | 0.0899689 | 0.730853 | 3.28278 | 0.359996 | 0.000833873 | 1.28751e-05 | 2.04558e-06 | 2(Loss) | true |
