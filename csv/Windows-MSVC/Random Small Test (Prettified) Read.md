
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1123.17 | 0.155291 | 701.895ms | 8051 | 4890 | 551076 | 6836.03 | 0.0602842 | 2.18939 | 1(Win) | true |
| Jsonifier | 1059.53 | 0.183993 | 758.596ms | 8051 | 30 | 5333.33 | 7246.67 | 0.230521 | 2.3215 | 2(Loss) | true |
| Glaze | 879.716 | 0.218139 | 868.866ms | 8051 | 2560 | 927942 | 8727.85 | 0.0380572 | 2.79811 | 3(Loss) | true |
| simdjson (ondemand) | 757.909 | 0.183015 | 1037.11ms | 8051 | 2560 | 879997 | 10130.5 | 0.0816786 | 3.25215 | 4(Loss) | true |
