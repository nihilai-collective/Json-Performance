
----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1718.04 | 0.196327 | 537.512ms | 8150 | 4890 | 385761 | 4524.03 | 0.266136 | 1(Win) | true |
| simdjson (ondemand) | 1090.56 | 0.207783 | 803.454ms | 8150 | 1280 | 280701 | 7127 | 0.560888 | 2(Loss) | true |
