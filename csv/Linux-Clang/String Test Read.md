
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1801.78 | 0.225414 | 509.556ms | 9578 | 1280 | 167154 | 5069.59 | 0.0753007 | 1.36714 | 1(Win) | true |
| Glaze | 1447.13 | 0.0361782 | 637.538ms | 9578 | 40 | 208.589 | 6312.02 | 0.00330047 | 1.70411 | 2(Loss) | true |
| simdjson (ondemand) | 1291.19 | 0.242242 | 709.646ms | 9578 | 640 | 187953 | 7074.34 | 0.00726605 | 1.91042 | 3(Loss) | true |
| Jsonifier (two-stage) | 1083.88 | 0.106839 | 847.965ms | 9578 | 2560 | 207534 | 8427.39 | 0.0285307 | 2.27735 | 4(Loss) | true |
