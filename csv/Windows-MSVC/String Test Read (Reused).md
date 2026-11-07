
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1339.94 | 0.289315 | 939.934ms | 9578 | 1280 | 497891 | 6816.95 | 0.198659 | 1.84103 | 1(Win) | true |
| Glaze | 973.114 | 0.0672489 | 1216.06ms | 9578 | 30 | 1195.4 | 9386.67 | 0.035524 | 2.53575 | 2(Loss) | true |
| Jsonifier (two-stage) | 852.987 | 0.169754 | 1316.11ms | 9578 | 2560 | 845952 | 10708.6 | 0.00583609 | 2.895 | 3(Loss) | true |
| simdjson (ondemand) | 682.579 | 0.209203 | 1607.19ms | 9578 | 640 | 501602 | 13382 | 0.00583771 | 3.62071 | 4(Loss) | true |
