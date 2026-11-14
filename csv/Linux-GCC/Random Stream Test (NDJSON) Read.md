
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1635.24 | 0.209903 | 9723.4ms | 4506447 | 40 | 1.21731e+09 | 2.62817e+06 | 0.100064 | 3.10763 | 15.2691 | 2.85081 | 0.00874005 | 0.0809546 | 0.000978631 | 1(Win) | true |
| simdjson (ondemand) | 1167.95 | 0.138777 | 6293.93ms | 4506447 | 80 | 2.08613e+09 | 3.67967e+06 | 0.36136 | 4.37349 | 17.1557 | 3.15455 | 0.0134883 | 0.0789807 | 0.00349918 | 2(Loss) | true |
