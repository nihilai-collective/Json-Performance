
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2111.22 | 0.226935 | 6343.12ms | 124597 | 160 | 2.61018e+06 | 56282.7 | 0.0620587 | 2.38448 | 10.6706 | 2.15318 | 0.00721667 | 9.78154e-06 | 6.16989e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1644.55 | 0.191383 | 8014.01ms | 124597 | 160 | 3.0595e+06 | 72254 | 0.0254982 | 3.06792 | 13.4648 | 2.39364 | 0.0121203 | 2.42281e-05 | 1.66035e-05 | 2(Loss) | true |
| Glaze | 1631.12 | 0.1128 | 8013.69ms | 124597 | 2560 | 1.72865e+07 | 72848.8 | 0.162238 | 3.10714 | 13.9268 | 2.76804 | 0.0118022 | 4.14367e-05 | 2.95045e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1577.81 | 0.0775076 | 8298.17ms | 124597 | 640 | 2.18059e+06 | 75310 | 0.215354 | 3.20852 | 13.1596 | 2.39452 | 0.00851202 | 2.05538e-05 | 9.44294e-06 | 4(Loss) | true |
