
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1204.91 | 0.156386 | 5370.55ms | 4203058 | 30 | 8.11973e+08 | 3.32668e+06 | 0.530995 | 4.22069 | 19.5471 | 3.77044 | 0.0155551 | 0.0880988 | 0.00793116 | 1(Win) | true |
| simdjson (ondemand) | 816.738 | 0.10362 | 7704.88ms | 4203058 | 80 | 2.06891e+09 | 4.90775e+06 | 0.521209 | 6.22211 | 24.4107 | 5.1822 | 0.0226459 | 0.104197 | 0.00485306 | 2(Loss) | true |
