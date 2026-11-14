
----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5476.82 | 0.0702831 | 5322.55ms | 1151920 | 40 | 794966 | 200583 | 0.198516 | 0.921927 | 5.0685 | 0.781332 | 0.00171462 | 0.00812635 | 1.77964e-05 | 1(Win) | true |
| Jsonifier (generic) | 5379.54 | 0.088705 | 5407.22ms | 1151920 | 640 | 2.10005e+07 | 204210 | 0.169094 | 0.940782 | 4.96371 | 0.801993 | 0.00142015 | 0.0041493 | 2.71503e-05 | 2(Loss) | true |
