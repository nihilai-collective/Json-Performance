
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1262.35 | 0.399193 | 9317.06ms | 94653 | 320 | 2.60749e+07 | 71507.8 | 0.474521 | 1.96055 | 1(Win) | true |
| Jsonifier (two-stage) | 1160.53 | 0.218766 | 5064.82ms | 94653 | 640 | 1.85308e+07 | 77781.9 | 0.307893 | 2.13259 | 2(Loss) | true |
| Glaze | 1104.19 | 0.298151 | 5214.81ms | 94653 | 640 | 3.80218e+07 | 81750.5 | 0.100243 | 2.24137 | 3(Loss) | true |
| simdjson (ondemand) | 978.306 | 0.458436 | 5505.26ms | 94653 | 2560 | 4.58054e+08 | 92269.8 | 0.369359 | 2.52993 | 4(Loss) | true |
