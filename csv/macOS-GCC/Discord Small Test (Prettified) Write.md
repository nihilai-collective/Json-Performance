
----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13440.6 | 1.38451 | 55.1421ms | 7376 | 4890 | 256747 | 523.36 | 0.549535 | 1(Win) | true |
| Glaze | 2175.05 | 0.249837 | 315.393ms | 7376 | 4890 | 319246 | 3234.08 | 0.413211 | 2(Loss) | true |
| simdjson (reflection) | 357.841 | 0.190222 | 2078.05ms | 7376 | 160 | 223719 | 19657.6 | 0.0975768 | 3(Loss) | true |
