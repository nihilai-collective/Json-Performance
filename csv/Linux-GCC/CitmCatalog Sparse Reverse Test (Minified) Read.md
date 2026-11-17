
----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3070.33 | 0.0587032 | 8349.56ms | 500299 | 320 | 2.66294e+06 | 155398 | 0.0140205 | 1.66604 | 9.43971 | 1.76389 | 0.0021343 | 2.01192e-05 | 5.12818e-06 | 1(Win) | true |
| simdjson (ondemand) | 2976.86 | 0.0427468 | 8546.03ms | 500299 | 640 | 3.00421e+06 | 160277 | 0.027974 | 1.70761 | 10.191 | 1.7313 | 0.00221567 | 0.000428581 | 9.83474e-06 | 2(Loss) | true |
