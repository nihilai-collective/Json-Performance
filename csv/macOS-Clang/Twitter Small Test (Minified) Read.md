
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2329.2 | 0.0543848 | 121.844ms | 2889 | 1280 | 529.72 | 1182.88 | 0.112405 | 1(Win) | true |
| Jsonifier (two-stage) | 1881.2 | 0.0881845 | 149.826ms | 2889 | 160 | 266.887 | 1464.58 | 0.147436 | 2(Loss) | true |
| Glaze | 1812.91 | 0.461197 | 167.627ms | 2889 | 40 | 1965.06 | 1519.75 | 0.16751 | 3(Loss) | true |
| simdjson (ondemand) | 847.202 | 0.205076 | 328.991ms | 2889 | 40 | 1779.15 | 3252.07 | 0.0632529 | 4(Loss) | true |
