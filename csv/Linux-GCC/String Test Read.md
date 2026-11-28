
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1378.74 | 0.112528 | 299.4ms | 4215 | 80 | 861.088 | 2915.53 | 0.21818 | 1.77887 | 1(Win) | true |
| Glaze | 1005.49 | 0.172714 | 404.544ms | 4215 | 2560 | 122049 | 3997.78 | 0.0883302 | 2.44566 | 2(Loss) | true |
| simdjson (reflection) | 988.966 | 0.361545 | 407.597ms | 4215 | 640 | 138209 | 4064.58 | 0.112815 | 2.48656 | 3(Loss) | true |
| simdjson (ondemand) | 706.987 | 0.0551108 | 574.756ms | 4215 | 160 | 1570.97 | 5685.73 | 0.335132 | 3.4848 | 4(Loss) | true |
