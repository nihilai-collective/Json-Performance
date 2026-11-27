
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5227.82 | 0.0671287 | 891.235ms | 9739 | 640 | 910.302 | 1776.62 | 0.000351793 | 1.00739 | 4.62193 | 0.758805 | 0.00187006 | 6.57793e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4803.33 | 0.0521624 | 910.738ms | 9739 | 2560 | 2604.35 | 1933.62 | 0.273046 | 1.09401 | 5.03183 | 0.719171 | 0.000930457 | 2.7515e-05 | 1.42388e-05 | 2(Loss) | true |
