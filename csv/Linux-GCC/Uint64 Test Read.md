
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1894.02 | 0.11974 | 774.814ms | 1213 | 640 | 342.303 | 610.769 | 0.0860312 | 2.89959 | 13.488 | 2.28195 | 0.000874639 | 0.000171321 | 4.63726e-05 | 1(Win) | true |
| simdjson (reflection) | 994.069 | 0.0735276 | 827.987ms | 1213 | 4890 | 3580.13 | 1163.71 | 0.0860232 | 5.36366 | 26.6208 | 6.20363 | 0.000832663 | 0.000169264 | 6.9796e-05 | 2(Loss) | true |
| Glaze | 848.208 | 0.0534911 | 851.422ms | 1213 | 80 | 42.5766 | 1363.83 | 0.0311526 | 6.24682 | 23.2201 | 3.35284 | 0.00120569 | 0.00016488 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 377.388 | 0.0371487 | 1022.48ms | 1213 | 4890 | 6340.77 | 3065.3 | 0.409651 | 13.8285 | 58.7238 | 11.8054 | 0.00421187 | 0.00014701 | 5.85005e-05 | 4(Loss) | true |
