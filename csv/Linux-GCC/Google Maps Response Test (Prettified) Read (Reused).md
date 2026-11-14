
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2891.14 | 0.0262636 | 1618.05ms | 25388 | 640 | 3096.04 | 8374.51 | 0.0304216 | 1.79119 | 8.59434 | 1.48716 | 0.00246893 | 8.73937e-06 | 2.27716e-06 | 1(Win) | true |
| simdjson (ondemand) | 2393.99 | 0.0274613 | 1787.55ms | 25388 | 2560 | 19746.7 | 10113.6 | 0.0802316 | 2.15623 | 9.32653 | 1.61667 | 0.00189481 | 1.18012e-05 | 2.50795e-06 | 2(Loss) | true |
