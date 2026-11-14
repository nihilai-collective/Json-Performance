
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3168.03 | 0.0522628 | 867.378ms | 5092 | 2560 | 1642.95 | 1532.85 | 0.0474985 | 1.66602 | 7.65436 | 1.3586 | 0.00337931 | 1.28111e-05 | 3.83567e-07 | 1(Win) | true |
| simdjson (ondemand) | 3143.25 | 0.0366994 | 868.526ms | 5092 | 4890 | 1571.97 | 1544.93 | 0.20681 | 1.67944 | 8.2117 | 1.28456 | 0.00317247 | 1.58635e-05 | 6.42573e-07 | 2(Loss) | true |
