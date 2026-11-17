
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2626.04 | 0.169453 | 8812.91ms | 7351818 | 30 | 6.14054e+08 | 2.66989e+06 | 1.18803 | 0.942732 | 1(Win) | true |
| Jsonifier | 2376.36 | 0.174889 | 9432.86ms | 7351818 | 160 | 4.26e+09 | 2.95041e+06 | 0.78584 | 1.0418 | 2(Loss) | true |
| simdjson (ondemand) | 2042.23 | 0.548259 | 5149.44ms | 7351818 | 40 | 1.41714e+10 | 3.43313e+06 | 0.0148759 | 1.21223 | 3(Loss) | true |
| Glaze | 1944.06 | 0.138808 | 5423.75ms | 7351818 | 80 | 2.00489e+09 | 3.6065e+06 | 0.955536 | 1.27344 | 4(Loss) | true |
