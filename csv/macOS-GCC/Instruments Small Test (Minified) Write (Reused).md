
----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15256.3 | 2.2375 | 31.638ms | 4669 | 4890 | 208539 | 291.861 | 0.88522 | 1(Win) | true |
| simdjson (reflection) | 8350.87 | 1.36801 | 57.8202ms | 4669 | 4890 | 260180 | 533.202 | 0.817996 | 2(Loss) | true |
| Glaze | 2181.42 | 0.22869 | 209.363ms | 4669 | 2560 | 55783.6 | 2041.2 | 0.787402 | 3(Loss) | true |
