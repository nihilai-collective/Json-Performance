
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1080.28 | 0.163456 | 5900.48ms | 4203058 | 80 | 2.94274e+09 | 3.71048e+06 | 0.668353 | 4.70737 | 19.9816 | 3.95227 | 0.0167643 | 0.0891268 | 0.00521014 | 1(Win) | true |
| simdjson (ondemand) | 760.682 | 0.183008 | 8306.22ms | 4203058 | 30 | 2.78988e+09 | 5.26942e+06 | 0.0858352 | 6.67165 | 25.0667 | 4.46731 | 0.0288594 | 0.103106 | 0.00184777 | 2(Loss) | true |
