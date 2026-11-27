
----
### Random Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1830.75 | 0.0735503 | 5635.63ms | 409725 | 160 | 3.9429e+06 | 213434 | 0.0564544 | 2.76721 | 12.6223 | 2.39711 | 0.00960957 | 7.07792e-05 | 5.58301e-06 | 1(Win) | true |
| simdjson (ondemand) | 1457.43 | 0.126341 | 7018.86ms | 409725 | 80 | 9.17891e+06 | 268105 | 0.0571138 | 3.48497 | 15.3107 | 2.61244 | 0.01205 | 0.000713954 | 7.16029e-05 | 2(Loss) | true |
