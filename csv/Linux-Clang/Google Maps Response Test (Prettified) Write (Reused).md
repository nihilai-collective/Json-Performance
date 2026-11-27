
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16398 | 0.166811 | 914.142ms | 31235 | 640 | 5876.68 | 1816.57 | 0.185445 | 0.315597 | 1.42296 | 0.240499 | 9.92977e-05 | 5.60269e-06 | 1.75084e-06 | 1(Win) | true |
| Glaze | 5783.12 | 0.111946 | 1253.89ms | 31235 | 1280 | 42558.1 | 5150.85 | 0.0875621 | 0.896422 | 3.58447 | 0.627565 | 0.00224545 | 1.4482e-05 | 6.07792e-06 | 2(Loss) | true |
