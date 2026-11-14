
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10774.9 | 1.82369 | 42.3549ms | 4390 | 4890 | 245535 | 388.555 | 0.268326 | 1(Win) | true |
| simdjson (reflection) | 8436.67 | 1.46098 | 52.5399ms | 4390 | 4890 | 257030 | 496.242 | 0.492856 | 2(Loss) | true |
| Glaze | 1922.59 | 1.03026 | 233.716ms | 4390 | 320 | 161064 | 2177.6 | 0.438917 | 3(Loss) | true |
