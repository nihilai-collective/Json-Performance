
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15480.6 | 0.068916 | 5217.44ms | 728486 | 160 | 153048 | 44878 | 0.0823743 | 0.331625 | 1.87508 | 0.114693 | 0.000125732 | 5.38789e-06 | 3.98944e-06 | 1(Win) | true |
| simdjson (stage-1) | 13819.3 | 0.0276699 | 5756.95ms | 728486 | 2560 | 495364 | 50272.9 | 0.216182 | 0.370366 | 1.7744 | 0.0748855 | 1.27839e-05 | 4.02536e-06 | 2.72665e-06 | 2(Loss) | true |
