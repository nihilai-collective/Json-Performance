
----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5441.51 | 0.0729902 | 808.784ms | 5092 | 320 | 135.774 | 892.419 | 0.191527 | 0.98987 | 4.52003 | 0.689513 | 0.00141582 | 8.59191e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4467.72 | 0.206192 | 832.447ms | 5092 | 30 | 150.685 | 1086.93 | 0.0767271 | 1.17524 | 5.17145 | 0.637471 | 0.0018133 | 1.30924e-05 | 0 | 2(Loss) | true |
