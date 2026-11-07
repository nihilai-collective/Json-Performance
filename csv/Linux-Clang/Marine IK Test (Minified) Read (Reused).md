
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 976.336 | 0.108974 | 6288.66ms | 1834197 | 80 | 3.04952e+08 | 1.79162e+06 | 0.730049 | 2.53575 | 1(Win) | true |
| Jsonifier (two-stage) | 881.788 | 0.121794 | 6901.25ms | 1834197 | 40 | 2.33492e+08 | 1.98373e+06 | 0.00665795 | 2.80766 | 2(Loss) | true |
| Glaze | 744.023 | 0.0746181 | 8050.15ms | 1834197 | 160 | 4.92411e+08 | 2.35104e+06 | 0.363994 | 3.32756 | 3(Loss) | true |
| simdjson (ondemand) | 683.031 | 0.191672 | 8635.73ms | 1834197 | 40 | 9.63808e+08 | 2.56098e+06 | 0.233784 | 3.62453 | 4(Loss) | true |
