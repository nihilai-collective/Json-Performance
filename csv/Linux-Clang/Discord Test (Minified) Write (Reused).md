
----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14802.7 | 0.0875723 | 1113.86ms | 56369 | 2560 | 25892.3 | 3631.61 | 0.0925679 | 0.342336 | 1.41182 | 0.236478 | 0.0001466 | 1.11639e-05 | 5.55076e-06 | 1(Win) | true |
| Glaze | 5531.94 | 0.0575813 | 1720.23ms | 56369 | 4890 | 153108 | 9717.69 | 0.35874 | 0.912113 | 3.41113 | 0.467048 | 0.000123957 | 1.24762e-05 | 5.51798e-06 | 2(Loss) | true |
