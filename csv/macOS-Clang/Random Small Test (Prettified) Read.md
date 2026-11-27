
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1653.72 | 0.0666569 | 477.421ms | 8150 | 160 | 1570.38 | 4699.99 | 0.533417 | 1(Win) | true |
| simdjson (ondemand) | 1273.97 | 0.126142 | 611.83ms | 8150 | 4890 | 289617 | 6100.97 | 0.396721 | 2(Loss) | true |
