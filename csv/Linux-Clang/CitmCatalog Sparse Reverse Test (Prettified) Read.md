
----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5517.66 | 0.241726 | 5292.47ms | 1151920 | 1280 | 2.96478e+08 | 199098 | 0.071902 | 0.927002 | 4.84651 | 0.82725 | 0.00151077 | 0.00829502 | 1.06093e-05 | 1(Win) | true |
| simdjson (ondemand) | 5445.2 | 0.549621 | 5397.59ms | 1151920 | 320 | 3.93455e+08 | 201748 | 0.251845 | 0.934425 | 5.08083 | 0.783871 | 0.0016057 | 0.0110155 | 4.07472e-06 | 2(Loss) | true |
