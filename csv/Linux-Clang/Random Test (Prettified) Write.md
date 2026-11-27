
----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14375.6 | 0.044801 | 6343.32ms | 837491 | 4890 | 3.02965e+06 | 55559 | 0.222472 | 0.352911 | 1.40067 | 0.242219 | 0.000473436 | 0.0161712 | 2.43311e-05 | 1(Win) | true |
| Glaze | 3874.77 | 0.115842 | 5476.8ms | 837491 | 1280 | 7.29809e+07 | 206127 | 0.029579 | 1.3002 | 4.56912 | 0.770719 | 0.00620552 | 0.0570846 | 5.21433e-05 | 2(Loss) | true |
