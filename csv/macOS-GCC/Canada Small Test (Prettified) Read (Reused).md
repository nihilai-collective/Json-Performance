
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1345.72 | 0.132293 | 932.42ms | 11579 | 2560 | 301677 | 8205.7 | 0.295261 | 1(Win) | true |
| simdjson (ondemand) | 1302.33 | 0.117221 | 957.344ms | 11579 | 4890 | 483080 | 8479.1 | 0.023618 | 2(Loss) | true |
