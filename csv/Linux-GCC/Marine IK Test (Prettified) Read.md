
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2619.73 | 0.134537 | 8335.5ms | 7351818 | 160 | 2.07434e+09 | 2.67632e+06 | 1.0015 | 0.945043 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2615.17 | 0.234013 | 8237.73ms | 7351818 | 30 | 1.18084e+09 | 2.68099e+06 | 0.0728309 | 0.946686 | 1(Tie) | true |
| simdjson (reflection) | 2379.76 | 0.154277 | 9076.93ms | 7351818 | 30 | 6.19795e+08 | 2.94619e+06 | 1.54034 | 1.04028 | 3(Loss) | true |
| simdjson (ondemand) | 2015.95 | 0.197407 | 5252.93ms | 7351818 | 80 | 3.77089e+09 | 3.47788e+06 | 0.295274 | 1.22804 | 4(Loss) | true |
| Glaze | 1926.97 | 0.194285 | 5440.2ms | 7351818 | 40 | 1.99883e+09 | 3.63848e+06 | 0.266332 | 1.28479 | 5(Loss) | true |
