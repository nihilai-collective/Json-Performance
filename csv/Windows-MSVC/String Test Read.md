
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 647.648 | 0.317884 | 744.187ms | 4215 | 30 | 11678.2 | 6206.67 | 1.16773 | 3.79665 | 1(Win) | true |
| Glaze | 494.838 | 0.127732 | 807.108ms | 4215 | 30 | 3229.89 | 8123.33 | 0.0410509 | 4.98158 | 2(Loss) | true |
| simdjson (ondemand) | 404.502 | 0.17162 | 1025.24ms | 4215 | 40 | 11634.6 | 9937.5 | 0.0921582 | 6.0998 | 3(Loss) | true |
