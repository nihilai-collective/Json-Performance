
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 524.575 | 0.0902607 | 880.882ms | 905 | 1280 | 2822.86 | 1645.29 | 0.484778 | 10.1357 | 55.4608 | 5.50387 | 0.0011136 | 0.000115677 | 1.89917e-05 | 1(Win) | true |
| simdjson (ondemand) | 228.398 | 0.0294175 | 1091.1ms | 905 | 4890 | 6042.71 | 3778.81 | 0.0573344 | 22.7554 | 104.421 | 9.82431 | 0.0802725 | 0.00012993 | 7.9088e-06 | 2(Loss) | true |
