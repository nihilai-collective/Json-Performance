
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2532.73 | 0.0248659 | 7642.8ms | 183677 | 2560 | 757145 | 69161.7 | 0.104382 | 1.99982 | 8.46946 | 1.61146 | 0.00208498 | 2.15392e-05 | 1.59821e-05 | 1(Win) | true |
| simdjson (ondemand) | 2420.66 | 0.0679167 | 7960.38ms | 183677 | 640 | 1.54587e+06 | 72363.7 | 0.431304 | 2.09073 | 9.51058 | 1.46884 | 0.00415629 | 9.57864e-06 | 6.12488e-06 | 2(Loss) | true |
