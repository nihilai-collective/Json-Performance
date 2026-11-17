
----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 746.141 | 0.302007 | 8455.44ms | 4219120 | 30 | 7.95716e+09 | 5.39263e+06 | 0.52273 | 6.75332 | 26.4403 | 4.97387 | 0.0167754 | 0.0576631 | 0.00113435 | 1(Win) | true |
| simdjson (ondemand) | 287.92 | 0.0861247 | 10007.2ms | 4219120 | 40 | 5.7945e+09 | 1.39749e+07 | 0.0603813 | 17.5269 | 70.159 | 12.1737 | 0.0850667 | 0.0540767 | 0.00847667 | 2(Loss) | true |
