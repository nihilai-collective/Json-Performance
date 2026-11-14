
----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4048.11 | 0.0412946 | 942.643ms | 9378 | 4890 | 4070.16 | 2209.32 | 0.0356897 | 1.29647 | 5.78482 | 0.924398 | 0.0011542 | 1.96256e-05 | 7.41412e-06 | 1(Win) | true |
| simdjson (ondemand) | 3671.25 | 0.0575475 | 958.608ms | 9378 | 640 | 1257.84 | 2436.1 | 0.0213538 | 1.42526 | 6.10035 | 0.928024 | 0.00113264 | 1.14963e-05 | 3.33227e-07 | 2(Loss) | true |
