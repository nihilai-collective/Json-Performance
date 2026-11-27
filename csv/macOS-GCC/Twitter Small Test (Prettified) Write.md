
----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13601.3 | 3.0205 | 32.4442ms | 4300 | 2560 | 212310 | 301.5 | 0.567045 | 1(Win) | true |
| Glaze | 3272.26 | 1.40041 | 129.301ms | 4300 | 640 | 197119 | 1253.2 | 0.288092 | 2(Loss) | true |
| simdjson (reflection) | 416.093 | 0.114711 | 992.365ms | 4300 | 4890 | 624991 | 9855.48 | 0.138042 | 3(Loss) | true |
