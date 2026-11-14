
----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8743.14 | 0.0960871 | 6787.86ms | 1151920 | 320 | 4.66434e+06 | 125648 | 0.0501155 | 0.581577 | 2.88345 | 0.336247 | 0.000608517 | 0.00471675 | 1.81762e-07 | 1(Win) | true |
| simdjson (ondemand) | 8031.66 | 0.0265779 | 7380.14ms | 1151920 | 1280 | 1.69155e+06 | 136778 | 0.0616106 | 0.638745 | 3.21565 | 0.347607 | 0.000869515 | 0.00530305 | 1.77421e-06 | 2(Loss) | true |
