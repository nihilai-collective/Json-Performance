
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1245.47 | 0.469158 | 756.941ms | 9578 | 640 | 757705 | 7334 | 0.0381638 | 1(Win) | true |
| Glaze | 1099.14 | 0.664278 | 918.385ms | 9578 | 80 | 243800 | 8310.4 | 0.19216 | 2(Loss) | true |
| simdjson (ondemand) | 690.277 | 0.34831 | 1363.29ms | 9578 | 640 | 1.35961e+06 | 13232.8 | 0.451372 | 3(Loss) | true |
| Jsonifier (two-stage) | 677.771 | 0.215463 | 1346.69ms | 9578 | 4890 | 4.12324e+06 | 13477 | 3.30181 | 4(Loss) | true |
