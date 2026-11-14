
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 925.973 | 1.88595 | 848.877ms | 9578 | 30 | 1.03833e+06 | 9864.53 | 0 | 1(Tie) | true |
| Glaze STATISTICAL TIE DID NOT CONVERGE | 922.751 | 0.692333 | 938.263ms | 9578 | 4890 | 2.29678e+07 | 9898.98 | 7.84966 | -(Tie) | false |
| simdjson (ondemand) | 705.994 | 0.216466 | 1368.15ms | 9578 | 4890 | 3.83563e+06 | 12938.2 | 0.94848 | 3(Loss) | true |
| Jsonifier (two-stage) | 673.382 | 0.234473 | 1430.35ms | 9578 | 4890 | 4.94677e+06 | 13564.8 | 4.82423e-05 | 4(Loss) | true |
