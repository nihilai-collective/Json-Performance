
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 853.585 | 0.192571 | 6490.34ms | 1834197 | 30 | 4.67198e+08 | 2.04927e+06 | 0.100169 | 2.90042 | 1(Win) | true |
| Jsonifier (two-stage) | 751.177 | 0.135805 | 7285.42ms | 1834197 | 40 | 4.00038e+08 | 2.32865e+06 | 0.555375 | 3.29585 | 2(Loss) | true |
| simdjson (reflection) | 652.604 | 0.138646 | 8298.25ms | 1834197 | 160 | 2.20967e+09 | 2.68038e+06 | 0.0242611 | 3.79368 | 3(Loss) | true |
| Glaze | 629.309 | 0.558268 | 8518.16ms | 1834197 | 30 | 7.2239e+09 | 2.7796e+06 | 1.42968 | 3.93409 | 4(Loss) | true |
| simdjson (ondemand) | 551.951 | 0.315133 | 9773.49ms | 1834197 | 40 | 3.9897e+09 | 3.16917e+06 | 0.0599834 | 4.4855 | 5(Loss) | true |
