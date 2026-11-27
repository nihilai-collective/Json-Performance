
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2730.43 | 0.0253204 | 897.809ms | 25388 | 160 | 806.597 | 8867.42 | 0.01431 | 1(Win) | true |
| Jsonifier (two-stage) | 2327.57 | 0.0616084 | 1046.31ms | 25388 | 4890 | 200836 | 10402.2 | 0.00711752 | 2(Loss) | true |
| Glaze | 1774.17 | 0.168255 | 1455.1ms | 25388 | 40 | 21089.2 | 13646.9 | 0.0580446 | 3(Loss) | true |
| simdjson (ondemand) | 1647.31 | 0.13431 | 1476.05ms | 25388 | 1280 | 498810 | 14697.8 | 0.0197004 | 4(Loss) | true |
