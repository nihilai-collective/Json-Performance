
----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1291.27 | 0.890663 | 5812.03ms | 4506447 | 80 | 7.02996e+10 | 3.32827e+06 | 0.159007 | 3.92083 | 15.8377 | 2.89712 | 0.0168539 | 0.080454 | 0.0119945 | 1(Win) | true |
| simdjson (ondemand) | 1035.14 | 1.374 | 7111.71ms | 4506447 | 30 | 9.76251e+10 | 4.15178e+06 | 1.97623 | 4.9117 | 18.1956 | 3.10547 | 0.0167829 | 0.0790671 | 0.0113274 | 2(Loss) | true |
