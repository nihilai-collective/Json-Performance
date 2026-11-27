
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14348.4 | 0.156687 | 8253.71ms | 2251027 | 40 | 2.19825e+06 | 149615 | 0.584109 | 0.356328 | 1.67877 | 0.110613 | 0.00217623 | 0.02482 | 5.44196e-07 | 1(Win) | true |
| simdjson (stage-1) | 11721.5 | 0.0664548 | 9957.53ms | 2251027 | 40 | 592525 | 183146 | 0.243202 | 0.439057 | 2.1019 | 0.0806473 | 0.00163475 | 0.0245034 | 1.92135e-06 | 2(Loss) | true |
