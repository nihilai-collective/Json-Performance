
----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12286.3 | 2.45603 | 42.1059ms | 5094 | 2560 | 241424 | 395.4 | 1.28074 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 8225.84 | 1.22645 | 60.0399ms | 5094 | 4890 | 256544 | 590.58 | 5.78183 | -(Loss) | false |
| Glaze | 2303.31 | 0.247704 | 214.789ms | 5094 | 4890 | 133472 | 2109.15 | 1.74934 | 3(Loss) | true |
