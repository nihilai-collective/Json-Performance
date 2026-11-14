
----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 981.889 | 0.085257 | 5948.93ms | 53331 | 320 | 624087 | 51798.6 | 0.0457812 | 5.22394 | 19.492 | 3.91626 | 0.0159465 | 7.19563e-05 | 4.73458e-05 | 1(Win) | true |
| simdjson (ondemand) | 444.895 | 0.102143 | 6239.59ms | 53331 | 640 | 8.72656e+06 | 114320 | 0.0356424 | 11.5457 | 40.8025 | 7.36421 | 0.064802 | 8.2152e-05 | 4.35957e-05 | 2(Loss) | true |
