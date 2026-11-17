
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1141.55 | 0.299128 | 384.692ms | 4390 | 40 | 4814.1 | 3667.5 | 0.204918 | 2.14854 | 1(Win) | true |
| Jsonifier (two-stage) | 949.618 | 0.172108 | 450.754ms | 4390 | 80 | 4606.01 | 4408.75 | 0.0283447 | 2.59361 | 2(Loss) | true |
| Glaze | 793.921 | 0.360241 | 533.787ms | 4390 | 1280 | 461925 | 5273.36 | 0.211407 | 3.0999 | 3(Loss) | true |
| simdjson (ondemand) | 491.123 | 0.355398 | 864.069ms | 4390 | 1280 | 1.17487e+06 | 8524.61 | 0.213081 | 5.02213 | 4(Loss) | true |
