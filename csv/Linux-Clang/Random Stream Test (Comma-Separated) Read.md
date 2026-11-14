
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1315.87 | 0.131448 | 5643.12ms | 4506446 | 40 | 7.37247e+08 | 3.26605e+06 | 0.130945 | 3.87153 | 17.5592 | 3.41545 | 0.0111467 | 0.0816765 | 0.003959 | 1(Win) | true |
| simdjson (ondemand) | 932.299 | 0.16982 | 7631.21ms | 4506446 | 40 | 2.4513e+09 | 4.60977e+06 | 0.225324 | 5.46727 | 21.9317 | 3.84809 | 0.0142171 | 0.0864623 | 0.00385869 | 2(Loss) | true |
