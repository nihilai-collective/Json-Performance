
----
### CitmCatalog Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5108.47 | 0.229734 | 811.531ms | 5092 | 30 | 143.076 | 950.6 | 0.122579 | 1.03342 | 4.64513 | 0.716025 | 0.00125687 | 1.30924e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4431.2 | 0.0840859 | 832.597ms | 5092 | 1280 | 1086.9 | 1095.89 | 0.156725 | 1.20526 | 5.2936 | 0.663002 | 0.00142181 | 1.91784e-05 | 7.05764e-06 | 2(Loss) | true |
