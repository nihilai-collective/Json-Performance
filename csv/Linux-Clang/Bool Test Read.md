
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 652.532 | 0.227954 | 856.724ms | 905 | 2560 | 23271.7 | 1322.66 | 0.0234255 | 8.15257 | 37.3039 | 6.70055 | 0.00457571 | 0.000197255 | 8.02831e-05 | 1(Win) | true |
| simdjson (ondemand) | 491.462 | 0.0987659 | 891.899ms | 905 | 160 | 481.339 | 1756.14 | 0.0085422 | 10.7244 | 50.5039 | 9.81436 | 0.0441851 | 0.000103591 | 1.38122e-05 | 2(Loss) | true |
