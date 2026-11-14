
----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10337.2 | 0.0372523 | 886.427ms | 18245 | 4890 | 1922.64 | 1683.22 | 0.00181192 | 0.509795 | 2.44434 | 0.258592 | 0.000110179 | 8.07012e-06 | 4.25923e-07 | 1(Win) | true |
| simdjson (ondemand) | 9924.8 | 0.0388894 | 889.288ms | 18245 | 4890 | 2273.08 | 1753.16 | 0.0047063 | 0.530805 | 2.7823 | 0.279474 | 0.000126073 | 9.98677e-06 | 3.32892e-06 | 2(Loss) | true |
