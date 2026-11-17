
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10002.6 | 1.72269 | 45.1789ms | 4390 | 4890 | 254227 | 418.552 | 2.52628 | 1(Win) | true |
| simdjson (reflection) | 7767.96 | 1.33052 | 56.7212ms | 4390 | 4890 | 251457 | 538.961 | 1.97142 | 2(Loss) | true |
| Glaze | 1772.19 | 1.18871 | 246.259ms | 4390 | 320 | 252354 | 2362.4 | 0.579019 | 3(Loss) | true |
