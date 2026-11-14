
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2159.17 | 0.392828 | 7299.75ms | 631514 | 640 | 7.6838e+08 | 278930 | 0.309598 | 2.33027 | 7.12857 | 1.07055 | 0.0121015 | 0.03937 | 0.000143188 | 1(Win) | true |
| simdjson (reflection) | 2060.53 | 0.705207 | 7650.68ms | 631514 | 160 | 6.79766e+08 | 292283 | 0.682548 | 2.44309 | 7.88765 | 1.14835 | 0.00990408 | 0.0368318 | 0.00013526 | 2(Loss) | true |
| Jsonifier | 1947.67 | 0.0270949 | 8149.45ms | 631514 | 1280 | 8.98506e+06 | 309220 | 0.043139 | 2.59264 | 7.29255 | 1.33469 | 0.00963699 | 0.0264002 | 0.000288717 | 3(Loss) | true |
| Glaze | 1830.98 | 0.0633558 | 8580.48ms | 631514 | 320 | 1.38971e+07 | 328928 | 0.181041 | 2.73395 | 9.28801 | 1.71561 | 0.0107344 | 0.0209411 | 3.96814e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1490.87 | 0.599342 | 5245.76ms | 631514 | 160 | 9.37897e+08 | 403964 | 0.117365 | 3.37099 | 10.1108 | 2.05452 | 0.0106921 | 0.0500496 | 0.000119059 | 5(Loss) | true |
