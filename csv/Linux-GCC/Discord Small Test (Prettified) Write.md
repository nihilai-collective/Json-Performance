
----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14880.3 | 0.146905 | 771.375ms | 7376 | 80 | 38.5816 | 472.725 | 0.0264494 | 0.376144 | 1.15415 | 0.180721 | 0.000135575 | 2.37256e-05 | 8.47343e-06 | 1(Win) | true |
| Glaze | 3434.76 | 0.575318 | 933.311ms | 7376 | 160 | 22211.8 | 2047.97 | 0.0542925 | 1.52608 | 4.12107 | 0.686145 | 0.000148285 | 2.9657e-05 | 1.69469e-06 | 2(Loss) | true |
| simdjson (reflection) | 523.688 | 0.0653576 | 2083.87ms | 7376 | 4890 | 376875 | 13432.2 | 0.251498 | 9.77704 | 39.4154 | 8.02847 | 0.0127122 | 0.000155149 | 9.32389e-05 | 3(Loss) | true |
