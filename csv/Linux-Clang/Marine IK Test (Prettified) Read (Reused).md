
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2872.81 | 0.107451 | 8383.7ms | 7351818 | 40 | 2.75078e+08 | 2.44055e+06 | 0.452555 | 0.861731 | 1(Win) | true |
| Jsonifier | 2605.52 | 0.369264 | 8919.45ms | 7351818 | 30 | 2.96209e+09 | 2.69092e+06 | 1.05323 | 0.950201 | 2(Loss) | true |
| simdjson (ondemand) | 2384.1 | 0.115974 | 9669.73ms | 7351818 | 30 | 3.48969e+08 | 2.94084e+06 | 0.488713 | 1.03845 | 3(Loss) | true |
| Glaze | 2227.11 | 0.0565843 | 5108.76ms | 7351818 | 80 | 2.53856e+08 | 3.14813e+06 | 0.0916824 | 1.11166 | 4(Loss) | true |
