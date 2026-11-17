
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1515.72 | 0.475987 | 534.664ms | 8051 | 320 | 186038 | 5065.6 | 1.18249 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1290.9 | 0.174701 | 606.656ms | 8051 | 1280 | 138202 | 5947.8 | 0.32047 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1278.48 | 0.703893 | 587.491ms | 8051 | 320 | 571842 | 6005.6 | 0.200214 | 2(Tie) | true |
| simdjson (ondemand) | 1106.73 | 0.402514 | 727.375ms | 8051 | 80 | 62383.6 | 6937.6 | 0.184162 | 4(Loss) | true |
| Glaze | 1024.28 | 0.80649 | 712.549ms | 8051 | 320 | 1.16952e+06 | 7496 | 3.05763 | 5(Loss) | true |
