
----
### Google Maps Response Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1227.76 | 0.10798 | 5341.61ms | 4203059 | 80 | 9.94207e+08 | 3.26477e+06 | 1.19627 | 4.11913 | 17.8304 | 3.28646 | 0.0182796 | 0.0888779 | 0.00686289 | 1(Win) | true |
| simdjson (ondemand) | 954.555 | 0.706447 | 6709.3ms | 4203059 | 40 | 3.52005e+10 | 4.19918e+06 | 0.238249 | 5.27789 | 19.9861 | 3.46943 | 0.025161 | 0.0882546 | 0.010088 | 2(Loss) | true |
