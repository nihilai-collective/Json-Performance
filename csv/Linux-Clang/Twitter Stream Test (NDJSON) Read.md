
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1982.7 | 0.384606 | 7011.17ms | 4219120 | 40 | 2.43681e+09 | 2.02939e+06 | 0.247398 | 2.55562 | 9.28939 | 1.64433 | 0.011529 | 0.0566562 | 0.000206074 | 1(Win) | true |
| simdjson (ondemand) | 1701.21 | 0.106256 | 8071.08ms | 4219120 | 80 | 5.05266e+08 | 2.36517e+06 | 0.268928 | 2.95002 | 9.95526 | 1.53735 | 0.0175347 | 0.0538274 | 0.000226137 | 2(Loss) | true |
