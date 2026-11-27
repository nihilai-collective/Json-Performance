
----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1603.15 | 0.929966 | 8187.34ms | 4197495 | 80 | 4.31374e+10 | 2.49698e+06 | 0.858708 | 3.16102 | 15.9897 | 3.22267 | 0.000590114 | 0.083982 | 0.0034049 | 1(Win) | true |
| simdjson (ondemand) | 982.558 | 0.947636 | 6306.67ms | 4197495 | 80 | 1.19244e+11 | 4.0741e+06 | 0.172757 | 5.16295 | 22.1783 | 4.43516 | 0.0063186 | 0.1016 | 0.00452015 | 2(Loss) | true |
