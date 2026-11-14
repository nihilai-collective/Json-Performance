
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2805.84 | 0.0610459 | 6995.37ms | 183677 | 4890 | 7.1024e+06 | 62429.8 | 0.106228 | 1.80176 | 7.75 | 1.28316 | 0.00187874 | 4.11187e-05 | 2.81892e-05 | 1(Win) | true |
| Glaze | 2543.9 | 0.0819735 | 7655.2ms | 183677 | 2560 | 8.15634e+06 | 68858 | 0.120186 | 1.98602 | 9.22145 | 1.7258 | 0.00317376 | 1.65797e-05 | 9.07036e-06 | 2(Loss) | true |
| Jsonifier | 2159.04 | 0.078275 | 8891.69ms | 183677 | 1280 | 5.16232e+06 | 81132.5 | 0.0126266 | 2.34619 | 8.42061 | 1.88919 | 0.00249701 | 3.02161e-05 | 2.10713e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1270.61 | 0.0764367 | 7477.24ms | 183677 | 2560 | 2.8427e+07 | 137862 | 0.0323737 | 3.95832 | 17.312 | 2.66701 | 0.00250109 | 5.48071e-05 | 3.40548e-05 | 4(Loss) | true |
