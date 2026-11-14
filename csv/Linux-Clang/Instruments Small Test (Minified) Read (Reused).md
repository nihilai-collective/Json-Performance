
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2707.94 | 0.138982 | 903.104ms | 4669 | 2560 | 13369.8 | 1644.31 | 0.04101 | 1.91207 | 7.75027 | 1.52195 | 0.00129762 | 1.64817e-05 | 2.17525e-06 | 1(Win) | true |
| Glaze | 2322.6 | 0.119563 | 935.291ms | 4669 | 160 | 840.651 | 1917.12 | 0.0495288 | 2.22414 | 9.35875 | 1.63097 | 0.000797815 | 3.74813e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1941.65 | 0.385347 | 969.76ms | 4669 | 1280 | 99957.9 | 2293.25 | 0.0179843 | 2.65195 | 10.7278 | 1.80852 | 0.00116041 | 2.39278e-05 | 2.00792e-06 | 3(Loss) | true |
| simdjson (ondemand) | 687.901 | 0.0889487 | 1392.33ms | 4669 | 4890 | 162100 | 6472.89 | 0.143828 | 7.39958 | 28.1793 | 4.41208 | 0.00306455 | 5.75523e-05 | 2.4002e-05 | 4(Loss) | true |
