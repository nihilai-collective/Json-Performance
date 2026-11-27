
----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2038.13 | 0.0741322 | 1585.54ms | 18245 | 320 | 12817 | 8537.13 | 0.179808 | 2.53801 | 10.2015 | 2.01551 | 0.0030224 | 7.70759e-06 | 8.56399e-07 | 1(Win) | true |
| simdjson (ondemand) | 2007.61 | 0.0601564 | 1595.03ms | 18245 | 2560 | 69587.5 | 8666.9 | 0.0508457 | 2.57444 | 10.6994 | 1.91068 | 0.00277495 | 4.68664e-05 | 3.53265e-05 | 2(Loss) | true |
