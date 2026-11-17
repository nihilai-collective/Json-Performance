
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2089.87 | 0.105936 | 220.372ms | 4390 | 30 | 135.114 | 2003.3 | 0.084788 | 1.1687 | 1(Win) | true |
| Glaze | 1817.3 | 0.255894 | 243.509ms | 4390 | 30 | 1042.6 | 2303.77 | 0.12749 | 1.34657 | 2(Loss) | true |
| Jsonifier (two-stage) | 1710.03 | 0.0665663 | 264.071ms | 4390 | 80 | 212.48 | 2448.28 | 0.395715 | 1.43198 | 3(Loss) | true |
| simdjson (reflection) | 1518.46 | 0.143995 | 294.19ms | 4390 | 40 | 630.49 | 2757.15 | 0.00302254 | 1.61478 | 4(Loss) | true |
| simdjson (ondemand) | 1272.94 | 0.152052 | 347.044ms | 4390 | 30 | 750.271 | 3288.93 | 0.0415362 | 1.92836 | 5(Loss) | true |
