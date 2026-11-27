
----
### Random Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 864.994 | 0.0466312 | 1266.34ms | 4926 | 2560 | 16419.4 | 5431.02 | 0.106522 | 5.99602 | 26.5826 | 5.27548 | 0.00962154 | 0.00012775 | 7.08137e-05 | 1(Win) | true |
| simdjson (ondemand) | 464.937 | 0.0263926 | 1737.05ms | 4926 | 4890 | 34775.5 | 10104.2 | 0.0290615 | 11.073 | 45.4415 | 9.07329 | 0.0272874 | 0.000221271 | 0.000133012 | 2(Loss) | true |
