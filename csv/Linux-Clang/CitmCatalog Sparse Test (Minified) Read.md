
----
### CitmCatalog Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5343.27 | 0.0541898 | 9674.84ms | 500299 | 640 | 1.49851e+06 | 89294 | 0.0164827 | 0.957279 | 4.95019 | 0.787881 | 0.000977725 | 3.46793e-05 | 3.12907e-05 | 1(Win) | true |
| simdjson (ondemand) | 4848.81 | 0.0318393 | 5403.97ms | 500299 | 1280 | 1.2564e+06 | 98399.8 | 0.038319 | 1.04516 | 5.51377 | 0.723761 | 0.00111258 | 1.09981e-05 | 4.95953e-06 | 2(Loss) | true |
