
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 855.071 | 0.374389 | 1102.61ms | 9578 | 640 | 1.0237e+06 | 10682.5 | 0.0350918 | 2.8841 | 1(Win) | true |
| Glaze | 690.143 | 0.120473 | 1344.27ms | 9578 | 4890 | 1.24325e+06 | 13235.4 | 0.0532007 | 3.57516 | 2(Loss) | true |
| Jsonifier (two-stage) | 626.518 | 0.200747 | 1488.73ms | 9578 | 1280 | 1.09646e+06 | 14579.5 | 0.0241077 | 3.93988 | 3(Loss) | true |
| simdjson (ondemand) | 529.064 | 0.169184 | 1812.48ms | 9578 | 40 | 34128.2 | 17265 | 0.0869565 | 4.66637 | 4(Loss) | true |
