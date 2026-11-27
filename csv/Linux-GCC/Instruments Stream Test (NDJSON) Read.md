
----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1747.43 | 0.878021 | 7427.62ms | 4197496 | 160 | 6.4731e+10 | 2.29082e+06 | 0.278789 | 2.90148 | 13.9713 | 2.72555 | 0.000461613 | 0.0814967 | 0.00212511 | 1(Win) | true |
| simdjson (ondemand) | 1498.85 | 0.770977 | 8760.53ms | 4197496 | 160 | 6.78367e+10 | 2.67074e+06 | 0.690954 | 3.3741 | 16.4865 | 2.65769 | 0.00577512 | 0.0804483 | 0.00342488 | 2(Loss) | true |
