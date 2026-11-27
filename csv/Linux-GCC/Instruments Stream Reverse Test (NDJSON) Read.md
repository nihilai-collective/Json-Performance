
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 999.309 | 1.26599 | 6296.83ms | 4197496 | 30 | 7.71548e+10 | 4.00581e+06 | 0.539516 | 5.05473 | 26.5731 | 5.3455 | 0.000865992 | 0.081751 | 0.0045747 | 1(Win) | true |
| simdjson (ondemand) | 808.27 | 0.690842 | 7669.42ms | 4197496 | 80 | 9.36515e+10 | 4.95261e+06 | 0.000876062 | 6.26723 | 30.2381 | 5.3241 | 0.0090409 | 0.0812039 | 0.00561431 | 2(Loss) | true |
