
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1400.01 | 0.170988 | 927.251ms | 11579 | 40 | 7275.64 | 7887.5 | 0.222363 | 2.16313 | 1(Win) | true |
| Jsonifier | 1274.71 | 0.0589997 | 996.141ms | 11579 | 4890 | 127740 | 8662.82 | 0.157731 | 2.37794 | 2(Loss) | true |
| simdjson (ondemand) | 820.52 | 0.11781 | 1483.21ms | 11579 | 1280 | 321765 | 13458 | 0.0121921 | 3.69778 | 3(Loss) | true |
| Glaze | 750.83 | 0.116504 | 1599.38ms | 11579 | 640 | 187898 | 14707.2 | 0.106354 | 4.04176 | 4(Loss) | true |
