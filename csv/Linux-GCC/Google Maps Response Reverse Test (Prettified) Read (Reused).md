
----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1656.29 | 0.0452123 | 2232.45ms | 25388 | 1280 | 55912.4 | 14618.2 | 0.00623116 | 3.09741 | 14.1403 | 2.77655 | 0.00666106 | 1.19397e-05 | 2.6772e-06 | 1(Win) | true |
| simdjson (ondemand) | 1523.38 | 0.0335998 | 2363.99ms | 25388 | 1280 | 36502.6 | 15893.5 | 0.0267919 | 3.38715 | 14.8798 | 2.78612 | 0.00631628 | 1.76018e-05 | 7.50847e-06 | 2(Loss) | true |
