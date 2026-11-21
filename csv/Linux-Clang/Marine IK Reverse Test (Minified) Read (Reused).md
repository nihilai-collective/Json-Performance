
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 965.109 | 0.155844 | 6489.49ms | 1834197 | 30 | 2.39355e+08 | 1.81246e+06 | 0.00325902 | 2.56525 | 1(Win) | true |
| Jsonifier (two-stage) | 855.026 | 0.0955401 | 7261.71ms | 1834197 | 40 | 1.52815e+08 | 2.04582e+06 | 0.186694 | 2.89555 | 2(Loss) | true |
| Glaze | 759.337 | 0.104522 | 7965.71ms | 1834197 | 40 | 2.31898e+08 | 2.30362e+06 | 0.168631 | 3.26045 | 3(Loss) | true |
| simdjson (ondemand) | 674.821 | 0.160653 | 8833.3ms | 1834197 | 40 | 6.93669e+08 | 2.59213e+06 | 0.164228 | 3.66879 | 4(Loss) | true |
