
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 696.058 | 0.135328 | 8572.74ms | 1834197 | 40 | 4.62632e+08 | 2.51305e+06 | 0.00910995 | 7.3789 | 30.7033 | 6.42527 | 0.0366104 | 0.11816 | 1.45977e-05 | 1(Win) | true |
| simdjson (ondemand) | 650.494 | 0.0798838 | 9079.45ms | 1834197 | 160 | 7.38317e+08 | 2.68907e+06 | 0.0578412 | 7.79621 | 31.9435 | 5.62697 | 0.0432128 | 0.118933 | 0.00540898 | 2(Loss) | true |
