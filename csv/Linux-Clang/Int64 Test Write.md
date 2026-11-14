
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 897.979 | 0.16064 | 1151.03ms | 3862 | 30 | 1302.33 | 4101.53 | 0.0968054 | 5.6872 | 26.4037 | 5.40963 | 0.00780252 | 1.72622e-05 | 0 | 1(Win) | true |
| Glaze | 892.259 | 0.184994 | 1158.62ms | 3862 | 640 | 37319.7 | 4127.82 | 0.0683332 | 5.72155 | 29.5873 | 5.69575 | 0.00725013 | 0.000130276 | 6.47333e-05 | 2(Loss) | true |
