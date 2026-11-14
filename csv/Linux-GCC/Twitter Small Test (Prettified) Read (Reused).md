
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3279.72 | 0.0514319 | 842.698ms | 3808 | 320 | 103.785 | 1107.29 | 0.00338654 | 1.65814 | 6.02153 | 0.794905 | 0.000262605 | 5.17004e-05 | 8.20641e-07 | 1(Win) | true |
| simdjson (reflection) | 2767.43 | 0.235287 | 863.801ms | 3808 | 80 | 762.652 | 1312.26 | 0.284005 | 1.92179 | 6.9698 | 0.90625 | 0.000265888 | 0.000177258 | 5.58036e-05 | 2(Loss) | true |
| Jsonifier | 2726.62 | 0.0618197 | 866.351ms | 3808 | 40 | 27.1179 | 1331.9 | 0.127475 | 1.98292 | 5.84086 | 1.03624 | 0.000262605 | 0.000118172 | 0 | 3(Loss) | true |
| Glaze | 2570.61 | 0.137857 | 870.179ms | 3808 | 30 | 113.789 | 1412.73 | 0.303451 | 2.06136 | 7.97637 | 1.4073 | 0.000262605 | 8.7535e-06 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1769.95 | 0.0899429 | 935.843ms | 3808 | 160 | 544.912 | 2051.81 | 0.223167 | 2.97916 | 9.23398 | 1.77075 | 0.00158055 | 4.92384e-05 | 1.64128e-05 | 5(Loss) | true |
