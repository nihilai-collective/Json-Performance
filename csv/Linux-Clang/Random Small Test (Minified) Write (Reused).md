
----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14394.1 | 0.126172 | 758.073ms | 5094 | 4890 | 886.721 | 337.501 | 0.170273 | 0.397838 | 1.6755 | 0.243227 | 0.00048993 | 4.31961e-05 | 1.52953e-05 | 1(Win) | true |
| Glaze | 4241.09 | 0.214466 | 843.13ms | 5094 | 2560 | 15449.7 | 1145.46 | 0.0534432 | 1.24562 | 5.4413 | 0.804084 | 0.000250218 | 5.51353e-05 | 1.75605e-05 | 2(Loss) | true |
