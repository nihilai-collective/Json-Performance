
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2153.37 | 0.135153 | 223.954ms | 4857 | 80 | 676.149 | 2151.05 | 0.147821 | 1(Win) | true |
| Jsonifier (two-stage) | 1672.49 | 0.063093 | 289.989ms | 4857 | 320 | 977.059 | 2769.52 | 0.122463 | 2(Loss) | true |
| Glaze | 1390.41 | 0.135851 | 367.584ms | 4857 | 320 | 6554.31 | 3331.39 | 0.0904396 | 3(Loss) | true |
| simdjson (ondemand) | 651.467 | 0.0738996 | 724.395ms | 4857 | 160 | 4417.29 | 7110.11 | 0.0410339 | 4(Loss) | true |
