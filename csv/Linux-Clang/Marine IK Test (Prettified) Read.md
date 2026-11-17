
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2445.2 | 0.231878 | 8737.16ms | 7351818 | 80 | 3.53646e+09 | 2.86734e+06 | 0.360433 | 1.01237 | 1(Win) | true |
| Jsonifier | 2405.87 | 0.228012 | 8995.56ms | 7351818 | 30 | 1.32458e+09 | 2.91422e+06 | 0.876866 | 1.02903 | 2(Loss) | true |
| simdjson (ondemand) | 2082.36 | 0.134474 | 5196.62ms | 7351818 | 80 | 1.64001e+09 | 3.36697e+06 | 2.43338 | 1.18889 | 3(Loss) | true |
| Glaze | 1961.01 | 0.356819 | 5343.76ms | 7351818 | 40 | 6.51011e+09 | 3.57533e+06 | 0.225263 | 1.26247 | 4(Loss) | true |
