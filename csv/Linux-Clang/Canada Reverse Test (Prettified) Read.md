
----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1634.74 | 0.280568 | 9386.23ms | 5212421 | 30 | 2.18364e+09 | 3.04083e+06 | 0.466518 | 3.10865 | 14.8594 | 2.85724 | 0.0103426 | 0.101231 | 0.00394228 | 1(Win) | true |
| simdjson (ondemand) | 1562.54 | 0.117281 | 9962.27ms | 5212421 | 160 | 2.22738e+09 | 3.18133e+06 | 0.179525 | 3.24248 | 15.1996 | 2.68602 | 0.0102663 | 0.120311 | 0.00193636 | 2(Loss) | true |
