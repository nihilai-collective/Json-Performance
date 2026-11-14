
----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14638.1 | 0.233442 | 762.669ms | 5094 | 160 | 96.0346 | 331.875 | 0.13541 | 0.387765 | 1.67825 | 0.2766 | 0.000196309 | 9.81547e-06 | 0 | 1(Win) | true |
| Glaze | 3853.01 | 0.167239 | 860.959ms | 5094 | 4890 | 21742.2 | 1260.84 | 0.179063 | 1.3546 | 5.4413 | 0.804084 | 0.000237257 | 3.99845e-05 | 7.46698e-06 | 2(Loss) | true |
