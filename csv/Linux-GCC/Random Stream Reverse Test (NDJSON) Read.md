
----
### Random Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 925.92 | 0.0926076 | 7733.21ms | 4506447 | 40 | 7.39051e+08 | 4.64153e+06 | 0.0118711 | 5.47292 | 25.8845 | 5.15829 | 0.0181677 | 0.0809867 | 0.00575555 | 1(Win) | true |
| simdjson (ondemand) | 521.025 | 0.0730612 | 6163.07ms | 4506447 | 40 | 1.45273e+09 | 8.24852e+06 | 0.304216 | 9.72552 | 40.0712 | 7.89224 | 0.0332616 | 0.0786556 | 0.00770322 | 2(Loss) | true |
