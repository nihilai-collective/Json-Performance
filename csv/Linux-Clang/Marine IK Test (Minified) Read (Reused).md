
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 962.356 | 0.172841 | 6401.93ms | 1834197 | 30 | 2.96097e+08 | 1.81765e+06 | 0.191126 | 5.23221 | 23.5421 | 5.10383 | 0.030377 | 0.0565749 | 0.000332825 | 1(Win) | true |
| Jsonifier (two-stage) | 813.15 | 0.0731641 | 7450.22ms | 1834197 | 160 | 3.96339e+08 | 2.15117e+06 | 0.061151 | 6.17654 | 28.1861 | 5.81846 | 0.0329617 | 0.119431 | 0.000237205 | 2(Loss) | true |
| Glaze | 734.908 | 0.0967455 | 8141.14ms | 1834197 | 80 | 4.24206e+08 | 2.3802e+06 | 0.0677051 | 6.86694 | 28.993 | 5.79232 | 0.0349009 | 0.0593351 | 0.000324379 | 3(Loss) | true |
| simdjson (ondemand) | 638.884 | 0.0717391 | 9246.51ms | 1834197 | 160 | 6.17277e+08 | 2.73794e+06 | 0.131385 | 7.86001 | 34.223 | 5.59902 | 0.041349 | 0.119145 | 0.00231829 | 4(Loss) | true |
