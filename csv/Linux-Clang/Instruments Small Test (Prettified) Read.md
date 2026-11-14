
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2269.26 | 0.0426793 | 1068.06ms | 7932 | 4890 | 9897.84 | 3333.48 | 0.10207 | 2.24887 | 10.1771 | 1.47819 | 0.000699917 | 6.42218e-05 | 3.69707e-05 | 1(Win) | true |
| Jsonifier (generic) | 2210.46 | 0.126138 | 1078.92ms | 7932 | 320 | 5962.71 | 3422.15 | 0.229135 | 2.33298 | 9.49143 | 1.81026 | 0.00162632 | 3.58516e-05 | 1.33951e-05 | 2(Loss) | true |
