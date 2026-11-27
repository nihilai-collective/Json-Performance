
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11970.1 | 0.165552 | 760.725ms | 4390 | 2560 | 858.314 | 349.758 | 0.32179 | 0.471712 | 2.16447 | 0.297267 | 0.000229392 | 4.95622e-05 | 1.62835e-05 | 1(Win) | true |
| Glaze | 3911.07 | 0.603665 | 837.261ms | 4390 | 160 | 6681.13 | 1070.46 | 0.107898 | 1.34296 | 5.37927 | 0.771071 | 0.000605068 | 6.12187e-05 | 0 | 2(Loss) | true |
