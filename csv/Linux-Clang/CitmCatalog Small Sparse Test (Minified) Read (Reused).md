
----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4936.61 | 0.0378802 | 813.186ms | 5092 | 640 | 88.8638 | 983.694 | 0.0136621 | 1.08608 | 4.8533 | 0.664768 | 0.000794445 | 1.56495e-05 | 6.13708e-07 | 1(Win) | true |
| simdjson (ondemand) | 4561.82 | 0.055769 | 819.93ms | 5092 | 2560 | 902.25 | 1064.51 | 0.0458166 | 1.17151 | 5.17046 | 0.637667 | 0.00083027 | 2.61593e-05 | 7.74806e-06 | 2(Loss) | true |
