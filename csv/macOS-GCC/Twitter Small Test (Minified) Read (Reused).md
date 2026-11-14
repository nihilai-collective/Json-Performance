
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2792.59 | 0.38674 | 119.931ms | 2889 | 1280 | 18635 | 986.6 | 0.509372 | 1(Win) | true |
| Glaze | 2208.73 | 1.03057 | 146.647ms | 2889 | 1280 | 211531 | 1247.4 | 0.112108 | 2(Loss) | true |
| Jsonifier (two-stage) | 2108.65 | 0.74211 | 151.042ms | 2889 | 2560 | 240692 | 1306.6 | 0.476776 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1197.48 | 2.66654 | 212.166ms | 2889 | 80 | 301123 | 2300.8 | 1.50685 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1154.87 | 0.449753 | 264.348ms | 2889 | 2560 | 294727 | 2385.7 | 1.47597 | 4(Tie) | true |
