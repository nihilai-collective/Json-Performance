
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1000.4 | 0.0671166 | 844.074ms | 1313 | 2560 | 1806.68 | 1251.67 | 0.20781 | 5.30809 | 27.7113 | 5.50647 | 0.00214293 | 0.000117515 | 1.16027e-05 | 1(Win) | true |
| simdjson (ondemand) | 415.588 | 0.0240812 | 1022.34ms | 1313 | 160 | 84.2324 | 3013.02 | 0.00726069 | 12.5634 | 53.754 | 10.6101 | 0.00152323 | 3.33206e-05 | 4.76009e-06 | 2(Loss) | true |
