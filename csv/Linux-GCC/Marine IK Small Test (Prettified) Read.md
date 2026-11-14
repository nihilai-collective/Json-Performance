
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2048.9 | 0.193434 | 1612.02ms | 18245 | 30 | 8095.31 | 8492.27 | 0.424461 | 2.57328 | 10.7955 | 1.92754 | 0.00245364 | 6.02905e-05 | 3.47127e-05 | 1(Win) | true |
| Jsonifier (generic) | 1926.76 | 0.0503622 | 1631.11ms | 18245 | 1280 | 26476.1 | 9030.61 | 0.149838 | 2.68419 | 10.4333 | 2.02508 | 0.00266165 | 2.21807e-05 | 1.05765e-05 | 2(Loss) | true |
