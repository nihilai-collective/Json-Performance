
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1258.6 | 0.0898539 | 9044.73ms | 94653 | 2560 | 1.06319e+07 | 71721.3 | 0.0655089 | 1.9664 | 1(Win) | true |
| Jsonifier (two-stage) | 1219.2 | 0.0575744 | 9304.71ms | 94653 | 4890 | 8.88566e+06 | 74039.1 | 0.205155 | 2.0299 | 2(Loss) | true |
| Glaze | 1165.67 | 0.0951343 | 9552.32ms | 94653 | 2560 | 1.38941e+07 | 77438.7 | 0.22181 | 2.12311 | 3(Loss) | true |
| simdjson (ondemand) | 1081.31 | 0.205659 | 5164.69ms | 94653 | 320 | 9.43224e+06 | 83480.3 | 0.0108547 | 2.2878 | 4(Loss) | true |
