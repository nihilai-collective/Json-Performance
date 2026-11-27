
----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2209.51 | 0.327418 | 808.022ms | 1691 | 1280 | 7309.9 | 729.873 | 0.260069 | 2.42899 | 7.48019 | 1.4453 | 0.00178149 | 0.000150614 | 3.97324e-05 | 1(Win) | true |
| Glaze | 1938.02 | 0.425815 | 826.165ms | 1691 | 160 | 2008.78 | 832.119 | 0.113287 | 2.78515 | 10.1307 | 1.91839 | 0.00125665 | 4.43525e-05 | 0 | 2(Loss) | true |
| Jsonifier (two-stage) | 1730.37 | 0.194978 | 827.192ms | 1691 | 4890 | 16146.9 | 931.974 | 0.0643366 | 3.04449 | 10.7246 | 1.77117 | 0.000608418 | 0.000162898 | 5.51458e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1357.48 | 0.307748 | 855.172ms | 1691 | 1280 | 17108.8 | 1187.98 | 0.231147 | 3.86269 | 12.495 | 2.06978 | 0.0011989 | 0.000163088 | 5.17445e-05 | 4(Loss) | true |
