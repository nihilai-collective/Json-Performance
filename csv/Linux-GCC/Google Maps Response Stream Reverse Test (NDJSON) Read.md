
----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 819.731 | 0.115974 | 7745.74ms | 4203059 | 40 | 1.28637e+09 | 4.88983e+06 | 0.562527 | 6.24103 | 27.6901 | 5.59929 | 0.0221059 | 0.0885769 | 0.0185928 | 1(Win) | true |
| simdjson (ondemand) | 751.313 | 0.0587864 | 8420.62ms | 4203059 | 80 | 7.86925e+08 | 5.33512e+06 | 0.0950206 | 6.73677 | 27.1249 | 5.21161 | 0.0264916 | 0.0880991 | 0.0120072 | 2(Loss) | true |
