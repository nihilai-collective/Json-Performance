
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 515.208 | 0.23805 | 880.533ms | 4604 | 2560 | 1.05362e+06 | 8522.23 | 0.0499862 | 4.79054 | 1(Win) | true |
| Jsonifier (two-stage) | 467.595 | 0.246736 | 970.485ms | 4604 | 30 | 16103.4 | 9390 | 0.142197 | 5.27886 | 2(Loss) | true |
| simdjson (ondemand) | 190.348 | 0.108954 | 2345.84ms | 4604 | 4890 | 3.08863e+06 | 23066.8 | 0.101928 | 12.9905 | 3(Loss) | true |
| Glaze | 160.178 | 0.104057 | 2770.4ms | 4604 | 4890 | 3.97845e+06 | 27411.5 | 0.0418767 | 15.4413 | 4(Loss) | true |
