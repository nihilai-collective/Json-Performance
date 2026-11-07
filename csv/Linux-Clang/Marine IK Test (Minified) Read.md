
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 859.62 | 0.489052 | 6242.3ms | 1834197 | 30 | 2.97105e+09 | 2.03488e+06 | 1.35035 | 2.88004 | 1(Win) | true |
| Jsonifier (two-stage) | 805.797 | 0.0643387 | 6795.25ms | 1834197 | 80 | 1.56055e+08 | 2.1708e+06 | 0.537635 | 3.07243 | 2(Loss) | true |
| Glaze | 688.644 | 0.0595634 | 8018ms | 1834197 | 40 | 9.15634e+07 | 2.5401e+06 | 0.345769 | 3.59508 | 3(Loss) | true |
| simdjson (ondemand) | 612.798 | 0.0949619 | 8861.38ms | 1834197 | 40 | 2.93911e+08 | 2.85449e+06 | 0.030721 | 4.03992 | 4(Loss) | true |
