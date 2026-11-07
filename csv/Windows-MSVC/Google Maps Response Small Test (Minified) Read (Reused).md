
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1398.48 | 0.318392 | 347.416ms | 4390 | 2560 | 232586 | 2993.71 | 0.221002 | 1.75514 | 1(Win) | true |
| Jsonifier (two-stage) | 1191.92 | 0.2086 | 413.758ms | 4390 | 40 | 2147.44 | 3512.5 | 0.0237192 | 2.0733 | 2(Loss) | true |
| Glaze | 1000.24 | 0.167934 | 477.402ms | 4390 | 160 | 7905.27 | 4185.62 | 0.164523 | 2.45717 | 3(Loss) | true |
| simdjson (ondemand) | 617.801 | 0.288989 | 753.227ms | 4390 | 30 | 11505.7 | 6776.67 | 0.0984737 | 3.9947 | 4(Loss) | true |
