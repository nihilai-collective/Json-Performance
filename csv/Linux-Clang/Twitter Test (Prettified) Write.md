
----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16608.2 | 0.309751 | 5035.9ms | 716365 | 160 | 2.59757e+06 | 41134.9 | 0.273968 | 0.303373 | 1.08505 | 0.173199 | 0.000223202 | 0.00640094 | 7.6602e-06 | 1(Win) | true |
| Glaze | 4142.51 | 0.170782 | 8901.02ms | 716365 | 640 | 5.07698e+07 | 164919 | 0.0343261 | 1.22113 | 2.81742 | 0.4635 | 0.000532652 | 0.0450889 | 7.82859e-05 | 2(Loss) | true |
