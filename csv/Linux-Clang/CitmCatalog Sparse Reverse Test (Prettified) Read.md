
----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5453.79 | 0.0643732 | 5341.92ms | 1151920 | 160 | 2.69017e+06 | 201430 | 0.00938689 | 0.92745 | 5.08125 | 0.784306 | 0.00174341 | 0.00904946 | 1.72267e-05 | 1(Win) | true |
| Jsonifier (generic) | 5305.4 | 0.11577 | 5467.09ms | 1151920 | 320 | 1.83887e+07 | 207064 | 0.0785142 | 0.953455 | 4.97646 | 0.804974 | 0.00145868 | 0.00510395 | 4.70899e-05 | 2(Loss) | true |
