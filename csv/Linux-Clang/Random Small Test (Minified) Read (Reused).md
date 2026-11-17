
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1548.13 | 0.069532 | 1069.6ms | 4926 | 2560 | 11396.8 | 3034.5 | 0.0266152 | 3.36846 | 14.4533 | 2.75822 | 0.00430885 | 3.74289e-05 | 3.72704e-06 | 1(Win) | true |
| simdjson (ondemand) | 1272.75 | 0.035804 | 1128.97ms | 4926 | 2560 | 4471 | 3691.06 | 0.112157 | 4.09103 | 16.9959 | 2.8512 | 0.00368477 | 4.06802e-05 | 1.03088e-05 | 2(Loss) | true |
