
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1504.72 | 0.0880144 | 1528.92ms | 11812 | 2560 | 111143 | 7486.29 | 0.0253681 | 3.42109 | 16.6726 | 3.08762 | 0.00447906 | 2.50672e-05 | 4.56369e-06 | 1(Win) | true |
| simdjson (ondemand) | 1149.63 | 0.0569618 | 1762.27ms | 11812 | 1280 | 39875.4 | 9798.6 | 0.0248663 | 4.49611 | 18.6022 | 3.43117 | 0.00869819 | 2.13633e-05 | 4.62983e-06 | 2(Loss) | true |
