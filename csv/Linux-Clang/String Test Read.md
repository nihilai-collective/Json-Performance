
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1777.31 | 0.074951 | 516.317ms | 9578 | 30 | 445.145 | 5139.4 | 0.0512644 | 1.38603 | 1(Win) | true |
| Jsonifier (two-stage) | 1658.35 | 0.0481993 | 559.111ms | 9578 | 80 | 563.857 | 5508.06 | 0.262785 | 1.4856 | 2(Loss) | true |
| Glaze | 1384.1 | 0.0500652 | 649.941ms | 9578 | 40 | 436.664 | 6599.45 | 0.0426621 | 1.78189 | 3(Loss) | true |
| simdjson (ondemand) | 1275.48 | 0.0621982 | 725.751ms | 9578 | 30 | 595.22 | 7161.43 | 0.00418928 | 1.93445 | 4(Loss) | true |
