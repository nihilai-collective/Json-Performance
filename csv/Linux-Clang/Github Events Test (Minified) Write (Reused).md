
----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16780.2 | 0.342615 | 1075.59ms | 58581 | 1280 | 166549 | 3329.35 | 0.0103024 | 0.302488 | 1.06791 | 0.162339 | 3.52343e-05 | 1.3683e-05 | 7.13489e-06 | 1(Win) | true |
| Glaze | 5962.52 | 0.177046 | 1679.98ms | 58581 | 2560 | 704476 | 9369.73 | 0.0796206 | 0.850409 | 2.55385 | 0.36587 | 3.78149e-05 | 2.62991e-05 | 1.31695e-05 | 2(Loss) | true |
