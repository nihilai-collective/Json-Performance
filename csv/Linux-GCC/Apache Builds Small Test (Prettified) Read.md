
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2413.32 | 0.0880115 | 870.321ms | 3370 | 1280 | 1758.41 | 1331.73 | 0.243216 | 2.16615 | 8.40386 | 1.50178 | 0.000602513 | 0.000113594 | 5.07697e-05 | 1(Win) | true |
| simdjson (ondemand) | 1994.97 | 0.0599584 | 914.431ms | 3370 | 1280 | 1194.26 | 1611 | 0.132372 | 2.62465 | 9.36855 | 1.6822 | 0.00119019 | 2.36461e-05 | 1.8546e-06 | 2(Loss) | true |
