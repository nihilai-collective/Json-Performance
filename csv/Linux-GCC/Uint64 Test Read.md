
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2599.08 | 0.0685537 | 750.499ms | 1213 | 1280 | 119.167 | 445.084 | 0.0296556 | 2.16558 | 10.1698 | 2.53339 | 0.000824402 | 0.000122372 | 4.05761e-05 | 1(Win) | true |
| simdjson (stage-1) | 1156.07 | 0.327554 | 805.59ms | 1213 | 320 | 3437.74 | 1000.64 | 0.341884 | 4.63166 | 26.6447 | 5.99341 | 0.000845012 | 0.000141694 | 5.41014e-05 | 2(Loss) | true |
