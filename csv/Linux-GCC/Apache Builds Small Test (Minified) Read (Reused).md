
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3544.32 | 0.0723947 | 797.292ms | 2632 | 2560 | 672.915 | 708.196 | 0.130563 | 1.53301 | 6.16109 | 1.00874 | 0.000767893 | 2.18168e-05 | 3.71034e-06 | 1(Win) | true |
| Glaze | 2550.87 | 0.058388 | 823.028ms | 2632 | 4890 | 1614.17 | 984.004 | 0.12769 | 2.09703 | 9.23366 | 1.68351 | 0.0010486 | 2.80487e-05 | 8.46899e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2336.45 | 0.0322852 | 838.958ms | 2632 | 1280 | 153.984 | 1074.31 | 0.000509051 | 2.28803 | 9.93085 | 1.44909 | 0.000760175 | 3.29479e-05 | 4.74924e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2104.2 | 0.0964842 | 853.13ms | 2632 | 80 | 105.975 | 1192.89 | 0.181612 | 2.52998 | 8.70555 | 1.55357 | 0.00138203 | 1.8997e-05 | 1.42477e-05 | 4(Loss) | true |
| simdjson (reflection) | 1990.58 | 0.178261 | 855.062ms | 2632 | 320 | 1616.87 | 1260.97 | 0.345754 | 2.67348 | 8.61816 | 1.32789 | 0.00209441 | 0.000213716 | 0.000140103 | 5(Loss) | true |
