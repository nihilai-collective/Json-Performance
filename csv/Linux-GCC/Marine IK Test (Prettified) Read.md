
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2228.13 | 0.079272 | 9786.58ms | 7351818 | 160 | 9.95559e+08 | 3.14669e+06 | 0.60712 | 2.2628 | 9.3265 | 1.82015 | 0.0107838 | 0.0588036 | 0.00457712 | 1(Win) | true |
| simdjson (ondemand) | 2139.38 | 0.170741 | 10190.7ms | 7351818 | 80 | 2.50485e+09 | 3.27723e+06 | 0.193511 | 2.35415 | 9.73245 | 1.61549 | 0.0108547 | 0.0590222 | 0.00822112 | 2(Loss) | true |
