
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1595.1 | 0.15697 | 9687.41ms | 5212421 | 160 | 3.82872e+09 | 3.11638e+06 | 0.18402 | 3.15713 | 14.4215 | 2.86079 | 0.0103214 | 0.101567 | 0.00107828 | 1(Win) | true |
| simdjson (ondemand) | 1557.63 | 0.626771 | 9903.71ms | 5212421 | 160 | 6.40155e+10 | 3.19135e+06 | 0.0024851 | 3.22551 | 14.7124 | 2.67314 | 0.0104583 | 0.121099 | 0.00117534 | 2(Loss) | true |
