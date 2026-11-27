
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1537.57 | 0.0264603 | 7460.27ms | 108313 | 2560 | 808951 | 67181.1 | 0.0279588 | 3.29352 | 14.7548 | 2.81716 | 0.00406717 | 2.89417e-05 | 1.87499e-05 | 1(Win) | true |
| simdjson (ondemand) | 1437.8 | 0.102551 | 7942.45ms | 108313 | 320 | 1.73698e+06 | 71842.7 | 0.204971 | 3.53429 | 16.4494 | 2.45138 | 0.00647894 | 2.89381e-05 | 1.97633e-05 | 2(Loss) | true |
