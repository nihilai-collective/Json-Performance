
----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 8060.39 | 0.653882 | 5765.93ms | 466906 | 80 | 1.04384e+07 | 55242.5 | 0.252787 | 0.306915 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 7989.96 | 0.140355 | 5761.51ms | 466906 | 1280 | 7.83131e+06 | 55729.5 | 0.0343338 | 0.309678 | 1(Tie) | true |
| simdjson (ondemand) | 3480.26 | 0.56289 | 6677.47ms | 466906 | 30 | 1.55598e+07 | 127943 | 0.616245 | 0.711205 | 3(Loss) | true |
| Glaze | 2912.35 | 0.1453 | 7919.82ms | 466906 | 320 | 1.57927e+07 | 152892 | 0.397388 | 0.849968 | 4(Loss) | true |
