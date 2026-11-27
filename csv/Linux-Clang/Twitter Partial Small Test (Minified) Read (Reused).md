
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5962.19 | 0.15588 | 767.04ms | 2889 | 4890 | 2537.31 | 462.106 | 0.252644 | 0.935141 | 3.61925 | 0.51748 | 0.00053443 | 3.53927e-05 | 2.54827e-06 | 1(Win) | true |
| Jsonifier | 5889.43 | 0.226525 | 771.125ms | 2889 | 2560 | 2874.9 | 467.816 | 0.102266 | 0.938484 | 3.61925 | 0.51748 | 0.000489194 | 5.40845e-05 | 7.57182e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5740.24 | 0.142286 | 770.592ms | 2889 | 1280 | 596.992 | 479.974 | 0.116842 | 0.963644 | 3.72032 | 0.417792 | 0.00100976 | 3.73183e-05 | 4.59718e-06 | 3(Loss) | true |
| Glaze | 3043.6 | 0.0960707 | 813.09ms | 2889 | 4890 | 3698.37 | 905.231 | 0.239066 | 1.75689 | 6.72897 | 1.21634 | 0.000366527 | 3.05085e-05 | 3.53927e-06 | 4(Loss) | true |
