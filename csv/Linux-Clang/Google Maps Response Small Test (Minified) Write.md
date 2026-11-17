
----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10411.9 | 0.226466 | 774.077ms | 4390 | 40 | 33.1692 | 402.1 | 0.14944 | 0.53627 | 2.25535 | 0.37221 | 0.000455581 | 2.84738e-05 | 0 | 1(Win) | true |
| Glaze | 3674.59 | 0.137287 | 850.083ms | 4390 | 4890 | 11964 | 1139.35 | 0.254816 | 1.42923 | 5.77927 | 0.860365 | 0.000543483 | 0.000138025 | 6.57285e-05 | 2(Loss) | true |
