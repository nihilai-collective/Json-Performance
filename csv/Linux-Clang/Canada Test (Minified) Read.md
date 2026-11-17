
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 790.743 | 0.0813605 | 7889.95ms | 2090234 | 160 | 6.7308e+08 | 2.52092e+06 | 0.903193 | 6.40874 | 32.6323 | 6.38394 | 0.0230273 | 0.10413 | 0.000596094 | 1(Win) | true |
| simdjson (ondemand) | 760.007 | 0.228242 | 8225.31ms | 2090234 | 160 | 5.73411e+09 | 2.62288e+06 | 0.794331 | 6.70619 | 31.7593 | 5.65027 | 0.0232213 | 0.105009 | 0.000769274 | 2(Loss) | true |
