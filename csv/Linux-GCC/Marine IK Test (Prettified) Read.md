
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2171.48 | 0.19298 | 10046.1ms | 7351818 | 40 | 1.55297e+09 | 3.22878e+06 | 0.188759 | 2.33023 | 9.7344 | 1.61637 | 0.0110037 | 0.0584184 | 0.00177573 | 1(Win) | true |
| Jsonifier (generic) | 2138.92 | 0.277694 | 10227.7ms | 7351818 | 30 | 2.48573e+09 | 3.27793e+06 | 0.284551 | 2.38609 | 9.45964 | 1.83011 | 0.0105024 | 0.0585747 | 0.000614991 | 2(Loss) | true |
