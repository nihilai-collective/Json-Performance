
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1845.21 | 1.3694 | 150.201ms | 2821 | 640 | 255127 | 1458 | 0.635008 | 1(Win) | true |
| simdjson (ondemand) | 1358.2 | 0.468167 | 204.934ms | 2821 | 320 | 27519 | 1980.8 | 0 | 2(Loss) | true |
