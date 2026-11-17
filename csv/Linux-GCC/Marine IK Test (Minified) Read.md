
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 839.829 | 0.0618372 | 6443.87ms | 1834197 | 160 | 2.65418e+08 | 2.08284e+06 | 0.2349 | 2.94797 | 1(Win) | true |
| Jsonifier (two-stage) | 740.725 | 0.12464 | 7347.74ms | 1834197 | 80 | 6.93084e+08 | 2.36151e+06 | 0.155465 | 3.3424 | 2(Loss) | true |
| Glaze | 651.952 | 0.105104 | 8355.25ms | 1834197 | 30 | 2.38573e+08 | 2.68306e+06 | 1.203 | 3.79753 | 3(Loss) | true |
| simdjson (reflection) | 615.008 | 0.0629491 | 8895.27ms | 1834197 | 160 | 5.12896e+08 | 2.84423e+06 | 0.673821 | 4.02564 | 4(Loss) | true |
| simdjson (ondemand) | 553.055 | 0.113764 | 10018.5ms | 1834197 | 30 | 3.88406e+08 | 3.16284e+06 | 0.120516 | 4.47656 | 5(Loss) | true |
