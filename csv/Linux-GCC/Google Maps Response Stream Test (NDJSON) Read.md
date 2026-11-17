
----
### Google Maps Response Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1345.83 | 0.0998922 | 9854.26ms | 4203059 | 160 | 1.41624e+09 | 2.97836e+06 | 0.0973129 | 3.77928 | 17.4233 | 3.23825 | 0.0141748 | 0.0887702 | 0.00227005 | 1(Win) | true |
| simdjson (ondemand) | 1031.11 | 0.146727 | 6167.71ms | 4203059 | 30 | 9.76038e+08 | 3.88743e+06 | 0.073447 | 4.94053 | 19.3013 | 3.6176 | 0.021442 | 0.088865 | 0.0025707 | 2(Loss) | true |
