
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 658.703 | 0.151401 | 634.956ms | 4215 | 80 | 6829.11 | 6102.5 | 0.205255 | 3.73443 | 1(Win) | true |
| Glaze | 516.233 | 0.171233 | 752.714ms | 4215 | 30 | 5333.33 | 7786.67 | 0.17094 | 4.78402 | 2(Loss) | true |
| simdjson (ondemand) | 271.146 | 0.197326 | 1017.25ms | 4215 | 40 | 34230.8 | 14825 | 0.0112435 | 9.11647 | 3(Loss) | true |
