
----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5482.74 | 0.143621 | 5383.13ms | 1151920 | 160 | 1.32496e+07 | 200366 | 0.325793 | 0.93756 | 5.08132 | 0.784265 | 0.00176267 | 0.0107859 | 1.74274e-05 | 1(Win) | true |
| Jsonifier (generic) | 5320.91 | 0.208746 | 5460.16ms | 1151920 | 1280 | 2.37749e+08 | 206460 | 0.0592816 | 0.959237 | 4.97644 | 0.804975 | 0.00148886 | 0.010072 | 4.51081e-06 | 2(Loss) | true |
