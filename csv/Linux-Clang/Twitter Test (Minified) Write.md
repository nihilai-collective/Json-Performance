
----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16888 | 0.116326 | 3446.95ms | 475954 | 4890 | 4.78005e+06 | 26877.3 | 0.13882 | 0.298485 | 1.08677 | 0.142858 | 0.000265044 | 0.000930292 | 1.33539e-05 | 1(Win) | true |
| Glaze | 6090.65 | 0.127587 | 8220.61ms | 475954 | 4890 | 4.42107e+07 | 74524.9 | 0.362706 | 0.826344 | 2.36368 | 0.337182 | 0.000347806 | 0.0161668 | 3.39935e-05 | 2(Loss) | true |
