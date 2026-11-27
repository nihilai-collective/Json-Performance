
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 828.295 | 0.0665067 | 6616.48ms | 1834197 | 160 | 3.15627e+08 | 2.11184e+06 | 0.132738 | 6.09466 | 25.7816 | 5.78192 | 0.0366542 | 0.0831344 | 0.00267141 | 1(Win) | true |
| Jsonifier (two-stage) | 710.518 | 0.129732 | 7650.65ms | 1834197 | 80 | 8.16069e+08 | 2.4619e+06 | 0.113785 | 7.09465 | 30.0091 | 6.27293 | 0.0462405 | 0.146752 | 0.00647867 | 2(Loss) | true |
| simdjson (reflection) | 670.03 | 0.0790667 | 8114.4ms | 1834197 | 40 | 1.70432e+08 | 2.61067e+06 | 0.272587 | 7.51874 | 32.2473 | 5.9494 | 0.0317071 | 0.135985 | 0.00182318 | 3(Loss) | true |
| Glaze | 653.583 | 0.229558 | 8327.5ms | 1834197 | 80 | 3.01972e+09 | 2.67636e+06 | 0.0904978 | 7.71774 | 32.3794 | 6.32443 | 0.0346494 | 0.0822488 | 0.00152312 | 4(Loss) | true |
| simdjson (ondemand) | 543.308 | 0.139634 | 9966.89ms | 1834197 | 40 | 8.08426e+08 | 3.21959e+06 | 0.318355 | 9.28942 | 37.5542 | 7.1635 | 0.0366757 | 0.148849 | 0.0117999 | 5(Loss) | true |
