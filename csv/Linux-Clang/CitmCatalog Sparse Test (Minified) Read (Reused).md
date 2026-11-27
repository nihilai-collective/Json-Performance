
----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5402.37 | 0.0314524 | 9592.87ms | 500299 | 4890 | 3.77317e+06 | 88317.2 | 0.15515 | 0.943519 | 4.92123 | 0.781097 | 0.000939359 | 1.34316e-05 | 9.04163e-06 | 1(Win) | true |
| simdjson (ondemand) | 4916.13 | 0.0279132 | 5330.08ms | 500299 | 1280 | 939379 | 97052.3 | 0.120136 | 1.03181 | 5.48485 | 0.716999 | 0.00108486 | 1.21021e-05 | 8.88531e-06 | 2(Loss) | true |
