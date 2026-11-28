
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1473.32 | 0.0762848 | 120.691ms | 1811 | 40 | 31.9872 | 1172.25 | 0.0440554 | 1.64658 | 1(Win) | true |
| Glaze | 1080.01 | 0.0368432 | 164.016ms | 1811 | 160 | 55.5415 | 1599.16 | 0.140506 | 2.25485 | 2(Loss) | true |
| simdjson (ondemand) | 420.33 | 0.140031 | 417.882ms | 1811 | 40 | 1324.23 | 4108.93 | 0.0131809 | 5.85493 | 3(Loss) | true |
| simdjson (reflection) | 392.977 | 0.165073 | 450.125ms | 1811 | 4890 | 257374 | 4394.92 | 0.120499 | 6.26346 | 4(Loss) | true |
