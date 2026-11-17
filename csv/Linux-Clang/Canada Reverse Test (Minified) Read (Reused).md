
----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 852.407 | 0.652694 | 8489.12ms | 2090234 | 80 | 1.86382e+10 | 2.33856e+06 | 0.168369 | 5.96683 | 30.3269 | 5.7316 | 0.0220575 | 0.129408 | 0.00108002 | 1(Win) | true |
| simdjson (ondemand) | 802.358 | 0.109447 | 8964.42ms | 2090234 | 80 | 5.9149e+08 | 2.48443e+06 | 0.166248 | 6.30694 | 30.7483 | 5.32089 | 0.0220614 | 0.15228 | 0.000290888 | 2(Loss) | true |
