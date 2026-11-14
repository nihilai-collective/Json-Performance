
----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5393.68 | 0.0890636 | 761.071ms | 2821 | 2560 | 505.215 | 498.79 | 0.0877108 | 1.03283 | 3.83729 | 0.485289 | 0.000709522 | 2.7971e-05 | 8.16975e-06 | 1(Win) | true |
| simdjson (ondemand) | 4793.46 | 0.104484 | 773.456ms | 2821 | 320 | 110.042 | 561.247 | 0.0205972 | 1.15843 | 4.0787 | 0.43637 | 0.00106788 | 1.8832e-05 | 0 | 2(Loss) | true |
