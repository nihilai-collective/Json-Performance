
----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5232.54 | 0.0389294 | 5019.88ms | 500299 | 640 | 806437 | 91183.7 | 0.177113 | 0.981076 | 5.40903 | 0.739194 | 0.000951197 | 2.01442e-06 | 1.81142e-07 | 1(Win) | true |
| simdjson (ondemand) | 4927.64 | 0.0217488 | 5327.21ms | 500299 | 1280 | 567622 | 96825.6 | 0.0580273 | 1.04498 | 5.5135 | 0.724737 | 0.00121607 | 2.64685e-06 | 6.04326e-07 | 2(Loss) | true |
