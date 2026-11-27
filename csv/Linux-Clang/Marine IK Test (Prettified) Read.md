
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2384.58 | 0.042612 | 9189.09ms | 7351818 | 160 | 2.51159e+08 | 2.94024e+06 | 0.147378 | 1.03824 | 1(Win) | true |
| simdjson (ondemand) | 2330 | 0.0586405 | 5118.15ms | 7351818 | 80 | 2.49093e+08 | 3.00911e+06 | 0.12522 | 1.06256 | 2(Loss) | true |
