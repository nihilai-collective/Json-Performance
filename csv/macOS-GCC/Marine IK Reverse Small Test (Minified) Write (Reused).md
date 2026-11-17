
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1843.83 | 0.454392 | 242.771ms | 4604 | 2560 | 299729 | 2381.3 | 0.459838 | 1(Win) | true |
| simdjson (reflection) | 1565.9 | 0.627179 | 306.325ms | 4918 | 40 | 14115.4 | 2995.2 | 0 | 2(Loss) | true |
| Glaze | 1051.05 | 0.183871 | 421.78ms | 4604 | 4890 | 288510 | 4177.46 | 0.0177276 | 3(Loss) | true |
