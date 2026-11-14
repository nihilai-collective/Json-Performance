
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 546.705 | 0.0897868 | 1528.12ms | 4604 | 320 | 16639.5 | 8031.24 | 0.0831605 | 9.4587 | 38.7164 | 7.48436 | 0.00837519 | 6.58395e-05 | 2.78291e-05 | 1(Win) | true |
| Jsonifier (generic) | 533.116 | 0.143392 | 1547.8ms | 4604 | 320 | 44630.1 | 8235.95 | 0.13743 | 9.69526 | 37.3159 | 7.81277 | 0.0104108 | 6.58395e-05 | 3.05441e-05 | 2(Loss) | true |
