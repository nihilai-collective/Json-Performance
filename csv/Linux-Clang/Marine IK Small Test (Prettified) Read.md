
----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2094.47 | 0.0613675 | 1566.44ms | 18245 | 4890 | 127094 | 8307.49 | 0.157357 | 2.44526 | 9.94629 | 1.95155 | 0.0026496 | 0.000100406 | 5.88558e-05 | 1(Win) | true |
| simdjson (ondemand) | 1993.01 | 0.0337867 | 1607.51ms | 18245 | 2560 | 22274.1 | 8730.41 | 0.0958598 | 2.57974 | 10.6427 | 1.79973 | 0.00311235 | 2.31014e-05 | 1.03838e-05 | 2(Loss) | true |
