
----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 955.765 | 0.103793 | 5872.35ms | 409725 | 80 | 1.44049e+07 | 408829 | 0.0578575 | 5.32808 | 25.8413 | 5.15292 | 0.00975679 | 0.00226942 | 2.31863e-06 | 1(Win) | true |
| simdjson (ondemand) | 491.477 | 0.134264 | 5365.24ms | 409725 | 80 | 9.11567e+07 | 795040 | 0.105338 | 10.3774 | 47.6272 | 8.62647 | 0.0318493 | 0.0128476 | 5.64098e-05 | 2(Loss) | true |
