
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 994.052 | 0.159445 | 1277.23ms | 4604 | 1280 | 63486.9 | 4416.99 | 0.16692 | 5.13601 | 20.0226 | 4.34079 | 0.0053632 | 6.07488e-05 | 2.37565e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 837.106 | 0.0968255 | 1356.86ms | 4604 | 4890 | 126124 | 5245.11 | 0.0233689 | 6.12703 | 24.0706 | 4.82124 | 0.00605146 | 0.000141159 | 7.82195e-05 | 2(Loss) | true |
| Glaze | 733.053 | 0.0567632 | 1430.98ms | 4604 | 4890 | 56525.3 | 5989.63 | 0.166463 | 6.94231 | 29.3108 | 5.84948 | 0.00464778 | 7.71535e-05 | 3.52676e-05 | 3(Loss) | true |
| simdjson (ondemand) | 557.429 | 0.078399 | 1628.85ms | 4604 | 2560 | 97623 | 7876.72 | 0.164341 | 9.10978 | 37.4058 | 6.53685 | 0.00474019 | 8.49295e-05 | 2.64715e-05 | 4(Loss) | true |
