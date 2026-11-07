
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2782.37 | 0.116222 | 7863.93ms | 7351818 | 160 | 1.37232e+09 | 2.51988e+06 | 0.55611 | 0.889808 | 1(Win) | true |
| Jsonifier | 2569.69 | 0.237291 | 8526.12ms | 7351818 | 30 | 1.25751e+09 | 2.72844e+06 | 0.353582 | 0.963446 | 2(Loss) | true |
| simdjson (ondemand) | 2249.12 | 0.0539216 | 9716.38ms | 7351818 | 160 | 4.52074e+08 | 3.11733e+06 | 0.110742 | 1.10077 | 3(Loss) | true |
| Glaze | 2152.54 | 0.0782262 | 10082.1ms | 7351818 | 80 | 5.19377e+08 | 3.2572e+06 | 0.287616 | 1.15016 | 4(Loss) | true |
