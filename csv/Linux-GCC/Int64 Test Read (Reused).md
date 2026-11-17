
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3784.3 | 0.078068 | 815.853ms | 3862 | 160 | 92.3679 | 973.256 | 0.154525 | 1.41824 | 6.70637 | 0.786121 | 0.000258933 | 1.4565e-05 | 0 | 1(Win) | true |
| Glaze | 1860.54 | 0.0980786 | 913.416ms | 3862 | 1280 | 4825.1 | 1979.58 | 0.289803 | 2.81691 | 14.1854 | 1.71129 | 0.000300403 | 1.73971e-05 | 1.82062e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1763.07 | 0.0840161 | 926.809ms | 3862 | 1280 | 3942.96 | 2089.03 | 0.0299272 | 2.97191 | 14.3084 | 1.56551 | 0.000261968 | 2.99392e-05 | 7.68708e-06 | 3(Loss) | true |
| simdjson (ondemand) | 749.466 | 0.0416112 | 1209.08ms | 3862 | 1280 | 5352.41 | 4914.28 | 0.042619 | 6.86131 | 31.8708 | 3.45236 | 0.00102703 | 1.88131e-05 | 2.22521e-06 | 4(Loss) | true |
