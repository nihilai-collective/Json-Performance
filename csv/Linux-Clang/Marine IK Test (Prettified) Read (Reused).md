
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3088 | 0.136304 | 7742.73ms | 7351818 | 40 | 3.83103e+08 | 2.27048e+06 | 0.139357 | 0.801734 | 1(Win) | true |
| Jsonifier | 2864.59 | 0.136128 | 8278.62ms | 7351818 | 40 | 4.44034e+08 | 2.44755e+06 | 0.0645104 | 0.864265 | 2(Loss) | true |
| simdjson (ondemand) | 2438.51 | 0.134756 | 9697.25ms | 7351818 | 40 | 6.00475e+08 | 2.87521e+06 | 0.0830712 | 1.01527 | 3(Loss) | true |
| Glaze | 2322.13 | 0.0474258 | 10095.5ms | 7351818 | 160 | 3.28069e+08 | 3.01931e+06 | 0.42869 | 1.06616 | 4(Loss) | true |
