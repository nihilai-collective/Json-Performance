
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 417.002 | 0.095048 | 422.529ms | 1811 | 4890 | 75780.2 | 4141.72 | 0.0802087 | 7.25896 | 1(Win) | true |
| Glaze | 145.626 | 0.308596 | 1177.32ms | 1798 | 1280 | 1.69001e+06 | 11774.7 | 0.246099 | 20.8257 | 2(Loss) | true |
