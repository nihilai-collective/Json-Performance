
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4598.28 | 0.123692 | 7796.58ms | 699405 | 320 | 1.03015e+07 | 145055 | 0.334143 | 1.08733 | 4.43454 | 0.719483 | 0.00282578 | 0.00124399 | 3.63255e-06 | 1(Win) | true |
| Glaze | 3511.37 | 0.05964 | 5053.23ms | 699405 | 640 | 8.21411e+06 | 189956 | 0.129691 | 1.4339 | 5.22155 | 1.16244 | 0.0022027 | 0.00125834 | 4.90596e-06 | 2(Loss) | true |
| simdjson (ondemand) | 2305.02 | 0.0830728 | 8291.25ms | 767297 | 1280 | 8.90233e+07 | 317459 | 0.160921 | 2.16696 | 8.67119 | 1.1824 | 0.00357856 | 0.0835488 | 4.48266e-05 | 3(Loss) | true |
