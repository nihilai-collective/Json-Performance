
----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2935.82 | 0.0878749 | 8736.83ms | 500299 | 640 | 1.3053e+07 | 162517 | 0.0539583 | 1.7372 | 9.78511 | 1.76254 | 0.00210328 | 0.00272172 | 1.04531e-05 | 1(Win) | true |
| simdjson (ondemand) | 2861.72 | 0.178995 | 8857.86ms | 500299 | 160 | 1.42498e+07 | 166726 | 0.276556 | 1.77169 | 10.0933 | 1.7228 | 0.00244837 | 0.00214397 | 1.36169e-06 | 2(Loss) | true |
