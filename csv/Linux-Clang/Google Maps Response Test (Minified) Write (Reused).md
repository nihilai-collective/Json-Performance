
----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12458.1 | 0.127413 | 822.435ms | 11812 | 2560 | 3397.89 | 904.217 | 0.49671 | 0.424716 | 2.04462 | 0.332035 | 8.88265e-05 | 2.28846e-05 | 1.0351e-05 | 1(Win) | true |
| Glaze | 4240.08 | 0.108752 | 1003.47ms | 11812 | 4890 | 40821.2 | 2656.74 | 0.371903 | 1.21188 | 5.37437 | 0.765324 | 0.00040673 | 3.57856e-05 | 1.51833e-05 | 2(Loss) | true |
