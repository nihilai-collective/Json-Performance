
----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14018.9 | 0.0724509 | 22.7845ms | 2963 | 1280 | 27.2982 | 201.566 | 0.101059 | 0.152754 | 1(Win) | true |
| simdjson (reflection) | 11102.5 | 0.133178 | 28.0828ms | 2963 | 320 | 36.7647 | 254.512 | 0.242522 | 0.201126 | 2(Loss) | true |
| Glaze | 5595.24 | 0.15702 | 53.7084ms | 2963 | 40 | 25.1532 | 505.025 | 0.19012 | 0.41895 | 3(Loss) | true |
