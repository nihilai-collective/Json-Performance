
----
### Twitter Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 698.675 | 0.262691 | 9305.71ms | 264040 | 320 | 2.86834e+08 | 360408 | 0.0760645 | 7.2677 | 27.0426 | 5.08452 | 0.0272219 | 0.00147323 | 0.000112317 | 1(Win) | true |
| simdjson (ondemand) | 279.235 | 0.108097 | 5718.63ms | 264040 | 320 | 3.04071e+08 | 901779 | 0.02279 | 18.0378 | 72.6752 | 12.7188 | 0.0868583 | 0.000759887 | 0.000123975 | 2(Loss) | true |
