
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1197.35 | 0.0404207 | 9579.33ms | 461466 | 320 | 7.06308e+06 | 367552 | 0.0398059 | 4.22089 | 17.8094 | 3.2223 | 0.0192569 | 0.0441569 | 9.04658e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1089.99 | 0.114202 | 5231.08ms | 461466 | 160 | 3.40174e+07 | 403753 | 0.188766 | 4.62357 | 19.2173 | 3.44868 | 0.022549 | 0.0894678 | 0.000168837 | 2(Loss) | true |
| Glaze | 1053.03 | 0.182117 | 5400.61ms | 461466 | 80 | 4.63435e+07 | 417926 | 0.0662238 | 4.78412 | 20.1525 | 3.94161 | 0.0243223 | 0.03391 | 0.000107023 | 3(Loss) | true |
| simdjson (ondemand) | 977.417 | 0.179833 | 5855.86ms | 461466 | 160 | 1.04901e+08 | 450256 | 0.0433662 | 5.15097 | 20.2893 | 3.60155 | 0.0122087 | 0.0850626 | 0.000602252 | 4(Loss) | true |
| simdjson (reflection) | 966.002 | 0.0621086 | 5903.69ms | 461466 | 640 | 5.12397e+07 | 455577 | 0.212507 | 5.22615 | 18.5842 | 3.24557 | 0.0105076 | 0.0574983 | 0.000337819 | 5(Loss) | true |
