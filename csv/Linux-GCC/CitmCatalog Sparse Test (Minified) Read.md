
----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5489.99 | 0.0375292 | 9448.61ms | 500299 | 640 | 680825 | 86907.6 | 0.000871967 | 0.937647 | 4.98844 | 0.721119 | 0.000937005 | 2.34235e-05 | 6.02765e-07 | 1(Win) | true |
| simdjson (ondemand) | 4882.86 | 0.0484426 | 5370.95ms | 500299 | 640 | 1.43399e+06 | 97713.8 | 0.0501788 | 1.04685 | 5.64612 | 0.724185 | 0.00103386 | 3.35768e-05 | 7.71414e-07 | 2(Loss) | true |
