
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 6086.47 | 0.978685 | 67.8269ms | 3808 | 30 | 1022.99 | 596.667 | 0 | 0.485557 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 6046.35 | 0.454929 | 67.8213ms | 3808 | 160 | 1194.58 | 600.625 | 0.104167 | 0.483855 | 1(Tie) | true |
| simdjson (ondemand) | 4991.61 | 1.27035 | 79.8586ms | 3808 | 2560 | 218675 | 727.539 | 0.480147 | 0.592922 | 3(Loss) | true |
| Glaze | 3373 | 0.729477 | 115.692ms | 3808 | 30 | 1850.57 | 1076.67 | 0.615385 | 0.880427 | 4(Loss) | true |
