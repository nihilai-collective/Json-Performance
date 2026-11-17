
----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16449.4 | 0.229491 | 1085.64ms | 58581 | 4890 | 297068 | 3396.31 | 0.676376 | 0.310419 | 1.06791 | 0.16234 | 3.51112e-05 | 1.36389e-05 | 6.72692e-06 | 1(Win) | true |
| Glaze | 6040.34 | 0.181389 | 1676.15ms | 58581 | 2560 | 720528 | 9249.02 | 0.16539 | 0.840194 | 2.55385 | 0.36587 | 5.27181e-05 | 2.90797e-05 | 1.519e-05 | 2(Loss) | true |
