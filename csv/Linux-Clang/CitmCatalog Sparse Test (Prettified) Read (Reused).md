
----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8343.74 | 0.0680158 | 7138ms | 1151920 | 2560 | 2.05297e+07 | 131662 | 0.114611 | 0.609221 | 3.02512 | 0.350985 | 0.000888498 | 0.00737194 | 4.13271e-06 | 1(Win) | true |
| simdjson (ondemand) | 8295.36 | 0.0279878 | 7156.35ms | 1151920 | 2560 | 3.51683e+06 | 132430 | 0.328275 | 0.610838 | 3.06702 | 0.344856 | 0.00118782 | 0.00975455 | 4.78752e-06 | 2(Loss) | true |
