
----
### Apache Builds Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1450.72 | 0.10102 | 8932.38ms | 124597 | 160 | 1.09543e+06 | 81907.8 | 0.00446366 | 3.50105 | 16.267 | 3.25986 | 0.0081257 | 9.93202e-06 | 6.97248e-06 | 1(Win) | true |
| simdjson (ondemand) | 919.765 | 0.0736702 | 6997.36ms | 124597 | 2560 | 2.31892e+07 | 129191 | 0.124101 | 5.53226 | 26.6686 | 5.30136 | 0.00991676 | 3.44172e-05 | 2.27483e-05 | 2(Loss) | true |
