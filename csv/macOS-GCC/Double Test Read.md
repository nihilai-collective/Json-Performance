
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 902.19 | 0.399683 | 206.825ms | 1811 | 4890 | 286274 | 1914.35 | 0.951643 | 1(Win) | true |
| Glaze | 791.231 | 0.45055 | 227.627ms | 1811 | 4890 | 472962 | 2182.81 | 0.632507 | 2(Loss) | true |
| Jsonifier (two-stage) | 481.463 | 1.94819 | 396.644ms | 1811 | 80 | 390717 | 3587.2 | 0.44405 | 3(Loss) | true |
| simdjson (ondemand) | 140.229 | 0.395769 | 1278.27ms | 1811 | 2560 | 6.08252e+06 | 12316.3 | 1.17708 | 4(Loss) | true |
