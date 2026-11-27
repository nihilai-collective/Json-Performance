
----
### Github Events Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5468.71 | 0.0883419 | 753.178ms | 2158 | 320 | 35.3685 | 376.328 | 0.000830399 | 1.04625 | 3.8531 | 0.57924 | 0.000926784 | 1.01367e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4928.23 | 0.213827 | 761.551ms | 2158 | 80 | 63.7873 | 417.6 | 0.221996 | 1.14534 | 4.2507 | 0.572289 | 0.000463392 | 0 | 0 | 2(Loss) | true |
