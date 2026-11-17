
----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1822.29 | 0.0204773 | 8488.76ms | 124597 | 2560 | 456422 | 65206.6 | 0.0187972 | 2.78345 | 13.3353 | 2.59718 | 0.00586794 | 1.6939e-05 | 9.96964e-06 | 1(Win) | true |
| simdjson (ondemand) | 1072.6 | 0.220746 | 6700.6ms | 124597 | 30 | 1.7941e+06 | 110782 | 0.231599 | 4.77134 | 23.1441 | 4.67254 | 0.00769441 | 6.4207e-06 | 2.67529e-06 | 2(Loss) | true |
