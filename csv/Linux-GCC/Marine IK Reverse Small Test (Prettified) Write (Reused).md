
----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6438.12 | 0.0949243 | 1093.64ms | 24579 | 4890 | 58408.2 | 3640.87 | 0.0520576 | 0.807678 | 1.86948 | 0.101184 | 0.000104558 | 1.43854e-05 | 6.26501e-06 | 1(Win) | true |
| Glaze | 3660.51 | 0.0807846 | 1373.45ms | 24579 | 4890 | 130862 | 6403.58 | 0.15178 | 1.41534 | 3.77273 | 0.441597 | 0.000267249 | 1.43688e-05 | 6.26501e-06 | 2(Loss) | true |
| simdjson (reflection) | 528.532 | 0.139694 | 5237.21ms | 24893 | 2560 | 1.00788e+07 | 44916.6 | 0.1234 | 9.64083 | 36.7977 | 6.03708 | 0.00725508 | 0.000100665 | 5.93791e-05 | 3(Loss) | true |
