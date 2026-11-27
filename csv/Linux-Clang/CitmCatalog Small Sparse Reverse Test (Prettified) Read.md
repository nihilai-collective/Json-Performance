
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5195.72 | 0.112403 | 903.223ms | 9739 | 640 | 2583.88 | 1787.59 | 0.238053 | 1.0015 | 4.65736 | 0.772256 | 0.00139356 | 1.01076e-05 | 9.62624e-07 | 1(Win) | true |
| simdjson (ondemand) | 5006.05 | 0.0300531 | 905.526ms | 9739 | 1280 | 397.949 | 1855.32 | 0.020806 | 1.05181 | 4.9616 | 0.714139 | 0.000854971 | 2.08569e-05 | 9.46581e-06 | 2(Loss) | true |
