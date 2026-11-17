
----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4280.27 | 0.119281 | 1285.2ms | 25388 | 320 | 14568.2 | 5656.63 | 0.00480654 | 1.21052 | 5.69474 | 0.909879 | 0.00155795 | 4.30814e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3983.9 | 0.0566757 | 1330.52ms | 25388 | 640 | 7593.01 | 6077.44 | 0.0524463 | 1.30078 | 5.98472 | 0.912715 | 0.00148582 | 7.20074e-06 | 1.35399e-06 | 2(Loss) | true |
