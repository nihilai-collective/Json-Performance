
----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14388.9 | 0.191609 | 794.967ms | 9249 | 4890 | 6746.47 | 613.011 | 0.240275 | 0.374956 | 1.22759 | 0.292897 | 0.000168105 | 1.21828e-05 | 2.58692e-06 | 1(Win) | true |
| Glaze | 2633.65 | 0.13224 | 1075.96ms | 9249 | 4890 | 95920.3 | 3349.17 | 0.209878 | 1.94397 | 3.88215 | 0.648827 | 0.000344436 | 2.79475e-05 | 9.90545e-06 | 2(Loss) | true |
