
----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16558.8 | 0.0439599 | 1522.31ms | 136037 | 4890 | 58007.1 | 7834.82 | 0.139545 | 0.308036 | 1.29399 | 0.215125 | 0.00021991 | 3.23051e-06 | 8.92936e-07 | 1(Win) | true |
| Glaze | 5363.64 | 0.0707311 | 3164.91ms | 136076 | 2560 | 749731 | 24194.8 | 0.176973 | 0.93892 | 4.09524 | 0.690408 | 0.00145646 | 4.67053e-06 | 1.84869e-06 | 2(Loss) | true |
