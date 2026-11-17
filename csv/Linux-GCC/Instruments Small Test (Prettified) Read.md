
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3344.74 | 0.099793 | 960.085ms | 7932 | 80 | 407.503 | 2261.62 | 0.0475548 | 1.56795 | 6.40494 | 1.04564 | 0.000753278 | 2.52143e-05 | 3.15179e-06 | 1(Win) | true |
| Jsonifier | 2827.46 | 0.0623532 | 995.317ms | 7932 | 2560 | 7124.12 | 2675.39 | 0.0278074 | 1.81875 | 6.55724 | 1.45411 | 0.00101734 | 2.83169e-05 | 1.06373e-05 | 2(Loss) | true |
| simdjson (reflection) | 2660.4 | 0.144084 | 1022.49ms | 7932 | 320 | 5371 | 2843.39 | 0.0553123 | 1.95313 | 8.03429 | 1.19617 | 0.000615781 | 1.5365e-05 | 5.12166e-06 | 3(Loss) | true |
| Glaze | 2377.73 | 0.0471758 | 1045.71ms | 7932 | 4890 | 11015.1 | 3181.41 | 0.273678 | 2.17616 | 8.49458 | 1.65368 | 0.00182329 | 5.59975e-05 | 3.52949e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2112.46 | 0.0828978 | 1088.11ms | 7932 | 40 | 352.481 | 3580.93 | 0.118126 | 2.42157 | 9.38061 | 1.6001 | 0.00101803 | 1.26072e-05 | 0 | 5(Loss) | true |
