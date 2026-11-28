
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1307.37 | 0.0936073 | 324.443ms | 4215 | 30 | 248.506 | 3074.67 | 0.229276 | 1.87704 | 1(Win) | true |
| Glaze | 965.175 | 0.0662353 | 420.767ms | 4215 | 40 | 304.384 | 4164.77 | 0.0350036 | 2.54785 | 2(Loss) | true |
| simdjson (ondemand) | 815.404 | 0.274949 | 502.941ms | 4215 | 1280 | 235160 | 4929.75 | 0.118205 | 3.01983 | 3(Loss) | true |
