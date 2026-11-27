
----
### Discord Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 822.164 | 0.0325097 | 792.821ms | 6701 | 160 | 1021.67 | 7772.86 | 0.0199452 | 1(Win) | true |
| simdjson (ondemand) | 195.441 | 0.300862 | 3288.17ms | 6701 | 160 | 1.54847e+06 | 32698.2 | 0.243322 | 2(Loss) | true |
