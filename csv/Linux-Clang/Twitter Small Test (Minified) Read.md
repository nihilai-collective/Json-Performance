
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2666.12 | 0.181991 | 831.898ms | 2889 | 30 | 106.11 | 1033.4 | 0.0258114 | 1.97073 | 5.99238 | 1.08377 | 0.00211146 | 6.92281e-05 | 2.3076e-05 | 1(Win) | true |
| Glaze | 2392.61 | 0.276477 | 849.543ms | 2889 | 1280 | 12974.2 | 1151.53 | 0.28191 | 2.21272 | 8.84112 | 1.51713 | 0.000363448 | 3.73183e-05 | 5.40845e-07 | 2(Loss) | true |
| Jsonifier (two-stage) | 2202.95 | 0.284419 | 855.985ms | 2889 | 2560 | 32392.6 | 1250.67 | 0.00843225 | 2.38618 | 8.55244 | 1.3001 | 0.000699988 | 8.53182e-05 | 2.46084e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1010.55 | 0.095543 | 1008.16ms | 2889 | 4890 | 33180.4 | 2726.39 | 0.261143 | 5.08354 | 17.3925 | 2.86154 | 0.000367164 | 7.2555e-05 | 1.45818e-05 | 4(Loss) | true |
