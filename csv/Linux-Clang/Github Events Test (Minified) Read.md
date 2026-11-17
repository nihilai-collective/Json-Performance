
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1788.68 | 0.123829 | 3640.84ms | 53331 | 2560 | 3.17379e+06 | 28434.7 | 0.304287 | 2.82532 | 10.6192 | 1.88423 | 0.00175396 | 0.000233045 | 0.000140228 | 1(Win) | true |
| Jsonifier | 1600.11 | 0.118065 | 3927.44ms | 53331 | 2560 | 3.6053e+06 | 31785.5 | 0.233244 | 3.15629 | 9.89229 | 1.7817 | 0.0138464 | 0.000415221 | 0.000193075 | 2(Loss) | true |
| Glaze | 1428.04 | 0.0594984 | 4320.11ms | 53331 | 4890 | 2.19581e+06 | 35615.4 | 0.163775 | 3.52164 | 11.6956 | 2.24687 | 0.0214922 | 0.000206317 | 0.00011359 | 3(Loss) | true |
| simdjson (ondemand) | 974.958 | 0.138229 | 5814.19ms | 53331 | 640 | 3.32785e+06 | 52166.8 | 0.0897839 | 5.20435 | 15.3902 | 2.7677 | 0.0146101 | 0.000135123 | 6.19363e-05 | 4(Loss) | true |
