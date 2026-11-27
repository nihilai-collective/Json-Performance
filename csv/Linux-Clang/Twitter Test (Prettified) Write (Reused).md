
----
### Twitter Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16632.9 | 0.861473 | 5006.36ms | 716365 | 30 | 3.75608e+06 | 41073.8 | 0.094472 | 0.304096 | 1.08434 | 0.173036 | 0.000224885 | 0.00613905 | 9.0131e-05 | 1(Win) | true |
| Glaze | 4777.43 | 0.123968 | 7711.06ms | 716365 | 1280 | 4.02261e+07 | 143001 | 0.0703169 | 1.06155 | 2.80754 | 0.461218 | 0.000533235 | 0.00643849 | 3.6976e-05 | 2(Loss) | true |
