
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 856.042 | 0.0550408 | 6387.49ms | 1834197 | 160 | 2.02391e+08 | 2.04339e+06 | 0.230066 | 5.87342 | 26.5235 | 5.79902 | 0.0313253 | 0.0826507 | 0.000262448 | 1(Win) | true |
| Jsonifier (two-stage) | 734.011 | 0.110576 | 7425.17ms | 1834197 | 80 | 5.55517e+08 | 2.38311e+06 | 0.105931 | 6.82001 | 31.1661 | 6.51347 | 0.0339763 | 0.146052 | 0.00122468 | 2(Loss) | true |
| Glaze | 667.159 | 0.10022 | 8145.28ms | 1834197 | 80 | 5.52371e+08 | 2.6219e+06 | 0.244577 | 7.53254 | 31.9798 | 6.48941 | 0.0361718 | 0.0827063 | 0.000247479 | 3(Loss) | true |
| simdjson (ondemand) | 579.311 | 0.099957 | 9434.31ms | 1834197 | 80 | 7.28761e+08 | 3.0195e+06 | 0.0353702 | 8.65982 | 37.2161 | 6.29552 | 0.0463075 | 0.147463 | 0.000955507 | 4(Loss) | true |
