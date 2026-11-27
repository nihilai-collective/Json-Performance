
----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1538.71 | 0.0999428 | 9605.55ms | 1151920 | 640 | 3.25849e+08 | 713948 | 0.0899741 | 3.28933 | 16.0379 | 3.23343 | 0.00783699 | 0.0367437 | 7.76109e-05 | 1(Win) | true |
| simdjson (ondemand) | 950.305 | 0.19288 | 7570.41ms | 1151920 | 40 | 1.98862e+08 | 1.156e+06 | 0.23302 | 5.33585 | 28.6316 | 5.58462 | 0.0123912 | 0.0776756 | 0.000147211 | 2(Loss) | true |
