
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5736.43 | 0.204166 | 781.038ms | 2889 | 4890 | 4702.06 | 480.293 | 0.0724393 | 0.957123 | 3.67809 | 0.496366 | 0.000437595 | 2.65445e-05 | 4.24712e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 5690.48 | 0.187536 | 782.529ms | 2889 | 4890 | 4031.58 | 484.171 | 0.124042 | 0.961589 | 3.67809 | 0.496366 | 0.000497975 | 2.89512e-05 | 7.57404e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5578.16 | 0.170989 | 784.284ms | 2889 | 4890 | 3487.86 | 493.92 | 0.146311 | 0.981165 | 3.70751 | 0.416754 | 0.0010724 | 3.51803e-05 | 7.92796e-06 | 3(Loss) | true |
| Glaze | 3181.97 | 0.211346 | 822.858ms | 2889 | 30 | 100.464 | 865.867 | 0.0616333 | 1.66542 | 6.72897 | 1.21634 | 0.000369217 | 4.61521e-05 | 0 | 4(Loss) | true |
