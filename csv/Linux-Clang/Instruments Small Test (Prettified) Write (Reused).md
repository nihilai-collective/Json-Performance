
----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16039.5 | 0.217609 | 788.064ms | 9249 | 4890 | 7002.73 | 549.925 | 0.125588 | 0.338717 | 1.16791 | 0.2783 | 0.000109071 | 2.85666e-05 | 1.1011e-05 | 1(Win) | true |
| Glaze | 2721.24 | 0.110873 | 1062.11ms | 9249 | 4890 | 63156.2 | 3241.37 | 0.132167 | 1.88607 | 3.62255 | 0.590443 | 0.000372914 | 9.86123e-06 | 2.14471e-06 | 2(Loss) | true |
