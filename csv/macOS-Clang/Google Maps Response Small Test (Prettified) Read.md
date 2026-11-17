
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2466.62 | 0.536613 | 365.368ms | 9378 | 4890 | 1.85118e+06 | 3625.84 | 1.94403 | 1(Win) | true |
| Jsonifier (two-stage) | 1882.11 | 0.683098 | 455.96ms | 9378 | 1280 | 1.34867e+06 | 4751.87 | 0.469426 | 2(Loss) | true |
| Glaze | 1448.17 | 0.315679 | 619.507ms | 9378 | 2560 | 972996 | 6175.75 | 0.0147144 | 3(Loss) | true |
| simdjson (ondemand) | 1230.23 | 0.534929 | 697.212ms | 9378 | 160 | 241968 | 7269.81 | 0.209247 | 4(Loss) | true |
