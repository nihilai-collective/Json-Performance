
----
### Instruments Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6807.45 | 0.112483 | 820.958ms | 7932 | 2560 | 3999.55 | 1111.22 | 0.0941227 | 0.788734 | 3.69201 | 0.400025 | 0.000641045 | 2.98928e-05 | 1.31489e-05 | 1(Win) | true |
| Jsonifier (generic) | 6769.32 | 0.0664821 | 822.115ms | 7932 | 640 | 353.236 | 1117.47 | 0.0456035 | 0.797615 | 3.53253 | 0.430408 | 0.00071132 | 5.71262e-06 | 1.96987e-07 | 2(Loss) | true |
