
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6646.81 | 0.16293 | 1082.49ms | 24579 | 640 | 21129.2 | 3526.56 | 0.14993 | 0.784653 | 1.86501 | 0.100655 | 7.32968e-05 | 1.91347e-05 | 1.0362e-05 | 1(Win) | true |
| Glaze | 3566.16 | 0.117662 | 1384.18ms | 24579 | 2560 | 153124 | 6572.99 | 0.321891 | 1.44526 | 3.76179 | 0.442166 | 0.000330392 | 4.44676e-05 | 2.87816e-05 | 2(Loss) | true |
| simdjson (reflection) | 534.169 | 0.181255 | 5179.44ms | 24893 | 1280 | 8.30587e+06 | 44442.5 | 0.146691 | 9.5775 | 36.8094 | 6.04411 | 0.00780324 | 9.20188e-05 | 5.73078e-05 | 3(Loss) | true |
