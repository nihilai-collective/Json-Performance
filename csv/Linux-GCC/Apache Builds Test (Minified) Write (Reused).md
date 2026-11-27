
----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16150.4 | 0.116396 | 1296.11ms | 94653 | 30 | 1269.7 | 5589.23 | 0.0525094 | 0.315524 | 1.28243 | 0.179086 | 7.43065e-05 | 7.04327e-06 | 5.28245e-06 | 1(Win) | true |
| simdjson (reflection) | 13912.5 | 0.053358 | 1389ms | 94653 | 2560 | 30682.7 | 6488.25 | 0.128794 | 0.364178 | 2.03222 | 0.294423 | 3.22519e-05 | 4.60151e-06 | 2.146e-06 | 2(Loss) | true |
| Glaze | 9376.73 | 0.0910448 | 1714.05ms | 94653 | 320 | 24582.5 | 9626.83 | 0.000844003 | 0.541824 | 3.41879 | 0.557426 | 6.13095e-05 | 6.80116e-06 | 4.62215e-06 | 3(Loss) | true |
