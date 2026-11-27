
----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5568.06 | 0.0842733 | 5284.9ms | 1151920 | 80 | 2.2116e+06 | 197296 | 0.0172043 | 0.922051 | 4.83393 | 0.824304 | 0.00149295 | 0.00366785 | 2.47413e-06 | 1(Win) | true |
| simdjson (ondemand) | 5506.07 | 0.0632682 | 5299.08ms | 1151920 | 1280 | 2.03959e+07 | 199517 | 0.102951 | 0.923315 | 5.06834 | 0.780939 | 0.00159022 | 0.00984656 | 7.97514e-06 | 2(Loss) | true |
