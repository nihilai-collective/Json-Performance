
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1515.54 | 0.526279 | 136.809ms | 2158 | 4890 | 249753 | 1357.95 | 2.31266 | 1(Win) | true |
| simdjson (ondemand) | 1401.93 | 0.696406 | 151.831ms | 2158 | 2560 | 267557 | 1468 | 0.0136258 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1353.38 | 0.483738 | 156.147ms | 2158 | 4890 | 264603 | 1520.66 | 0.979297 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1348.02 | 0.703215 | 155.405ms | 2158 | 2560 | 295069 | 1526.7 | 0.0852235 | 3(Tie) | true |
| Jsonifier | 1248.05 | 0.892494 | 162.851ms | 2158 | 2560 | 554488 | 1649 | 0.506818 | 5(Loss) | true |
