
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 810.253 | 0.130611 | 222.243ms | 1811 | 320 | 2480.31 | 2131.56 | 0.220394 | 3.01645 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 804.81 | 0.407079 | 235.709ms | 1811 | 2560 | 195365 | 2145.98 | 0.129072 | 3.03819 | 1(Tie) | true |
| Glaze | 415.836 | 0.223052 | 394.48ms | 1811 | 30 | 2574.71 | 4153.33 | 0 | 5.90869 | 3(Loss) | true |
| simdjson (ondemand) | 317.104 | 0.441147 | 547.676ms | 1811 | 1280 | 738940 | 5446.48 | 0.144666 | 7.76398 | 4(Loss) | true |
