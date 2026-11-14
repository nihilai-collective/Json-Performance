
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1266.14 | 0.127664 | 9099.03ms | 461466 | 80 | 1.57521e+07 | 347582 | 0.0343598 | 3.99895 | 17.3631 | 3.29407 | 0.0186719 | 0.0364685 | 6.25723e-05 | 1(Win) | true |
| Glaze | 1183.12 | 0.0775379 | 9720.9ms | 461466 | 320 | 2.66197e+07 | 371974 | 0.0879926 | 4.27034 | 19.1676 | 3.7914 | 0.013674 | 0.0326973 | 8.53462e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1101.86 | 0.11546 | 5183.77ms | 461466 | 80 | 1.70132e+07 | 399406 | 0.0752458 | 4.58453 | 18.839 | 3.55535 | 0.0251145 | 0.0777181 | 8.15065e-05 | 3(Loss) | true |
| simdjson (ondemand) | 825.243 | 0.124063 | 6895.47ms | 461466 | 160 | 7.00356e+07 | 533283 | 0.0134643 | 6.10067 | 25.2998 | 4.47819 | 0.0108109 | 0.0812863 | 0.000126987 | 4(Loss) | true |
