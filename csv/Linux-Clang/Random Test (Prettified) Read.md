
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1798.88 | 0.105322 | 9378.95ms | 676745 | 320 | 4.56912e+07 | 358776 | 0.0748696 | 2.82324 | 11.8396 | 2.18809 | 0.00976021 | 0.0245839 | 8.08696e-05 | 1(Win) | true |
| simdjson (ondemand) | 1489.95 | 0.0905 | 5614.28ms | 676745 | 640 | 9.83523e+07 | 433165 | 0.0693833 | 3.41784 | 13.2473 | 2.2971 | 0.0130212 | 0.0345998 | 6.11382e-05 | 2(Loss) | true |
