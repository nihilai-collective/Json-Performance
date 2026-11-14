
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2226.31 | 0.808634 | 828.011ms | 2158 | 320 | 17880.8 | 924.413 | 0.0540592 | 2.37142 | 8.25626 | 1.36237 | 0.000470633 | 7.38531e-05 | 0 | 1(Win) | true |
| Glaze | 1946.69 | 0.221822 | 842.697ms | 2158 | 2560 | 14078.6 | 1057.19 | 0.239043 | 2.69767 | 9.8772 | 1.8962 | 0.000483484 | 0.000113133 | 2.96861e-05 | 2(Loss) | true |
| Jsonifier | 1862.71 | 0.294295 | 846.277ms | 2158 | 4890 | 51699.4 | 1104.86 | 0.109358 | 2.80505 | 8.92586 | 1.70621 | 0.000476375 | 9.66585e-05 | 2.15112e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1746.8 | 0.156904 | 856.018ms | 2158 | 4890 | 16710.6 | 1178.17 | 0.0367459 | 2.99204 | 9.9101 | 1.62836 | 0.000474195 | 0.000114853 | 2.02793e-05 | 4(Loss) | true |
