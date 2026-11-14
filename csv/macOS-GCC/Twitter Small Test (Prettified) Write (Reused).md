
----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14557.1 | 2.29214 | 30.1501ms | 4300 | 4890 | 203883 | 281.705 | 0.143869 | 1(Win) | true |
| Glaze | 3498.68 | 0.685342 | 121.188ms | 4300 | 2560 | 165190 | 1172.1 | 0.713181 | 2(Loss) | true |
| simdjson (reflection) | 332.6 | 0.237991 | 1232.41ms | 4300 | 4890 | 4.21037e+06 | 12329.5 | 0.161784 | 3(Loss) | true |
