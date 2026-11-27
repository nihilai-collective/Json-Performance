
----
### Random Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 889.651 | 0.101018 | 8102.88ms | 4506447 | 80 | 1.90509e+09 | 4.83075e+06 | 0.173588 | 5.70386 | 26.3563 | 5.35491 | 0.015381 | 0.0809563 | 0.00582249 | 1(Win) | true |
| simdjson (ondemand) | 517.335 | 0.141541 | 6217.29ms | 4506447 | 30 | 4.14774e+09 | 8.30735e+06 | 0.705733 | 9.8497 | 43.5972 | 7.74267 | 0.0323564 | 0.0790361 | 0.0101628 | 2(Loss) | true |
