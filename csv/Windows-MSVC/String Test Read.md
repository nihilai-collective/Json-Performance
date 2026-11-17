
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 833.665 | 0.167313 | 1100.81ms | 9578 | 1280 | 430165 | 10956.8 | 0.249467 | 3.63801 | 1(Win) | true |
| Glaze | 707.862 | 0.148263 | 1312.28ms | 9578 | 320 | 117131 | 12904.1 | 0.591961 | 4.28565 | 2(Loss) | true |
| Jsonifier (two-stage) | 700.894 | 0.0726022 | 1309.04ms | 9578 | 2560 | 229184 | 13032.3 | 0.148448 | 4.32837 | 3(Loss) | true |
| simdjson (ondemand) | 671.585 | 0.104433 | 1361.37ms | 9578 | 1280 | 258247 | 13601.1 | 0.101197 | 4.51717 | 4(Loss) | true |
