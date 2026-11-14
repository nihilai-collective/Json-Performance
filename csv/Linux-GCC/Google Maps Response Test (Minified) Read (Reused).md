
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1540.17 | 0.0305194 | 1508.14ms | 11812 | 4890 | 24365.1 | 7313.99 | 0.0487381 | 3.35811 | 16.6684 | 3.09321 | 0.00393049 | 2.52248e-05 | 5.31503e-06 | 1(Win) | true |
| simdjson (ondemand) | 1174.12 | 0.0248316 | 1730.83ms | 11812 | 2560 | 14530.3 | 9594.29 | 0.0460796 | 4.40349 | 18.543 | 3.4139 | 0.00513041 | 2.80766e-05 | 2.24877e-06 | 2(Loss) | true |
