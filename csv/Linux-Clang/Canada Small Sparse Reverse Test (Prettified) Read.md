
----
### Canada Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10327.7 | 0.0898519 | 816.653ms | 11579 | 1280 | 1181.41 | 1069.22 | 0.0280656 | 0.517265 | 2.71137 | 0.345367 | 0.000259562 | 8.7038e-06 | 1.34943e-07 | 1(Win) | true |
| simdjson (ondemand) | 9163.67 | 0.0364372 | 831.372ms | 11579 | 640 | 123.388 | 1205.04 | 0.00648276 | 0.581034 | 2.96088 | 0.361862 | 0.000264892 | 2.83379e-06 | 1.34943e-07 | 2(Loss) | true |
