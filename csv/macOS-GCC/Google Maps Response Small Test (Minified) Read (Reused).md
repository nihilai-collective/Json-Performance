
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2157.71 | 0.22414 | 237.858ms | 4390 | 4890 | 92489.2 | 1940.31 | 0.128038 | 1(Win) | true |
| Jsonifier (two-stage) | 1441.23 | 0.292652 | 338.965ms | 4390 | 2560 | 185014 | 2904.9 | 0.243819 | 2(Loss) | true |
| Glaze | 1213.09 | 0.611553 | 398.766ms | 4390 | 640 | 285094 | 3451.2 | 0.300439 | 3(Loss) | true |
| simdjson (reflection) | 1095.75 | 0.372966 | 424.891ms | 4390 | 1280 | 259930 | 3820.8 | 0.293994 | 4(Loss) | true |
| simdjson (ondemand) | 689.044 | 0.388926 | 622.895ms | 4390 | 2560 | 1.42959e+06 | 6076 | 0.341163 | 5(Loss) | true |
