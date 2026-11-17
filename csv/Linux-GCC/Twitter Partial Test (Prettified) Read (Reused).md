
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9151.2 | 0.0545304 | 7393.25ms | 631514 | 1280 | 1.64853e+06 | 65812 | 0.00146129 | 0.552034 | 2.70327 | 0.279147 | 0.000573702 | 1.58758e-05 | 1.34721e-05 | 1(Win) | true |
| Jsonifier | 9132.26 | 0.0525198 | 7486.57ms | 631514 | 1280 | 1.53555e+06 | 65948.5 | 0.095408 | 0.552308 | 2.70494 | 0.279568 | 0.000592732 | 9.81644e-06 | 7.9447e-06 | 2(Loss) | true |
| simdjson (reflection) | 8364.93 | 0.021421 | 8016.21ms | 631514 | 2560 | 608924 | 71998 | 0.0499569 | 0.603563 | 3 | 0.288219 | 0.000673171 | 2.7173e-06 | 1.7004e-06 | 3(Loss) | true |
| simdjson (ondemand) | 8261.81 | 0.0291076 | 8101.22ms | 631514 | 4890 | 2.2016e+06 | 72896.7 | 0.00642905 | 0.61153 | 3.00993 | 0.285943 | 0.000584438 | 2.9374e-06 | 1.83414e-06 | 4(Loss) | true |
| Glaze | 3877.77 | 0.0368949 | 8347.14ms | 631514 | 2560 | 8.40574e+06 | 155311 | 0.0688016 | 1.30046 | 5.82432 | 0.955105 | 0.00132069 | 8.40923e-06 | 7.06388e-06 | 5(Loss) | true |
