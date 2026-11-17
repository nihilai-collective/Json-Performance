
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2332.5 | 0.759981 | 5099.73ms | 7351818 | 80 | 4.17486e+10 | 3.00589e+06 | 0.0242382 | 1.06143 | 1(Win) | true |
| Jsonifier | 2261.46 | 0.269385 | 5167.43ms | 7351818 | 80 | 5.5802e+09 | 3.10032e+06 | 0.755589 | 1.09477 | 2(Loss) | true |
| Glaze | 730.235 | 0.229759 | 7018.77ms | 7351818 | 40 | 1.94657e+10 | 9.60134e+06 | 0.100354 | 3.39043 | 3(Loss) | true |
| simdjson (ondemand) | 490.644 | 0.953984 | 10278.8ms | 7351818 | 40 | 7.43359e+11 | 1.42899e+07 | 0.368824 | 5.04604 | 4(Loss) | true |
