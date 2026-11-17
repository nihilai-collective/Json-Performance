
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 549.146 | 0.109754 | 1544.1ms | 4604 | 160 | 12321.2 | 7995.53 | 0.0025795 | 9.42125 | 37.1033 | 7.74707 | 0.00837451 | 4.88705e-05 | 1.22176e-05 | 1(Win) | true |
| simdjson (ondemand) | 536.561 | 0.102991 | 1542.32ms | 4604 | 320 | 22729.1 | 8183.07 | 0.0599538 | 9.47262 | 38.716 | 7.48892 | 0.0111561 | 3.59742e-05 | 1.15389e-05 | 2(Loss) | true |
