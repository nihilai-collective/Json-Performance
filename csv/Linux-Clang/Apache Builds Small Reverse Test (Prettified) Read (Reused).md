
----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1814.01 | 0.0478067 | 905.763ms | 3370 | 4890 | 3508.04 | 1771.7 | 0.0847354 | 2.89658 | 11.8119 | 2.25816 | 0.00355598 | 4.10818e-05 | 5.21867e-06 | 1(Win) | true |
| simdjson (ondemand) | 998.313 | 0.0413042 | 1048.59ms | 3370 | 4890 | 8646.15 | 3219.31 | 0.00258466 | 5.21265 | 22.719 | 4.24689 | 0.00854254 | 3.68341e-05 | 1.08621e-05 | 2(Loss) | true |
