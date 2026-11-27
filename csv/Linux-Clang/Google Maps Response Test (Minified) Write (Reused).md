
----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12995.9 | 0.248272 | 816.364ms | 11812 | 1280 | 5927.94 | 866.799 | 0.192257 | 0.414021 | 2.08119 | 0.283356 | 8.69746e-05 | 3.34009e-05 | 1.38895e-05 | 1(Win) | true |
| Glaze | 4393.03 | 0.110539 | 985.576ms | 11812 | 4890 | 39288 | 2564.24 | 0.0312122 | 1.18657 | 5.37437 | 0.765324 | 0.000483166 | 3.1215e-05 | 1.19285e-05 | 2(Loss) | true |
