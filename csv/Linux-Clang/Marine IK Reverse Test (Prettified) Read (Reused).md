
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2736.48 | 0.101175 | 8664.51ms | 7351818 | 80 | 5.37575e+08 | 2.56214e+06 | 0.062313 | 1.84628 | 8.02891 | 1.53231 | 0.0104871 | 0.0540882 | 0.000663795 | 1(Win) | true |
| Jsonifier | 2617.65 | 0.138166 | 9008.29ms | 7351818 | 30 | 4.10858e+08 | 2.67844e+06 | 0.0820165 | 1.92809 | 8.42725 | 1.90977 | 0.00738044 | 0.0268226 | 0.000852973 | 2(Loss) | true |
| simdjson (ondemand) | 2346.71 | 0.0859848 | 9979.2ms | 7351818 | 80 | 5.27965e+08 | 2.98769e+06 | 0.436765 | 2.15124 | 9.34252 | 1.41876 | 0.00875539 | 0.0535006 | 0.000422186 | 3(Loss) | true |
| Glaze | 2329.55 | 0.0803025 | 10034.8ms | 7351818 | 160 | 9.34592e+08 | 3.00969e+06 | 0.103229 | 2.17266 | 10.2816 | 2.06796 | 0.00868906 | 0.0272952 | 0.00196472 | 4(Loss) | true |
