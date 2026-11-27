
----
### Random Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3112.53 | 0.0593707 | 971.711ms | 8150 | 2560 | 5626.95 | 2497.15 | 0.00550659 | 1.67668 | 7.53975 | 1.35742 | 0.00184131 | 2.5115e-05 | 7.62078e-06 | 1(Win) | true |
| simdjson (ondemand) | 2375.88 | 0.115089 | 1051.2ms | 8150 | 40 | 567.015 | 3271.4 | 0.103823 | 2.19604 | 8.94049 | 1.51693 | 0.00414724 | 4.90798e-05 | 1.53374e-05 | 2(Loss) | true |
