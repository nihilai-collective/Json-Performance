
----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21156.8 | 0.0666395 | 4016ms | 716365 | 1280 | 592710 | 32291.2 | 0.0153607 | 0.236982 | 0.715198 | 0.0981804 | 0.000180647 | 0.00427973 | 5.80513e-06 | 1(Win) | true |
| Glaze | 6567.32 | 0.114124 | 5702.55ms | 716365 | 2560 | 3.60819e+07 | 104027 | 0.012068 | 0.764511 | 2.69622 | 0.435824 | 0.000337555 | 0.00421174 | 1.67834e-05 | 2(Loss) | true |
| simdjson (reflection) | 524.163 | 0.230558 | 8319.45ms | 716365 | 320 | 2.88966e+09 | 1.30337e+06 | 0.324702 | 9.5789 | 30.5777 | 6.83138 | 0.0693665 | 0.290283 | 0.000449588 | 3(Loss) | true |
