
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 758.662 | 0.234243 | 1385.49ms | 9578 | 30 | 23862.1 | 12040 | 0.249792 | 3.99706 | 1(Win) | true |
| simdjson (ondemand) | 734.946 | 0.361384 | 1249.18ms | 9578 | 4890 | 9.86473e+06 | 12428.5 | 0.131421 | 4.128 | 2(Loss) | true |
