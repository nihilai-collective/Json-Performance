
----
### Canada Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1059.75 | 0.370283 | 1085.99ms | 11579 | 320 | 476378 | 10420 | 0.192308 | 1(Win) | true |
| simdjson (ondemand) | 986.322 | 0.766911 | 1098.86ms | 11579 | 30 | 221165 | 11195.7 | 0.0761615 | 2(Loss) | true |
