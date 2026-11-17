
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2068.31 | 0.152444 | 1180.38ms | 9739 | 320 | 14995.7 | 4490.54 | 0.331264 | 2.50877 | 10.279 | 1.65335 | 0.00181198 | 1.5402e-05 | 1.92525e-06 | 1(Win) | true |
| Jsonifier (generic) | 2040.84 | 0.140507 | 1183.03ms | 9739 | 320 | 13084.5 | 4550.98 | 0.145303 | 2.54302 | 10.2771 | 1.84824 | 0.00165732 | 4.20346e-05 | 2.21404e-05 | 2(Loss) | true |
