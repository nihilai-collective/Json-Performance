
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1031.04 | 0.248805 | 7841.4ms | 2251027 | 40 | 1.07346e+09 | 2.08211e+06 | 0.562129 | 2.40122 | 1(Win) | true |
| Jsonifier (two-stage) | 911.043 | 0.0902768 | 8811.7ms | 2251027 | 30 | 1.35755e+08 | 2.35636e+06 | 0.353689 | 2.71749 | 2(Loss) | true |
| simdjson (ondemand) | 908.694 | 0.0504105 | 8785.87ms | 2251027 | 160 | 2.26928e+08 | 2.36245e+06 | 0.660629 | 2.72454 | 3(Loss) | true |
| Glaze | 883.984 | 0.229225 | 9027.12ms | 2251027 | 40 | 1.23952e+09 | 2.42849e+06 | 1.07534 | 2.8007 | 4(Loss) | true |
