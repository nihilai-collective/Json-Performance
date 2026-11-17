
----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17581.7 | 0.329411 | 795.686ms | 11521 | 320 | 1356.09 | 624.928 | 0.107628 | 0.31117 | 1.46012 | 0.265255 | 8.76118e-05 | 3.2278e-05 | 1.87158e-05 | 1(Win) | true |
| Glaze | 5469.6 | 0.0700879 | 933.562ms | 11521 | 4890 | 9693.15 | 2008.79 | 0.0691472 | 0.945164 | 3.62026 | 0.633279 | 0.00115557 | 2.72109e-05 | 1.02596e-05 | 2(Loss) | true |
