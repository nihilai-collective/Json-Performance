
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2734.71 | 0.130635 | 1229.26ms | 11579 | 30 | 834.754 | 4037.93 | 0.173879 | 1.90511 | 9.08084 | 1.92236 | 0.0035812 | 0.000109393 | 5.18179e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2610.24 | 0.109348 | 1247.45ms | 11579 | 320 | 6847.81 | 4230.48 | 0.0381755 | 1.95534 | 8.8081 | 1.53787 | 0.00241412 | 1.56533e-05 | 3.77839e-06 | 2(Loss) | true |
| simdjson (reflection) | 2002.17 | 0.129746 | 1401.29ms | 11579 | 40 | 2048.28 | 5515.32 | 0.0464074 | 2.54561 | 10.9242 | 1.8455 | 0.0028651 | 3.02271e-05 | 4.31816e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1783.8 | 0.0483348 | 1449.58ms | 11579 | 4890 | 43780.5 | 6190.5 | 0.084338 | 2.85974 | 11.987 | 2.14647 | 0.00168186 | 5.64452e-05 | 2.7834e-05 | 4(Loss) | true |
| Glaze | 1668.34 | 0.0534453 | 1475.74ms | 11579 | 2560 | 32035.4 | 6618.89 | 0.0342886 | 3.08822 | 13.5416 | 2.44529 | 0.00469094 | 7.3375e-05 | 3.17452e-05 | 5(Loss) | true |
