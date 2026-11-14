
----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 762.329 | 0.0709215 | 8234.19ms | 4203058 | 80 | 1.11248e+09 | 5.25803e+06 | 0.418695 | 6.67796 | 29.7818 | 6.13265 | 0.0239213 | 0.0886704 | 0.00372994 | 1(Win) | true |
| simdjson (ondemand) | 610.562 | 0.0853484 | 10192.4ms | 4203058 | 80 | 2.51161e+09 | 6.56502e+06 | 0.123697 | 8.29982 | 32.123 | 6.74674 | 0.0351092 | 0.102961 | 0.0197394 | 2(Loss) | true |
