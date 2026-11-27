
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2118.91 | 0.195272 | 8001.16ms | 676745 | 40 | 1.41503e+07 | 304588 | 0.0814904 | 2.39744 | 11.0145 | 2.06235 | 0.00645871 | 0.0323424 | 6.40936e-05 | 1(Win) | true |
| simdjson (ondemand) | 1613.14 | 0.114705 | 5222.5ms | 676745 | 80 | 1.68485e+07 | 400086 | 0.221457 | 3.15935 | 12.6299 | 2.30868 | 0.0107617 | 0.0353691 | 2.6875e-05 | 2(Loss) | true |
