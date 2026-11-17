
----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6320.81 | 0.175482 | 9495.39ms | 9930848 | 40 | 2.76535e+08 | 1.49835e+06 | 0.0356993 | 0.796308 | 2.51818 | 0.14758 | 0.000363637 | 0.0249799 | 0.000460593 | 1(Win) | true |
| Glaze | 4019.13 | 0.234598 | 7344.94ms | 9930228 | 40 | 1.22225e+09 | 2.35628e+06 | 0.00772238 | 1.25141 | 4.4153 | 0.474313 | 0.000785458 | 0.0224236 | 0.000424064 | 2(Loss) | true |
| simdjson (reflection) | 306.343 | 1.92745 | 9352.86ms | 10018896 | 30 | 1.0842e+13 | 3.11897e+07 | 0.689507 | 13.2489 | 38.7853 | 5.80152 | 0.0258138 | 0.29146 | 0.142776 | 3(Loss) | true |
