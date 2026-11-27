
----
### Canada Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5039.72 | 0.11562 | 801.637ms | 4630 | 1280 | 1313.48 | 876.142 | 0.109977 | 1.07035 | 5.16436 | 0.840605 | 0.000647948 | 3.10475e-05 | 1.58612e-05 | 1(Win) | true |
| simdjson (ondemand) | 4649.52 | 0.0689493 | 811.559ms | 4630 | 4890 | 2096.6 | 949.671 | 0.00334366 | 1.15413 | 5.59114 | 0.820086 | 0.000648257 | 1.66073e-05 | 4.19598e-06 | 2(Loss) | true |
