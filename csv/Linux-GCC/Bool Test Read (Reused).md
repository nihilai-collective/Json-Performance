
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 524.708 | 0.080926 | 874.377ms | 905 | 2560 | 4536.05 | 1644.87 | 0.0216061 | 10.052 | 54.8055 | 5.27735 | 0.00202391 | 0.000131215 | 1.9855e-05 | 1(Win) | true |
| simdjson (ondemand) | 227.095 | 0.0495405 | 1092.6ms | 905 | 1280 | 4537.45 | 3800.5 | 0.0518167 | 22.9383 | 103.737 | 9.68509 | 0.0889451 | 0.000162293 | 6.12914e-05 | 2(Loss) | true |
