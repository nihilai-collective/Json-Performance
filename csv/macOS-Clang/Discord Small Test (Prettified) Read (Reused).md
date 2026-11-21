
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2235.77 | 0.182722 | 317.152ms | 6701 | 4890 | 133387 | 2858.33 | 0.299184 | 1(Win) | true |
| Jsonifier (two-stage) | 2066.12 | 0.230004 | 374.51ms | 6701 | 30 | 1518.31 | 3093.03 | 0.090608 | 2(Loss) | true |
| Glaze | 2034.13 | 0.295057 | 351.83ms | 6701 | 30 | 2577.82 | 3141.67 | 0.265606 | 3(Loss) | true |
| simdjson (ondemand) | 943.846 | 0.182924 | 817.872ms | 6701 | 40 | 6135.87 | 6770.77 | 0.0412141 | 4(Loss) | true |
