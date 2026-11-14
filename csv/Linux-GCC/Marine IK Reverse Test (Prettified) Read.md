
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1309.15 | 0.291058 | 8065.23ms | 7351818 | 40 | 9.71916e+09 | 5.35555e+06 | 0.00736113 | 3.88213 | 16.0203 | 3.37909 | 0.0110902 | 0.185536 | 0.00532174 | 1(Win) | true |
| simdjson (ondemand) | 898.052 | 0.258165 | 5441.68ms | 7351818 | 30 | 1.21872e+10 | 7.80716e+06 | 0.0458365 | 5.69265 | 26.4531 | 5.32127 | 0.0126643 | 0.43518 | 0.00699387 | 2(Loss) | true |
