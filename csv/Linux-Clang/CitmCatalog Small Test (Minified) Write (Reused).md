
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8435.56 | 0.207201 | 767.838ms | 3223 | 4890 | 2787.32 | 364.373 | 0.141102 | 0.672533 | 2.19516 | 0.372014 | 0.000311349 | 2.70931e-05 | 3.29939e-06 | 1(Win) | true |
| Glaze | 3054.13 | 0.396394 | 832.967ms | 3223 | 1280 | 20370.9 | 1006.4 | 0.402719 | 1.72233 | 4.65106 | 0.65252 | 0.000317299 | 8.36274e-05 | 2.08463e-05 | 2(Loss) | true |
