
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 836.095 | 0.130246 | 6592.97ms | 1834197 | 30 | 2.22758e+08 | 2.09214e+06 | 0.0929173 | 6.01973 | 25.516 | 5.77962 | 0.0362322 | 0.0828848 | 0.00255043 | 1(Win) | true |
| Jsonifier (two-stage) | 714.801 | 0.123423 | 7662.9ms | 1834197 | 80 | 7.29799e+08 | 2.44715e+06 | 0.377241 | 7.00849 | 29.8089 | 6.18428 | 0.0418663 | 0.146038 | 0.00973365 | 2(Loss) | true |
| Glaze | 653.993 | 0.0862115 | 8334.24ms | 1834197 | 160 | 8.50739e+08 | 2.67469e+06 | 0.236918 | 7.6498 | 32.3736 | 6.3238 | 0.0346072 | 0.0835471 | 0.0036918 | 3(Loss) | true |
| simdjson (reflection) | 619.767 | 0.0612195 | 8783.71ms | 1834197 | 160 | 4.77678e+08 | 2.82239e+06 | 0.162774 | 8.1402 | 34.8334 | 6.48967 | 0.0369364 | 0.135894 | 0.00755803 | 4(Loss) | true |
| simdjson (ondemand) | 530.928 | 0.133278 | 10315.9ms | 1834197 | 80 | 1.5425e+09 | 3.29466e+06 | 0.0642726 | 9.43941 | 38.0357 | 7.35418 | 0.0417746 | 0.148514 | 0.00973428 | 5(Loss) | true |
