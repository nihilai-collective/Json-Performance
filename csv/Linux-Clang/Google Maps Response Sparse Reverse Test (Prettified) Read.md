
----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3273.89 | 0.12205 | 1464.07ms | 25388 | 320 | 26070.8 | 7395.46 | 0.0553243 | 1.55061 | 7.21636 | 1.2823 | 0.00328132 | 6.89302e-06 | 9.84717e-07 | 1(Win) | true |
| simdjson (ondemand) | 3224.15 | 0.0724889 | 1484.53ms | 25388 | 80 | 2370.61 | 7509.54 | 0.0241301 | 1.60667 | 7.32523 | 1.13782 | 0.00353612 | 8.3701e-06 | 3.44651e-06 | 2(Loss) | true |
