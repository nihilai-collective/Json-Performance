
----
### Github Events Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6540.58 | 0.0761453 | 1686.47ms | 65103 | 160 | 8359.43 | 9492.59 | 0.0152115 | 0.790622 | 3.76803 | 0.585396 | 0.00132674 | 5.18409e-06 | 2.11204e-06 | 1(Win) | true |
| simdjson (ondemand) | 4657.56 | 0.0386565 | 2061.66ms | 65103 | 1280 | 33989 | 13330.4 | 0.047449 | 1.09119 | 5.06315 | 0.79491 | 0.00205676 | 1.52403e-05 | 8.95216e-06 | 2(Loss) | true |
