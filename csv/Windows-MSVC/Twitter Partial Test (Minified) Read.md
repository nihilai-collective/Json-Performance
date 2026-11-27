
----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7732.49 | 0.168839 | 5920ms | 466906 | 1280 | 1.20997e+07 | 57585.1 | 0.359177 | 0.319955 | 1(Win) | true |
| Jsonifier (two-stage) | 7599.3 | 0.332306 | 5844.51ms | 466906 | 320 | 1.21322e+07 | 58594.4 | 0.0149309 | 0.325622 | 2(Loss) | true |
| simdjson (ondemand) | 3306.92 | 0.354997 | 7033.48ms | 466906 | 80 | 1.8279e+07 | 134650 | 0.279573 | 0.748429 | 3(Loss) | true |
| Glaze | 2833.18 | 0.258466 | 8246.25ms | 466906 | 80 | 1.3201e+07 | 157165 | 0.138198 | 0.873678 | 4(Loss) | true |
