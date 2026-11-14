
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1182.11 | 0.120049 | 1176.91ms | 4604 | 320 | 6362.47 | 3714.31 | 0.0228055 | 4.40418 | 18.6979 | 3.86187 | 0.00312568 | 5.70156e-05 | 5.43006e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 946.614 | 0.0458433 | 1271.4ms | 4604 | 2560 | 11574.9 | 4638.34 | 0.0727149 | 5.47785 | 22.5654 | 4.32146 | 0.00238091 | 7.1015e-05 | 1.48478e-05 | 2(Loss) | true |
| Glaze | 739.592 | 0.0620833 | 1402.56ms | 4604 | 4890 | 66427.2 | 5936.68 | 0.276464 | 6.98417 | 29.5996 | 5.96271 | 0.00606119 | 5.0725e-05 | 1.84778e-05 | 3(Loss) | true |
| simdjson (reflection) | 714.434 | 0.0440792 | 1437.74ms | 4604 | 4890 | 35885.8 | 6145.72 | 0.103631 | 7.24953 | 27.0929 | 5.08338 | 0.00833911 | 0.000131876 | 5.97862e-05 | 4(Loss) | true |
| simdjson (ondemand) | 535.736 | 0.0439427 | 1654.73ms | 4604 | 4890 | 63423.8 | 8195.67 | 0.0677515 | 9.64215 | 33.119 | 6.65388 | 0.0144605 | 0.000103316 | 3.86434e-05 | 5(Loss) | true |
