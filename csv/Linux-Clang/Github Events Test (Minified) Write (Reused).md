
----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15173 | 0.590225 | 1104.01ms | 58581 | 640 | 302263 | 3682.01 | 0.0688687 | 0.33772 | 1.11872 | 0.156092 | 3.45675e-05 | 1.52567e-05 | 7.62833e-06 | 1(Win) | true |
| Glaze | 5635.29 | 0.208074 | 1740.93ms | 58581 | 2560 | 1.08932e+06 | 9913.8 | 0.280663 | 0.900515 | 2.55385 | 0.36587 | 5.27915e-05 | 1.89775e-05 | 7.42828e-06 | 2(Loss) | true |
