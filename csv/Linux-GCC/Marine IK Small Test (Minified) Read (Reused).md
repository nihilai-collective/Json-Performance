
----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1147.32 | 0.152077 | 1195.82ms | 4604 | 40 | 1354.84 | 3826.93 | 0.228772 | 4.54764 | 19.4788 | 4.20708 | 0.00329062 | 5.43006e-05 | 5.43006e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 912.983 | 0.0398589 | 1292.44ms | 4604 | 4890 | 17968.2 | 4809.2 | 0.129373 | 5.67776 | 24.424 | 4.77467 | 0.00473075 | 9.26997e-05 | 3.06482e-05 | 2(Loss) | true |
| Glaze | 736.39 | 0.0296272 | 1409.64ms | 4604 | 4890 | 15259.7 | 5962.49 | 0.0719514 | 7.01855 | 29.1183 | 5.84894 | 0.00655911 | 7.44884e-05 | 3.03817e-05 | 3(Loss) | true |
| simdjson (reflection) | 730.536 | 0.0517165 | 1425.99ms | 4604 | 2560 | 24733.6 | 6010.27 | 0.00632421 | 7.048 | 26.2007 | 4.95129 | 0.00425547 | 9.70623e-05 | 3.63135e-05 | 4(Loss) | true |
| simdjson (ondemand) | 541.251 | 0.0907301 | 1655.79ms | 4604 | 320 | 17335.1 | 8112.17 | 0.0255854 | 9.561 | 33.1077 | 6.60541 | 0.0145804 | 0.00010928 | 4.54768e-05 | 5(Loss) | true |
