
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2678.6 | 0.135203 | 907.555ms | 4669 | 4890 | 24701.1 | 1662.33 | 0.11802 | 1.93514 | 7.75027 | 1.52195 | 0.00129107 | 2.72432e-05 | 6.1319e-06 | 1(Win) | true |
| Glaze | 2315.74 | 0.305736 | 934.346ms | 4669 | 2560 | 88471.5 | 1922.8 | 0.435667 | 2.2695 | 9.35875 | 1.63097 | 0.000788027 | 5.51343e-05 | 2.82783e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1975.41 | 0.389381 | 968.349ms | 4669 | 2560 | 197207 | 2254.07 | 0.137116 | 2.60762 | 10.7278 | 1.80853 | 0.00132021 | 5.23734e-05 | 1.14619e-05 | 3(Loss) | true |
| simdjson (ondemand) | 690.793 | 0.0852982 | 1389.97ms | 4669 | 4890 | 147822 | 6445.79 | 0.0825406 | 7.3417 | 28.1803 | 4.41251 | 0.00279238 | 9.0358e-05 | 3.60906e-05 | 4(Loss) | true |
