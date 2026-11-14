
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3671.47 | 0.0493304 | 834.32ms | 3862 | 1280 | 313.46 | 1003.16 | 0.137655 | 1.43919 | 6.70662 | 0.786171 | 0.000329128 | 7.22181e-05 | 2.12406e-05 | 1(Win) | true |
| Glaze | 1838.52 | 0.10297 | 932.061ms | 3862 | 2560 | 10893 | 2003.29 | 0.240534 | 2.80295 | 14.1854 | 1.71129 | 0.000325386 | 4.11663e-05 | 1.08226e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1742.85 | 0.0407357 | 943.905ms | 3862 | 4890 | 3623.79 | 2113.25 | 0.0727739 | 2.95861 | 14.3084 | 1.56551 | 0.000263964 | 4.74976e-05 | 1.3132e-05 | 3(Loss) | true |
| simdjson (ondemand) | 727.743 | 0.111972 | 1238.14ms | 3862 | 320 | 10276.3 | 5060.98 | 0.0774288 | 6.99639 | 31.8708 | 3.45236 | 0.00103816 | 4.3695e-05 | 2.02292e-05 | 4(Loss) | true |
