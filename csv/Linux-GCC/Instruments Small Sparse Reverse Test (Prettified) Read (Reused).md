
----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4857.66 | 0.149977 | 876.506ms | 7932 | 2560 | 13963.7 | 1557.24 | 0.0216525 | 1.07265 | 4.89397 | 0.782653 | 0.000789523 | 1.57097e-05 | 2.06836e-06 | 1(Win) | true |
| simdjson (ondemand) | 4083.4 | 0.14054 | 932.928ms | 7932 | 320 | 2169.05 | 1852.51 | 0.0420215 | 1.28406 | 5.97554 | 0.896369 | 0.00162672 | 1.4577e-05 | 0 | 2(Loss) | true |
