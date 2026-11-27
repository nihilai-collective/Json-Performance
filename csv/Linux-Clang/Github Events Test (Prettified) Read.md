
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2048 | 0.178744 | 3776.48ms | 65103 | 1280 | 3.7585e+06 | 30315.9 | 0.132513 | 2.4794 | 7.8095 | 1.5342 | 0.00969537 | 0.000113126 | 3.37806e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1691.08 | 0.201421 | 4418.99ms | 65103 | 640 | 3.49995e+06 | 36714.4 | 0.0869815 | 2.9946 | 9.96615 | 1.68144 | 0.0129703 | 0.000216196 | 8.80336e-05 | 2(Loss) | true |
| Glaze | 1532.41 | 0.0807458 | 4796.5ms | 65103 | 2560 | 2.73989e+06 | 40516 | 0.357664 | 3.31282 | 10.9126 | 2.10043 | 0.0204388 | 0.000102542 | 4.17127e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1148.58 | 0.206345 | 6140.22ms | 65103 | 320 | 3.98121e+06 | 54055.4 | 0.131895 | 4.40086 | 12.9806 | 2.27359 | 0.0125058 | 9.84018e-05 | 5.20329e-05 | 4(Loss) | true |
