
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 720.401 | 0.574958 | 6596.98ms | 94653 | 2560 | 1.32872e+09 | 125303 | 0.0203923 | 3.4358 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 706.621 | 1.8398 | 6704.49ms | 94653 | 320 | 1.76761e+09 | 127746 | 0.297555 | 3.50276 | 1(Tie) | true |
| simdjson (ondemand) | 702.876 | 0.595578 | 6736.04ms | 94653 | 1280 | 7.48856e+08 | 128427 | 1.46644 | 3.52157 | 3(Loss) | true |
| Glaze DID NOT CONVERGE | 673.955 | 1.00996 | 7266.92ms | 94653 | 640 | 1.1711e+09 | 133938 | 2.79558 | 3.6728 | -(Loss) | false |
