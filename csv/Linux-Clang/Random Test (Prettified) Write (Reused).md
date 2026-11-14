
----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15890.3 | 0.107661 | 5816.16ms | 837491 | 320 | 937050 | 50263 | 0.0767616 | 0.318305 | 1.35555 | 0.257614 | 0.00044877 | 0.016882 | 1.628e-05 | 1(Win) | true |
| Glaze | 4491.5 | 0.0769409 | 9517.06ms | 837491 | 2560 | 4.79217e+07 | 177823 | 0.106341 | 1.12373 | 4.56028 | 0.768648 | 0.00622463 | 0.017905 | 3.19108e-05 | 2(Loss) | true |
