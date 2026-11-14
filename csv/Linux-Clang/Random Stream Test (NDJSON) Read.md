
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1468.93 | 0.109724 | 5119.85ms | 4506447 | 40 | 4.12219e+08 | 2.92573e+06 | 0.0138582 | 3.45867 | 15.8899 | 3.00045 | 0.00842295 | 0.0812673 | 0.00141024 | 1(Win) | true |
| simdjson (ondemand) | 1141.88 | 0.0760923 | 6381.57ms | 4506447 | 80 | 6.56139e+08 | 3.76368e+06 | 0.0177952 | 4.44767 | 18.2754 | 3.12968 | 0.014082 | 0.0790395 | 0.00132092 | 2(Loss) | true |
