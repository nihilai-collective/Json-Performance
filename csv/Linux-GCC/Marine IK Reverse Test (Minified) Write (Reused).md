
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1299.78 | 0.0344596 | 8553.19ms | 1834197 | 160 | 3.44105e+07 | 1.34578e+06 | 0.126695 | 3.88442 | 13.1332 | 0.799039 | 0.00224277 | 0.0604543 | 0.000172034 | 1(Win) | true |
| Glaze | 979.877 | 0.129353 | 5558.43ms | 1833577 | 160 | 8.52568e+08 | 1.78455e+06 | 0.00793437 | 5.15452 | 16.048 | 1.05269 | 0.000995622 | 0.049528 | 0.000169297 | 2(Loss) | true |
| simdjson (reflection) | 883.619 | 0.0143839 | 6466.21ms | 1922245 | 40 | 3.56207e+06 | 2.07464e+06 | 0.0157811 | 5.71355 | 18.1521 | 2.01847 | 0.0263143 | 0.0501029 | 0.000231279 | 3(Loss) | true |
