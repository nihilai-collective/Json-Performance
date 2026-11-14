
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 921.19 | 0.103869 | 6569.73ms | 1834197 | 80 | 3.11212e+08 | 1.89888e+06 | 0.057756 | 5.44204 | 23.9458 | 5.05706 | 0.0293476 | 0.0553313 | 0.000241495 | 1(Win) | true |
| Jsonifier (two-stage) | 767.729 | 0.742163 | 7795.61ms | 1834197 | 160 | 4.57503e+10 | 2.27844e+06 | 0.131008 | 6.57323 | 28.0015 | 5.58184 | 0.0357543 | 0.119106 | 0.000301586 | 2(Loss) | true |
| Glaze | 734.449 | 0.179106 | 8109.82ms | 1834197 | 30 | 5.45896e+08 | 2.38169e+06 | 0.0416713 | 6.85869 | 28.9905 | 5.79182 | 0.0339813 | 0.0581276 | 0.000904538 | 3(Loss) | true |
| simdjson (ondemand) | 633.026 | 0.45432 | 9278.15ms | 1834197 | 30 | 4.72817e+09 | 2.76328e+06 | 0.323646 | 7.977 | 34.2442 | 5.59991 | 0.0412643 | 0.118391 | 0.00107393 | 4(Loss) | true |
