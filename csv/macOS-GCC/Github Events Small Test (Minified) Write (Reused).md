
----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14292.6 | 3.7013 | 15.742ms | 1996 | 4890 | 118827 | 133.183 | 1.58873 | 1(Win) | true |
| simdjson (reflection) | 11323.7 | 3.31739 | 19.338ms | 1996 | 4890 | 152071 | 168.101 | 0.539134 | 2(Loss) | true |
| Glaze | 3614.76 | 2.66688 | 55.808ms | 1996 | 1280 | 252451 | 526.6 | 0.649847 | 3(Loss) | true |
