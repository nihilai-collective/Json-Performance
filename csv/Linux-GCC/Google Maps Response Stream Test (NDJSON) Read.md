
----
### Google Maps Response Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1395.04 | 0.12148 | 9745.85ms | 4203059 | 160 | 1.94934e+09 | 2.8733e+06 | 1.58757 | 3.62668 | 16.6409 | 3.12536 | 0.0160329 | 0.0887071 | 0.00494235 | 1(Win) | true |
| simdjson (ondemand) | 1055.73 | 0.649438 | 6081.23ms | 4203059 | 80 | 4.86396e+10 | 3.79675e+06 | 0.0646832 | 4.83279 | 18.7597 | 3.51749 | 0.0223546 | 0.0867709 | 0.0134118 | 2(Loss) | true |
