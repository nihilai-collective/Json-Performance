
----
### Twitter Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 755.449 | 0.278448 | 8356.25ms | 4219120 | 40 | 8.79795e+09 | 5.32619e+06 | 0.200376 | 6.71932 | 25.6531 | 4.71924 | 0.0230705 | 0.0545298 | 0.00354073 | 1(Win) | true |
| simdjson (ondemand) | 291.1 | 0.210586 | 9846.86ms | 4219120 | 40 | 3.38904e+10 | 1.38223e+07 | 0.171813 | 17.3774 | 70.1315 | 12.1605 | 0.0796225 | 0.0551001 | 0.0162161 | 2(Loss) | true |
