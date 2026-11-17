
----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 720.792 | 0.202215 | 8867.79ms | 4219120 | 40 | 5.09693e+09 | 5.58228e+06 | 0.760127 | 7.06098 | 27.3297 | 5.16365 | 0.0203271 | 0.0579654 | 0.00187758 | 1(Win) | true |
| simdjson (ondemand) | 324.08 | 0.155005 | 8938.91ms | 4219120 | 40 | 1.48146e+10 | 1.24156e+07 | 0.218588 | 15.502 | 61.9484 | 12.5404 | 0.0866111 | 0.0550606 | 0.00587823 | 2(Loss) | true |
