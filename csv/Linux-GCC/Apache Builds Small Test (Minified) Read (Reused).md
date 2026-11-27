
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2591.72 | 0.0554932 | 842.247ms | 2632 | 1280 | 369.729 | 968.495 | 0.163941 | 2.0418 | 8.27698 | 1.45251 | 0.00113358 | 8.13307e-05 | 2.64176e-05 | 1(Win) | true |
| simdjson (ondemand) | 1858.49 | 0.144756 | 894.012ms | 2632 | 80 | 305.787 | 1350.6 | 0 | 2.86441 | 9.91983 | 1.74392 | 0.00240786 | 0.000137728 | 9.49848e-05 | 2(Loss) | true |
