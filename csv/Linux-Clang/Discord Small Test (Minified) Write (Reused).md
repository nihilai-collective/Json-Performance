
----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11365.5 | 0.292765 | 777.404ms | 4857 | 1280 | 1822.24 | 407.548 | 0.752828 | 0.491686 | 1.66049 | 0.242537 | 0.000206049 | 1.43157e-05 | 2.2519e-06 | 1(Win) | true |
| Glaze | 3608.97 | 0.185529 | 864.944ms | 4857 | 2560 | 14515.5 | 1283.47 | 0.415744 | 1.44848 | 3.68582 | 0.525428 | 0.000211116 | 7.77711e-05 | 2.83901e-05 | 2(Loss) | true |
