
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1120.3 | 0.0865426 | 1214.66ms | 4630 | 320 | 3723.08 | 3941.36 | 0.0404529 | 4.55949 | 22.1035 | 4.71447 | 0.000888904 | 2.29482e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 923.181 | 0.0794082 | 1290.81ms | 4630 | 30 | 432.754 | 4782.93 | 0.00627191 | 5.63545 | 25.327 | 5.12462 | 0.00192945 | 5.0396e-05 | 7.19942e-06 | 2(Loss) | true |
| Glaze | 864.72 | 0.0474803 | 1336.78ms | 4630 | 160 | 940.498 | 5106.29 | 0.259421 | 6.00631 | 26.1114 | 4.82613 | 0.00441415 | 2.83477e-05 | 5.39957e-06 | 3(Loss) | true |
| simdjson (reflection) | 849.717 | 0.0970586 | 1336.52ms | 4630 | 80 | 2035.04 | 5196.45 | 0.0817198 | 6.00006 | 25.0257 | 4.51231 | 0.00866901 | 5.12959e-05 | 1.34989e-05 | 4(Loss) | true |
| simdjson (ondemand) | 744.487 | 0.0932191 | 1411.49ms | 4630 | 1280 | 39126.3 | 5930.95 | 0.0508714 | 6.82787 | 27.74 | 5.25033 | 0.00409692 | 7.35691e-05 | 3.03726e-05 | 5(Loss) | true |
