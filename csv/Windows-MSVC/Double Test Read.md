
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 609.663 | 0.197861 | 289.597ms | 1811 | 4890 | 153633 | 2832.88 | 0.616927 | 4.9506 | 1(Win) | true |
| simdjson (ondemand) | 332.5 | 0.0845394 | 537.227ms | 1811 | 1280 | 24682.1 | 5194.3 | 0.482106 | 9.10445 | 2(Loss) | true |
