
----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5640.95 | 0.208528 | 5148.93ms | 1151920 | 640 | 1.05548e+08 | 194747 | 0.276838 | 0.901128 | 4.81196 | 0.789576 | 0.00111403 | 0.00487323 | 7.30302e-06 | 1(Win) | true |
| simdjson (ondemand) | 5596.69 | 0.0352964 | 5219.08ms | 1151920 | 1280 | 6.14403e+06 | 196287 | 0.136969 | 0.911426 | 5.17859 | 0.782349 | 0.00144117 | 0.00471934 | 2.55212e-06 | 2(Loss) | true |
