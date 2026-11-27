
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1412.35 | 0.0360926 | 4556.93ms | 56369 | 1280 | 241571 | 38062.7 | 0.0290062 | 3.60195 | 15.518 | 2.9646 | 0.00648739 | 1.59524e-05 | 7.95539e-06 | 1(Win) | true |
| simdjson (ondemand) | 1246.19 | 0.0953337 | 5053.57ms | 56369 | 4890 | 8.27016e+06 | 43137.6 | 0.0128946 | 4.0847 | 16.9534 | 2.83978 | 0.00896121 | 6.02116e-05 | 3.98521e-05 | 2(Loss) | true |
