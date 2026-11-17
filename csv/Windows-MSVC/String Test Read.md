
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 535.619 | 0.104234 | 1720.62ms | 9578 | 4890 | 1.54513e+06 | 17053.7 | 0.345192 | 4.61129 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 534.899 | 0.107588 | 1958.12ms | 9578 | 30 | 10126.4 | 17076.7 | 0.372257 | 4.61364 | 1(Tie) | true |
