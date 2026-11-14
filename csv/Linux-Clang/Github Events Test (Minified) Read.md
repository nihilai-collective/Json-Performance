
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1772.07 | 0.131476 | 3656.05ms | 53331 | 1280 | 1.82263e+06 | 28701.1 | 0.0515911 | 2.85533 | 10.6192 | 1.88423 | 0.00171479 | 0.000132076 | 8.11559e-05 | 1(Win) | true |
| Jsonifier | 1653.88 | 0.0835094 | 3824.77ms | 53331 | 2560 | 1.68834e+06 | 30752.1 | 0.217266 | 3.05974 | 9.89229 | 1.7817 | 0.0122946 | 0.000131182 | 6.76275e-05 | 2(Loss) | true |
| Glaze | 1440.89 | 0.0693667 | 4288.94ms | 53331 | 2560 | 1.53477e+06 | 35298 | 0.082342 | 3.51051 | 11.6953 | 2.24686 | 0.0226939 | 9.19449e-05 | 5.27294e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1011.51 | 0.0799281 | 5845.77ms | 53331 | 4890 | 7.89823e+06 | 50281.9 | 0.112668 | 5.00009 | 15.3877 | 2.76721 | 0.00855108 | 0.000120028 | 7.56973e-05 | 4(Loss) | true |
