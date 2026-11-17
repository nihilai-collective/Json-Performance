
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14612.4 | 0.108466 | 1124.76ms | 56369 | 40 | 636.913 | 3678.9 | 0.0298913 | 0.350025 | 1.42142 | 0.238677 | 0.000172524 | 5.32207e-06 | 4.43506e-07 | 1(Win) | true |
| Glaze | 4957.68 | 0.11903 | 1840.61ms | 56369 | 2560 | 426457 | 10843.3 | 0.209919 | 1.01298 | 3.48779 | 0.484203 | 0.000138734 | 1.91816e-05 | 9.50073e-06 | 2(Loss) | true |
