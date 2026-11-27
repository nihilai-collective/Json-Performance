
----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10354.2 | 0.453453 | 780.372ms | 4300 | 1280 | 4128.39 | 396.053 | 0.13435 | 0.538508 | 1.34674 | 0.207209 | 0.000233467 | 2.41642e-05 | 7.26744e-07 | 1(Win) | true |
| Glaze | 3584.47 | 0.488959 | 856.797ms | 4300 | 640 | 20026.8 | 1144.05 | 0.16882 | 1.45964 | 3.20907 | 0.507209 | 0.000238009 | 3.56105e-05 | 2.90698e-06 | 2(Loss) | true |
