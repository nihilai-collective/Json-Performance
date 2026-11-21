
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 926.047 | 0.191921 | 1043.28ms | 9578 | 80 | 28669.3 | 9863.75 | 0.541971 | 2.66099 | 1(Win) | true |
| Jsonifier (two-stage) | 888.735 | 0.138065 | 1059.41ms | 9578 | 4890 | 984645 | 10277.9 | 0.736786 | 2.7716 | 2(Loss) | true |
| Glaze | 743.246 | 0.183256 | 1278.22ms | 9578 | 2560 | 1.2985e+06 | 12289.7 | 0.571698 | 3.31894 | 3(Loss) | true |
| simdjson (ondemand) | 647.975 | 0.196813 | 1466.8ms | 9578 | 30 | 23092 | 14096.7 | 0.475172 | 3.80842 | 4(Loss) | true |
