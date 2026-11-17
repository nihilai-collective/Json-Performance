
----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14196.3 | 0.239524 | 766.046ms | 5094 | 4890 | 3285.29 | 342.203 | 0.164578 | 0.399231 | 1.68728 | 0.277582 | 0.000197273 | 2.15579e-05 | 4.29552e-06 | 1(Win) | true |
| Glaze | 3494.64 | 0.277058 | 875.742ms | 5094 | 2560 | 37974.7 | 1390.13 | 0.0384819 | 1.49022 | 5.4413 | 0.804083 | 0.000250908 | 5.0611e-05 | 1.38797e-05 | 2(Loss) | true |
