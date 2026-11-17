
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1557.23 | 0.796032 | 882.623ms | 11579 | 30 | 95592.2 | 7091.2 | 0 | 1(Win) | true |
| Jsonifier | 1518.3 | 0.276656 | 864.994ms | 11579 | 1280 | 518225 | 7273 | 0.194862 | 2(Loss) | true |
| simdjson (reflection) | 1393.52 | 0.268971 | 906.939ms | 11579 | 4890 | 2.22146e+06 | 7924.27 | 0.679661 | 3(Loss) | true |
| simdjson (ondemand) | 1192.61 | 0.990708 | 1125.63ms | 11579 | 160 | 1.34635e+06 | 9259.2 | 0.120815 | 4(Loss) | true |
| Glaze | 1124.62 | 0.279013 | 1115.05ms | 11579 | 1280 | 960713 | 9819 | 0.136657 | 5(Loss) | true |
