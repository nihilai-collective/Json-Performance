
----
### Discord Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 834.495 | 0.157171 | 812.137ms | 6701 | 4890 | 708415 | 7658.01 | 0.15369 | 1(Win) | true |
| simdjson (ondemand) | 242.773 | 0.278331 | 2835.47ms | 6701 | 40 | 214714 | 26323.2 | 0.331179 | 2(Loss) | true |
