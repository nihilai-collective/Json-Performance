
----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1019.7 | 0.0847301 | 1079.65ms | 3770 | 320 | 2856.04 | 3525.89 | 0.0290791 | 5.107 | 20.3621 | 3.81963 | 0.00172497 | 2.56963e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 543.617 | 0.0324697 | 1384.61ms | 3770 | 2560 | 11805.7 | 6613.76 | 0.0435303 | 9.52518 | 43.4584 | 8.6756 | 0.0101439 | 3.38818e-05 | 7.56383e-06 | 2(Loss) | true |
