
----
### Apache Builds Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1146.17 | 0.0332368 | 8642.16ms | 94653 | 1280 | 877037 | 78756.2 | 0.0430297 | 4.44072 | 20.561 | 4.20183 | 0.00989881 | 1.47331e-05 | 9.95412e-06 | 1(Win) | true |
| simdjson (ondemand) | 705.376 | 0.0282995 | 6913.86ms | 94653 | 2560 | 3.35757e+06 | 127972 | 0.00246276 | 7.19397 | 35.1358 | 7.03518 | 0.0120334 | 3.51489e-05 | 2.85087e-05 | 2(Loss) | true |
