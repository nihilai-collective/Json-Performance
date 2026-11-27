
----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17641.8 | 0.270141 | 5322.99ms | 837491 | 1280 | 1.91454e+07 | 45272.8 | 0.071789 | 0.286704 | 0.897786 | 0.106635 | 8.72584e-05 | 0.014282 | 2.52895e-06 | 1(Win) | true |
| Glaze | 5746.35 | 0.20225 | 7554.06ms | 837491 | 1280 | 1.01149e+08 | 138991 | 0.0264414 | 0.875414 | 4.42726 | 0.728068 | 0.00588784 | 0.0199495 | 1.49936e-05 | 2(Loss) | true |
| simdjson (reflection) | 546.584 | 1.02484 | 9366.2ms | 837491 | 30 | 6.72794e+09 | 1.46125e+06 | 0.152692 | 9.17676 | 37.1838 | 7.10495 | 0.0259536 | 0.349575 | 0.000136996 | 3(Loss) | true |
