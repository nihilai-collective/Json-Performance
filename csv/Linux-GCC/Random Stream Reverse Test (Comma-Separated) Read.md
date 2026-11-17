
----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 865.089 | 0.348183 | 8256.42ms | 4506446 | 80 | 2.39361e+10 | 4.96791e+06 | 0.0532283 | 5.89142 | 26.3603 | 5.39438 | 0.0109463 | 0.081368 | 0.00647726 | 1(Win) | true |
| simdjson (ondemand) | 494.425 | 0.178939 | 6443.82ms | 4506446 | 40 | 9.6769e+09 | 8.69228e+06 | 0.23855 | 10.2953 | 44.192 | 9.18949 | 0.0279526 | 0.088907 | 0.0122648 | 2(Loss) | true |
