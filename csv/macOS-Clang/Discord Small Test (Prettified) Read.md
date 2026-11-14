
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2129.25 | 0.0596531 | 304.553ms | 6701 | 160 | 512.875 | 3001.32 | 0.00833035 | 1(Win) | true |
| Jsonifier (two-stage) | 1650.18 | 0.0515243 | 394.778ms | 6701 | 160 | 637.032 | 3872.66 | 0.114879 | 2(Loss) | true |
| Glaze | 1621.94 | 0.0853578 | 401.135ms | 6701 | 320 | 3619.49 | 3940.08 | 0.211658 | 3(Loss) | true |
| simdjson (ondemand) | 871.991 | 0.0990063 | 745.573ms | 6701 | 80 | 4211.83 | 7328.71 | 0.079716 | 4(Loss) | true |
