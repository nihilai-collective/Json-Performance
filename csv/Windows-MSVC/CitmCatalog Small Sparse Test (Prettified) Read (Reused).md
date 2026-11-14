
----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6966.35 | 0.122594 | 136.341ms | 9739 | 2560 | 6839.03 | 1333.24 | 0.0497833 | 0.430428 | 1(Win) | true |
| simdjson (ondemand) | 6125.53 | 0.136224 | 154.715ms | 9739 | 320 | 1365.2 | 1516.25 | 0.0823723 | 0.49027 | 2(Loss) | true |
