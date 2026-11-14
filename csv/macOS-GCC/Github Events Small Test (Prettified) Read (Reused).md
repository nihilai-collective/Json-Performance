
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2145.57 | 0.665521 | 120.536ms | 2158 | 1280 | 52161.7 | 959.2 | 0.502934 | 1(Win) | true |
| Glaze | 2051.46 | 0.904247 | 147.354ms | 2158 | 160 | 13166.5 | 1003.2 | 0.480769 | 2(Loss) | true |
| Jsonifier (two-stage) | 1983.83 | 0.385532 | 128.617ms | 2158 | 2560 | 40950 | 1037.4 | 0.425944 | 3(Loss) | true |
| simdjson (ondemand) | 1726.31 | 0.490826 | 138.665ms | 2158 | 4890 | 167428 | 1192.15 | 0.739715 | 4(Loss) | true |
| simdjson (reflection) | 1594.34 | 0.531053 | 152.046ms | 2158 | 4890 | 229788 | 1290.84 | 0.422966 | 5(Loss) | true |
