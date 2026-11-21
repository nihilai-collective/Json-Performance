
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2967.63 | 0.0652658 | 129.71ms | 3873 | 40 | 26.3942 | 1244.62 | 0.0702529 | 0.81697 | 1(Win) | true |
| Jsonifier (two-stage) | 2946.03 | 0.0571528 | 130.137ms | 3873 | 80 | 41.0759 | 1253.75 | 0.0896504 | 0.823573 | 2(Loss) | true |
| Glaze | 1422.5 | 0.0417072 | 264.086ms | 3873 | 80 | 93.8214 | 2596.54 | 0.0168522 | 1.72347 | 3(Loss) | true |
| simdjson (ondemand) | 799.09 | 0.0326491 | 531.974ms | 3873 | 30 | 68.323 | 4622.23 | 0.122023 | 3.08282 | 4(Loss) | true |
