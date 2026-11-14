
----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14996.7 | 0.0378685 | 877.241ms | 25388 | 320 | 119.611 | 1614.48 | 0.034272 | 0.352173 | 1.88699 | 0.0881913 | 5.00975e-05 | 5.29285e-06 | 8.61628e-07 | 1(Win) | true |
| simdjson (stage-1) | 13833 | 0.0656696 | 889.981ms | 25388 | 2560 | 3382.15 | 1750.3 | 0.0441414 | 0.380563 | 1.77651 | 0.0766504 | 3.96195e-05 | 5.03129e-06 | 3.53883e-07 | 2(Loss) | true |
