
----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8658.68 | 0.111022 | 6959.57ms | 1151920 | 1280 | 2.53964e+07 | 126873 | 0.898299 | 0.587758 | 2.80513 | 0.372662 | 0.00087825 | 0.00709793 | 1.04805e-05 | 1(Win) | true |
| simdjson (ondemand) | 8374.55 | 0.105404 | 7184.68ms | 1151920 | 640 | 1.22354e+07 | 131178 | 0.160263 | 0.609965 | 3.06629 | 0.344492 | 0.00107393 | 0.00995323 | 1.63857e-06 | 2(Loss) | true |
